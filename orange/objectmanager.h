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
#include <QtCore/QReadWriteLock>
#include "object.h"
#include "player.h"
#include "bot.h"
#include "unit.h"
#include "WorldMap.h"

class CObjectManager
{
public:
	typedef UnorderedMap<GUID_HIGH, CObject*> MapType;
	CObjectManager();

	CPlayer* FindSocket(ServerSocket* socket);
	CObject* FindHigh(GUID_HIGH guid);
	CObject* CObjectManager::FindHIGH(GUID_HIGH guid);

	CPlayer* CreatePlayer(ServerSocket* socket);
	CBot* CreateBot();
	CUnit* CreateUnit();

	QReadWriteLock rwl;
	MapType container;

private:
	GUID_HIGH CreateGuid();
};

typedef CObjectManager * pObjectManager;

extern CObjectManager ObjManager;

#endif