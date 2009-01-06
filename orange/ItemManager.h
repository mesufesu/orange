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
#include ".\\mutex.h"
#include ".\\Item.h"

class CItemManager
{
public:
	CMyMutex con_mutex;
	std::map<uint32, CItem*> item_container;
	CItemManager();
	void LoadCharacterItems();
	bool Instanciate(const CItem* item);
	void DeleteInstance(const CItem* item);
	bool SaveItem(CItem* item, uint32 slot);
};

extern CItemManager ItemManager;

bool LoadItem(DATA_ITEM* item, int guid);

#endif