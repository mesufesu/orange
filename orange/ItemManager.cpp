#include "stdafx.h"
#include ".\\DataBase.h"
#include ".\\ItemManager.h"

CItemManager::CItemManager()
{
	this->item_guids.clear();
}

void CItemManager::LoadCharacterItems()
{
}

bool LoadItem(DATA_ITEM* item, int guid)
{
	bool exist = false;
	Query* q = TestDB.query;
	if(item)
	{
		TestDB.db_mutex.Lock();
		q->get_result(TestDB.AssembleQuery("SELECT `slot`, `type`, `level`, `durability`, `option1`, `option2`, `option3`, `newoption`, `setoption`, `setaddstat`, `petitem_level`, `petitem_exp`, `joh_option`, `joh_strength`, `joh_dexterity`, `optionex` FROM `character_items` WHERE `guid` = %d", guid));
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
			item->setaddstat = q->getval();
			item->petitem_level = q->getval();
			item->petitem_exp = q->getval();
			item->joh_option = q->getval();
			item->joh_strength = q->getval();
			item->joh_dexterity = q->getval();
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