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

bool CItemManager::SaveItem(CItem *item, uint32 slot)
{
	Query* q = TestDB.query;
	bool result = false;
	if(item->new_item == true)
	{
		uint32 new_guid = item->guid;
		while(TRUE)
		{
			TestDB.db_mutex.Lock();
			q->get_result(AssembleQuery("SELECT `id` FROM `character_items` WHERE `guid` = '%d'", new_guid));
			if(q->num_rows() == 0)
			{
				break;
			}
			else
			{
				new_guid = rand();
			}
			q->free_result();
			TestDB.db_mutex.Unlock();
		}
		this->DeleteInstance(item);
		item->guid = new_guid;
		this->Instanciate(item);
		TestDB.db_mutex.Lock();
		result = q->execute(AssembleQuery("INSERT IGNORE INTO `character_items` (`guid`, `slot`, `type`, `level`, `durability`, `option1`, `option2`, `option3`, `newoption`, `setoption`, `petitem_level`, `petitem_exp`, `joh_option`, `optionex`) VALUES (%u, %u, %u, %u, %f, %u, %u, %u, %u, %u, %u, %u, %u, %u);", item->guid, slot, item->type, item->level, item->durability, item->m_Option1, item->m_Option2, item->m_Option3, item->m_NewOption, item->m_SetOption, item->m_PetItem_Level, item->m_PetItem_Exp, item->m_JewelOfHarmonyOption, item->m_ItemOptionEx));
		TestDB.db_mutex.Unlock();
		item->new_item = false;
	}
	else
	{
		TestDB.db_mutex.Lock();
		result = q->execute(AssembleQuery("UPDATE `character_items` SET `slot` = %u, `type` = %u, `level` = %u, `durability` = %f, `option1` = %u, `option2` = %u, `option3` = %u, `newoption` = %u, `setoption` = %u, `petitem_level` = %u, `petitem_exp` = %u, `joh_option` = %u, `optionex` = %u WHERE `guid` = %u;", item->guid, slot, item->type, item->level, item->durability, item->m_Option1, item->m_Option2, item->m_Option3, item->m_NewOption, item->m_SetOption, item->m_PetItem_Level, item->m_PetItem_Exp, item->m_JewelOfHarmonyOption, item->m_ItemOptionEx, item->guid));
		TestDB.db_mutex.Unlock();
	}
	if(!result)
	{
		printf_s("Save item failed %u.\n", item->guid);
		return false;
	}
	return true;
}