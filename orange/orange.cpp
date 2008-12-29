// orange.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include ".\\utils.h"
#include ".\\sockets\\socketsmain.h"
#include ".\\gamemain.h"
#include ".\\JoinServer.h"
#include ".\\DataServer.h"
#include ".\\HeartbeatServer.h"
#include ".\\ServerSocket.h"
#include ".\\DataBase.h"
#include ".\\Item.h"
#include ".\\WorldMap.h"
#include ".\\objectmanager.h"
#include ".\\WhatsUpDummyServer.h"

int main(int argc, char* argv[])
{
	char ip[] = "127.0.0.1";

	if(!TestDB.query->Connected())
	{
		printf_s("MySQL connection cannot be established. Closing.\n");
		return 0;
	}
	if(TestDB.query->execute("UPDATE `account_test` SET `status` = 0 WHERE `status` <> 0"))
	{
		printf_s("Online status set to 0.\n");
	}

	//SocketMainInit();
	GameMainInit();
	//JoinServerConnect(ip, 1027);
	//DataServerCli.Connect();
	DWORD dwThreadId;
	HANDLE hHBThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HeartbeatServerProc, (LPVOID)55902, 0, &dwThreadId);
	HANDLE hServerSocketThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ServerSocketProc, (LPVOID)55901, 0, &dwThreadId);
	HANDLE hCSThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CSThreadProc, NULL, 0, &dwThreadId);
	printf_s("Socket Threads created.\n");
	ObjManager.Run();
	CObject * newPlayer = new CObject;
	/*ObjManager.obj_container.push_back(newPlayer);
	newPlayer->guid = ObjManager.MakeGuid((CObject*)newPlayer);
	newPlayer->x = 131;
	newPlayer->y = 133;
	newPlayer->map = 0;
	newPlayer->type = OBJECT_EMPTY;*/
	for(uint32 i = 0; i < MAX_MAPS; ++i)
	{
		char filename[256];
		ZeroMemory(filename, sizeof(filename));
		sprintf_s(filename, sizeof(filename), ".\\data\\maps\\Terrain%d.att", i + 1);
		WorldMap[i].map_number = i;
		WorldMap[i].LoadMap(filename);
		WorldMap[i].map_handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CWorldMap::UpdateProc, &WorldMap[i], 0, &dwThreadId);
	}
	printf_s("WorldMap threads started.\n");
	WaitForSingleObject(hServerSocketThread, INFINITE);
	return 0;
}
