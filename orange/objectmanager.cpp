/*
	Copyright 2008-2009 Ambient.5

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stdafx.h"
#include ".\\ItemManager.h"
#include ".\\objectmanager.h"

CObjectManager ObjManager;

CObjectManager::CObjectManager()
{
	this->container.clear();
	this->procHandle = 0;
}

CPlayer* CObjectManager::FindPlayerBySocket(ServerSocket *socket)
{
	for(std::map<short, CObject*>::iterator it = this->container.begin(); it != this->container.end(); ++it)
	{
		if((it->second->type == OBJECT_PLAYER) && (((CPlayer*)it->second)->socket == socket))
		{
			return ((CPlayer*)it->second);
		}
	}
	return NULL;
}

CPlayer* CObjectManager::FindPlayerByGuid(short guid) //deprecated
{
	for(std::map<short, CObject*>::iterator it = this->container.begin(); it != this->container.end(); ++it)
	{
		if((it->second->type == OBJECT_PLAYER) && (it->second->guid == guid))
		{
			return ((CPlayer*)it->second);
		}
	}
	return NULL;
}

CObject* CObjectManager::FindByGuid(short guid)
{
	std::map<short, CObject*>::iterator it;
	it = this->container.find(guid);
	if(it == this->container.end())
	{
		return NULL;
	}
	return it->second;
}

CPlayer* CObjectManager::CreatePlayer(ServerSocket* socket)
{
	CPlayer* player = new CPlayer;
	while(TRUE)
	{
		short new_guid = rand() % 32000;
		std::pair<std::map<short, CObject*>::iterator, bool> pr;
		pr = this->container.insert(std::make_pair<short, CObject*>(new_guid, (CObject*)player));
		if(pr.second == true)
		{
			player->guid = new_guid;
			player->socket = socket;
			printf_s("[DEBUG] %d %d\n", pr.first->first, pr.first->second->guid);
			return player;
		}
		else
		{
			continue;
		}
	}
}

void CObjectManager::Delete(CObject* object) //useless too, lol
{
	for(std::map<short, CObject*>::iterator it = this->container.begin(); it != this->container.end(); ++it)
	{
		if(it->second == object)
		{
			this->container.erase(it);
			switch(object->type)
			{
			case VOID_EMPTY:
				{
					delete object;
					break;
				}
			case VOID_UNIT:
				{
					//TODO
					break;
				}
			case VOID_PLAYER:
				{
					CPlayer* player = (CPlayer*)object;
					delete player;
					break;
				}
			}
		}
	}
}

void WINAPI CObjectManager::ObjectManagerProc(CObjectManager* mang)
{
	while(TRUE)
	{
		mang->con_mutex.Lock();
		for(std::map<short, CObject*>::iterator it = mang->container.begin(); it != mang->container.end(); 1)
		{
			std::map<short, CObject*>::iterator to_delete = it;
			it++;
			CObject* object = to_delete->second;
			if((object->type == VOID_EMPTY) || (object->type == VOID_UNIT) || (object->type == VOID_PLAYER))
			{
				mang->container.erase(to_delete);
				switch(object->type)
				{
				case VOID_EMPTY:
					{
						delete object;
						break;
					}
				case VOID_UNIT:
					{
						//TODO
						break;
					}
				case VOID_PLAYER:
					{
						CPlayer* player = (CPlayer*)object;
						for(uint32 i = 0; i < 108; ++i)
						{
							if(player->inventory[i]->IsItem())
							{
								player->inventory[i]->status = ITEM_NOTEXIST;
							}
						}
						delete player;
						break;
					}
				}
			}
		}
		mang->con_mutex.Unlock();
		Sleep(10000);
	}
}

void CObjectManager::Run()
{
	uint32 id;
	this->procHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CObjectManager::ObjectManagerProc, (LPVOID)this, 0, (LPDWORD)&id);
}