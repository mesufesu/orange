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
#include <assert.h>
#include ".\\DataBase.h"

CObjectManager ObjManager;

CObjectManager::CObjectManager()
{
	this->container.clear();
}

CPlayer* CObjectManager::FindPlayerBySocket(ServerSocket *socket)
{
	CPlayer* player = NULL;
	this->mtx.lock();
	for(MapType::iterator it = this->container.begin(); it != this->container.end(); ++it)
	{
		if((it->second->type == OBJECT_PLAYER) && (((CPlayer*)it->second)->socket == socket))
		{
			player = (CPlayer*)it->second;
			break;
		}
	}
	this->mtx.unlock();
	return player;
}

/*CPlayer* CObjectManager::FindPlayerByGuid(short guid) //deprecated
{
	for(std::map<short, CObject*>::iterator it = this->container.begin(); it != this->container.end(); ++it)
	{
		if((it->second->type == OBJECT_PLAYER) && (it->second->guid == guid))
		{
			return ((CPlayer*)it->second);
		}
	}
	return NULL;
}*/

CObject* CObjectManager::FindByGuid(uint32 guid)
{
	this->mtx.lock();
	MapType::iterator it = this->container.find(guid);
	this->mtx.unlock();
	if(it == this->container.end())
	{
		return NULL;
	}
	return it->second;
}

CPlayer* CObjectManager::CreatePlayer(ServerSocket* socket)
{
	init_genrand(GetTickCount());
	CPlayer* player = new CPlayer;
	while(TRUE)
	{
		uint32 new_guid = ((genrand_int32() % MAX_PLAYER_GUID) + MAX_TEMP_GUID);
		std::pair<MapType::iterator, bool> pr;
		this->mtx.lock();
		pr = this->container.insert(MapType::value_type(new_guid, (CObject*)player));
		this->mtx.unlock();
		if(pr.second == true)
		{
			player->guid = new_guid;
			player->socket = socket;
			return player;
		}
		else
		{
			continue;
		}
	}
}

void CObjectManager::ActualizePlayer(CPlayer * player, uint32 new_guid)
{
	this->mtx.lock();
	this->container.erase(player->guid);
	std::pair<MapType::iterator, bool> pr;
	pr = this->container.insert(MapType::value_type(new_guid, (CObject*)player));
	if(pr.second == true)
	{
		player->guid = new_guid;
	}
	else
	{
		assert(pr.second);
	}
	this->mtx.unlock();
}

uint32 CObjectManager::GetFreePlayerGuid()
{
	init_genrand(GetTickCount());
	QSqlQuery q;
	while(true)
	{
		uint32 new_guid = genrand_int32() % MAX_PLAYER_GUID;
		q.exec(Query("SELECT `name` from `characters` WHERE `guid` = %u;", new_guid).c_str()); /*non blocking*/
		if(!q.next())
		{
			return new_guid;
		}
	}
}

CBot* CObjectManager::CreateBot()
{
	init_genrand(GetTickCount());
	CBot* bot = new CBot;
	while(true)
	{
		uint32 new_guid = ((genrand_int32() % (MAX_UNIT_GUID - MAX_PLAYER_GUID)) + MAX_PLAYER_GUID);
		std::pair<MapType::iterator, bool> pr;
		this->mtx.lock();
		pr = this->container.insert(MapType::value_type(new_guid, (CObject*)bot));
		this->mtx.unlock();
		if(pr.second == true)
		{
			bot->guid = new_guid;
			return bot;
		}
		else
		{
			continue;
		}
	}
}

void CObjectManager::Delete(CObject* object) //useless too, lol
{
	std::vector<MapType::iterator> trash_bin;
	trash_bin.clear();
	this->mtx.lock();
	for(MapType::iterator it = this->container.begin(); it != this->container.end(); ++it)
	{
		if(it->second == object)
		{
			//this->container.erase(it);
			trash_bin.push_back(it);
			switch(object->type)
			{
			case VOID_BOT:
				{
					CBot* bot = (CBot*)object;
					delete bot;
					break;
				}
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
	for(uint32 i = 0; i < trash_bin.size(); ++i)
	{
		this->container.erase(trash_bin.at(i));
	}
	this->mtx.unlock();
}

void CObjectThread::run()
{
	std::vector<CObjectManager::MapType::iterator> trash_bin;
	uint32 tick_count = GetTickCount();
	while(true)
	{
		if((GetTickCount() - tick_count) >= 10 * SECOND)
		{
			trash_bin.clear();
			ObjManager.mtx.lock();
			for(CObjectManager::MapType::iterator it = ObjManager.container.begin(); it != ObjManager.container.end(); ++it)
			{
				CObject* object = it->second;
				if((object) && (object->type < OBJECT_EMPTY))
				{
					trash_bin.push_back(it);
					switch(object->type)
					{
					case VOID_BOT:
						{
							CBot* bot = (CBot*)object;
							delete bot;
							break;
						}
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
			for(uint32 i = 0; i < trash_bin.size(); ++i)
			{
				ObjManager.container.erase(trash_bin.at(i));
			}
			ObjManager.mtx.unlock();
			tick_count = GetTickCount();
		}
		this->msleep(300);
	}
}

void CObjectManager::Run()
{
	this->ObjThread.start();
}

void CObjectManager::Quit()
{
	this->ObjThread.quit();
}