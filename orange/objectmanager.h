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

#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <vector>
#include ".\\object.h"
#include ".\\mutex.h"
#include ".\\player.h"

class CObjectManager
{
public:
	HANDLE procHandle;
	std::map<short, CObject*> container;
	CMyMutex con_mutex;
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