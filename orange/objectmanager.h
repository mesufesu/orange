#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <vector>
#include ".\\object.h"
#include ".\\player.h"

class CObjectManager
{
public:
	HANDLE procHandle;
	std::map<short, CObject*> container;
	CObjectManager();
	CPlayer* FindPlayerBySocket(ServerSocket* socket);
	CPlayer* FindPlayerByGuid(short guid);
	CObject* CObjectManager::FindByGuid(short guid);
	CPlayer* CreatePlayer(ServerSocket* socket);
	//void DeletePlayer(CPlayer* player);
	void Delete(CObject* object);
	short MakeGuid(CObject* object);
	void Run();

	static void WINAPI ObjectManagerProc(CObjectManager* manager); //will cleanup each 10 seconds
};

extern CObjectManager ObjManager;

#endif