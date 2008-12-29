#include "stdafx.h"
#include ".\\utils.h"
#include ".\\DataBase.h"
#include ".\\ItemManager.h"

CItemManager ItemManager;

CItemManager::CItemManager()
{
	this->item_container.clear();
}

bool CItemManager::Instanciate(const CItem* item)
{
	std::pair<std::map<uint32, CItem*>::iterator, bool> pr;
	this->con_mutex.Lock();
	pr = this->item_container.insert(std::make_pair<uint32, CItem*>(item->guid, (CItem*)item));
	this->con_mutex.Unlock();
	if(pr.second == true)
	{
		printf_s("[DEBUG] %d %d\n", pr.first->first, pr.first->second->guid);
		return true;
	}
	else
	{
		return false;
	}
}

void CItemManager::DeleteInstance(const CItem* item)
{
	bool deleted = false;
	this->con_mutex.Lock();
	for(std::map<uint32, CItem*>::iterator it = this->item_container.begin(); it != this->item_container.end(); true)
	{
		std::map<uint32, CItem*>::iterator to_delete = it;
		it++;
		if(to_delete->first == item->guid)
		{
			this->item_container.erase(to_delete);
			deleted = true;
		}
	}
	this->con_mutex.Unlock();
	if(!deleted)
	{
		printf_s("Item was not deleted: %u\n", item->guid);
	}
	else
	{
		printf_s("Item %u was deleted from instance container.\n", item->guid);
	}
}

bool LoadItem(DATA_ITEM* item, int guid)
{
	bool exist = false;
	Query* q = TestDB.query;
	if(item)
	{
		TestDB.db_mutex.Lock();
		q->get_result(AssembleQuery("SELECT `slot`, `type`, `level`, `durability`, `option1`, `option2`, `option3`, `newoption`, `setoption`, `petitem_level`, `petitem_exp`, `joh_option`, `optionex` FROM `character_items` WHERE `guid` = %d", guid));
		while(q->fetch_row())
		{
			exist = true;
			item->guid = guid;
			item->slot = q->getval();
			item->type = q->getval();
			item->level = q->getval();
			item->durability = q->getnum();
			item->option1 = q->getval();
			item->option2 = q->getval();
			item->option3 = q->getval();
			item->newoption = q->getval();
			item->setoption = q->getval();
			item->petitem_level = q->getval();
			item->petitem_exp = q->getval();
			item->joh_option = q->getval();
			item->optionex = q->getval();
			break;
		}
		q->free_result();
		TestDB.db_mutex.Unlock();
		if(exist)
		{
			return true;
		}
	}
	return false;
}