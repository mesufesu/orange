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

CPlayer* CObjectManager::FindSocket(ServerSocket *socket)
{
	CPlayer* player = NULL;
	this->rwl.lockForRead();
	for(MapType::iterator it = this->container.begin(); it != this->container.end(); ++it)
	{
		if((it->second->type == OBJECT_PLAYER) && (((CPlayer*)it->second)->socket == socket))
		{
			player = (CPlayer*)it->second;
			break;
		}
	}
	this->rwl.unlock();
	return player;
}

CObject* CObjectManager::FindHigh(GUID_HIGH guid)
{
	CObject * value = NULL;
	this->rwl.lockForRead();
	MapType::iterator it = this->container.find(guid);
	if(it != this->container.end())
	{
		value = it->second;
	}
	this->rwl.unlock();
	return value;
}

GUID_HIGH CObjectManager::CreateGuid()
{
	init_genrand(GetTicks());
	GUID_HIGH guid = 0;
	uint32 count = 0;
	while(count < RETRIES)
	{
		count++;
		guid = GUID_HIGH(genrand_int32());
		MapType::iterator it = this->container.find(guid);
		if(it == this->container.end())
		{
			break;
		}
	}
	assert(count != RETRIES);
	return guid;
}

CPlayer* CObjectManager::CreatePlayer(ServerSocket *socket)
{
	CPlayer * player = new CPlayer;
	this->rwl.lockForWrite();
	GUID_HIGH newguid = this->CreateGuid();
	std::pair<MapType::iterator, bool> pr;
	pr = this->container.insert(MapType::value_type(newguid, (CObject*)player));
	this->rwl.unlock();
	if(pr.second == true)
	{
		player->guid.hi = newguid;
		player->socket = socket;
		return player;
	}
	/* failed */
	delete player;
	return NULL;
}

CBot* CObjectManager::CreateBot()
{
	CBot * bot = new CBot;
	this->rwl.lockForWrite();
	GUID_HIGH newguid = this->CreateGuid();
	std::pair<MapType::iterator, bool> pr;
	pr = this->container.insert(MapType::value_type(newguid, (CObject*)bot));
	this->rwl.unlock();
	if(pr.second == true)
	{
		bot->guid.hi = newguid;
		return bot;
	}
	/* failed */
	delete bot;
	return NULL;
}

CUnit * CObjectManager::CreateUnit()
{
	CUnit * unit = new CUnit;
	this->rwl.lockForWrite();
	GUID_HIGH newguid = this->CreateGuid();
	std::pair<MapType::iterator, bool> pr;
	pr = this->container.insert(MapType::value_type(newguid, (CObject*)unit));
	this->rwl.unlock();
	if(pr.second == true)
	{
		unit->guid.hi = newguid;
		return unit;
	}
	/* failed */
	delete unit;
	return NULL;
}

/*CUnit * CObjectManager::CreateUnit()
{
	init_genrand(GetTicks());
	CUnit* unit = new CUnit;
	this->rwl.lockForWrite();
	while(true)
	{
		uint32 new_guid = (genrand_int32() % MAX_UNIT_GUID) + 1;
		std::pair<MapType::iterator, bool> pr;
		pr = this->container.insert(MapType::value_type(new_guid, (CObject*)unit));
		if(pr.second == true)
		{
			unit->guid = new_guid;
			break;
		}
	}
	this->rwl.unlock();
	return unit;
}*/

/*CBot* CObjectManager::CreateBot()
{
	init_genrand(GetTicks());
	CBot* bot = new CBot;
	this->rwl.lockForWrite();
	while(true)
	{
		uint32 new_guid = ((genrand_int32() % (MAX_BOT_GUID - MAX_UNIT_GUID - 1)) + MAX_UNIT_GUID + 1);
		std::pair<MapType::iterator, bool> pr;
		pr = this->container.insert(MapType::value_type(new_guid, (CObject*)bot));
		if(pr.second == true)
		{
			bot->guid = new_guid;
			break;
		}
	}
	this->rwl.unlock();
	return bot;
}*/

/*CPlayer* CObjectManager::CreatePlayer(ServerSocket* socket)
{
	init_genrand(GetTicks());
	CPlayer* player = new CPlayer;
	this->rwl.lockForWrite();
	while(TRUE)
	{
		uint32 new_guid = ((genrand_int32() % (MAX_PLAYER_GUID - MAX_BOT_GUID - 1)) + MAX_TEMP_GUID + 1);
		std::pair<MapType::iterator, bool> pr;
		pr = this->container.insert(MapType::value_type(new_guid, (CObject*)player));
		if(pr.second == true)
		{
			player->guid = new_guid;
			player->socket = socket;
			break;
		}
	}
	this->rwl.unlock();
	return player;
}*/

/*uint32 CObjectManager::GetFreePlayerGuid()
{
	init_genrand(GetTicks());
	QSqlQuery q;
	while(true)
	{
		uint32 new_guid = (genrand_int32() % (MAX_PLAYER_GUID - MAX_BOT_GUID - 1)) + MAX_BOT_GUID + 1;
		q.exec(Query("SELECT `name` from `characters` WHERE `guid` = %u;", new_guid).c_str()); /*non blocking*/
		/*if(!q.next())
		{
			return new_guid;
		}
	}
}*/