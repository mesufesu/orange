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