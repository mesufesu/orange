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
#include "utils.h"
#include "HeartbeatServer.h"
#include "Deathway/SimpleModulus/SimpleModulus.h"
#include "ServerSocket.h"
#include "DataBase.h"
#include "Item.h"
#include "objectmanager.h"
#include "ObjectThread.h"
#include "ItemTemplate.h"
#include "UnitTemplate.h"
#include "log.h"
#include "bot.h"
#include "unit.h"
#include "classdef.h"
#include "cssocket.h"

int main(int argc, char* argv[])
{
	QCoreApplication orange(argc, argv);
	config.Read();
	MakeFrustum();
	DCInfo.Init();
	Log.Init(config.log_file_name.c_str());

	if(!g_SimpleModulusCS.LoadDecryptionKey("data/Dec1.dat"))
	{
		Log.String("Dec1.dat file not found");
		return 0;
	}
	if(!g_SimpleModulusSC.LoadEncryptionKey("data/Enc2.dat"))
	{
		Log.String("Enc2.dat file not found");
		return 0;
	}

	if(!data_db.Connect())
	{
		Log.String("Can't connect to %s:%s using %s:%s.", config.data_db_hostname.c_str(), config.data_db_dbname.c_str(), config.data_db_username.c_str(), config.data_db_password.c_str());
		return 0;
	}
	if(!accounts_db.Connect())
	{
		Log.String("Can't connect to %s:%s using %s:%s.", config.accounts_db_hostname.c_str(), config.accounts_db_dbname.c_str(), config.accounts_db_username.c_str(), config.accounts_db_password.c_str());
		return 0;
	}

	QSqlQuery q(accounts_db.db);
	if(q.exec("UPDATE `accounts` SET `status` = 0 WHERE `status` <> 0"))
	{
		Log.String("Online status set to 0.");
	}
	ItemTemplate.Load();
	UnitTemplate.Load();
	HeartBeatThread.start();
	_SocketThread.start(QThread::Priority::HighPriority);
	CSSocketThread.start();
	Log.String("Socket Threads created.");
	ItemManager.Run();
	for(uint32 i = 0; i < MAX_MAPS; ++i)
	{
		char filename[256];
		ZeroMemory(filename, sizeof(filename));
		sprintf_s(filename, sizeof(filename), "data/maps/Terrain%d.att", i + 1);
		WorldMap[i].map_number = i;
		WorldMap[i].LoadMap(filename);
	}
	Log.String("%u maps loaded.", MAX_MAPS);
	for(uint32 i = 0; i < 10000; ++i)
	{
		uint32 map = genrand_int32() % 60;
		CUnit* test_npc2 = ObjManager.CreateUnit();
		test_npc2->SetUnit(1, map, genrand_int32() % 256, genrand_int32() % 256, genrand_int32() % 256, genrand_int32() % 256, 0);
	}
	Log.String("Test bots created.");
	ObjThread.start();
	Log.String("Object processing thread started.");
	int32 exec = orange.exec();
	HeartBeatThread.exit();
	CSSocketThread.exit();
	ObjThread.Shutdown();
	_SocketThread.Shutdown();
	return exec;
}
