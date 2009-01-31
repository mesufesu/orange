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

#ifndef _ITEMMANAGER_H_
#define _ITEMMANAGER_H_

#include <map>
#include <unordered_map>
#include ".\\Item.h"
#include <QtCore\\QThread>
#include <QtCore\\QMutex>

class CItemThread : public QThread
{
public:
	void run();
};

class CItemManager
{
public:
	typedef std::tr1::unordered_map<uint32, CItem*> MapType;
	const CItem* CreateItem();
	CItem* InsertItem(uint32 guid);
	CItemManager();
	void LoadCharacterItems();
	void Run();
	void Quit();
	void CleanUp();
	static void WINAPI ItemProc(CItemManager* mang);
	static bool LoadItemData(DATA_ITEM* item, int guid);
	//bool Instanciate(const CItem* item);
	//void DeleteInstance(const CItem* item);
	bool SaveItem(CItem* item, uint32 slot);
	bool HaveGuid(uint32 guid);
	bool DeleteFromDB(uint32 guid); //hard

private:
	CItemThread ItemThread;
	MapType ItemMap;
	QMutex map_mutex;
};

extern CItemManager ItemManager;

#endif