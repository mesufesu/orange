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
#include ".\\utils.h"
#include ".\\HeartbeatServer.h"
#include ".\\ServerSocket.h"
#include ".\\DataBase.h"
#include ".\\Item.h"
#include ".\\WorldMap.h"
#include ".\\objectmanager.h"
#include ".\\ItemTemplate.h"
#include ".\\log.h"
#include ".\\bot.h"
#include ".\\classdef.h"
#include ".\\cssocket.h"

int main(int argc, char* argv[])
{
	QCoreApplication orange(argc, argv);
	MakeFrustum();
	DCInfo.Init();
	Log.Init("test.log");

	char ip[] = "127.0.0.1";

	if(!MainDB.Connect())
	{
		Log.String("MySQL connection cannot be established. Closing.");
		return 0;
	}
	QSqlQuery q;
	if(q.exec("UPDATE `accounts` SET `status` = 0 WHERE `status` <> 0"))
	{
		Log.String("Online status set to 0.");
	}
	ItemTemplate.Load();
	//SocketMainInit();
	//GameMainInit();
	//JoinServerConnect(ip, 1027);
	//DataServerCli.Connect();
	HeartBeatThread.start();
	_SocketThread.start((QThread::Priority)4);
	CSSocketThread.start();
	Log.String("Socket Threads created.");
	ObjManager.Run();
	ItemManager.Run();
	for(uint32 i = 0; i < MAX_MAPS; ++i)
	{
		char filename[256];
		ZeroMemory(filename, sizeof(filename));
		sprintf_s(filename, sizeof(filename), ".\\data\\maps\\Terrain%d.att", i + 1);
		WorldMap[i].map_number = i;
		WorldMap[i].LoadMap(filename);
		WorldMap[i].MapThread.lpmap = (void*)&WorldMap[i];
		WorldMap[i].Run();
	}
	Log.String("WorldMap threads started.");
	CBot* test_bot = ObjManager.CreateBot();
	test_bot->SetBot("Pwnage", 0, 130, 130);
	test_bot->Class = 5;
	test_bot->changeup = 2;
	test_bot->CookCharset();
	Log.String("Bot [Pwnage] created at 0,130,130");
	return orange.exec();
}
