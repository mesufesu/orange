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
#include ".\\bot.h"
#include ".\\WorldMap.h"
#include <QtCore\\QMutex>
#include <QtCore\\QThread>

class CObjectThread : public QThread
{
public:
	void run();
};

class CObjectManager
{
public:
	friend void CObjectThread::run();
	friend void CWorldMap::UpdateMap();
	typedef std::tr1::unordered_map<uint16, CObject*> MapType;
	CObjectManager();
	CPlayer* FindPlayerBySocket(ServerSocket* socket);
	//CPlayer* FindPlayerByGuid(short guid);
	CObject* CObjectManager::FindByGuid(uint16 guid);
	CPlayer* CreatePlayer(ServerSocket* socket);
	CBot* CreateBot();
	//void DeletePlayer(CPlayer* player);
	void Delete(CObject* object);
	short MakeGuid(CObject* object);
	void Run();
	void Quit();

private:
	QMutex mtx;
	MapType container;
	CObjectThread ObjThread;
};

extern CObjectManager ObjManager;

#endif