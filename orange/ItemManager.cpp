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

#include "stdafx.h"
#include ".\\utils.h"
#include ".\\DataBase.h"
#include ".\\ItemManager.h"

CItemManager ItemManager;

CItemManager::CItemManager()
{
	this->ItemMap.clear();
}

const CItem* CItemManager::CreateItem()
{
	std::pair<MapType::iterator, bool> pr;
	uint32 guid = 0;
	CItem* new_item = new CItem;
	if(!new_item)
	{
		return NULL;
	}
	while(TRUE)
	{
		guid = rand();
		this->map_mutex.lock();
		pr = this->ItemMap.insert(MapType::value_type(guid, new_item));
		this->map_mutex.unlock();
		if(pr.second == true)
		{
			new_item->guid = guid;
			new_item->status = ITEM_NEW;
			return new_item;
		}
	}
	return NULL;
}

CItem* CItemManager::InsertItem(uint32 guid)
{
	if(guid)
	{
		CItem* new_item = new CItem;
		if(!new_item)
		{
			return NULL;
		}
		std::pair<MapType::iterator, bool> pr;
		this->map_mutex.lock();
		pr = this->ItemMap.insert(MapType::value_type(guid, new_item));
		this->map_mutex.unlock();
		if(pr.second == true)
		{
			return new_item;
		}
	}
	return NULL;
}

void CItemManager::CleanUp()
{
	std::vector<MapType::iterator> list;
	list.clear();
	this->map_mutex.lock();
	for(MapType::iterator it = this->ItemMap.begin(); it != this->ItemMap.end(); ++it)
	{
		if(it->second && it->first)
		{
			switch(it->second->status)
			{
			case ITEM_DELETED:
				{
					list.push_back(it);
					QSqlQuery q;
					MainDB.Lock();
					q.exec(Query("DELETE FROM `character_items` WHERE `guid` = %u;", it->second->guid).c_str());
					MainDB.Unlock();
					CItem * item = it->second;
					delete item;
					break;
				}
			case ITEM_NOTEXIST:
				{
					list.push_back(it);
					CItem * item = it->second;
					delete item;
					break;
				}
			default:
				break;
			}
		}
	}
	for(uint32 i = 0; i < list.size(); ++i)
	{
		this->ItemMap.erase(list.at(i));
	}
	this->map_mutex.unlock();
}

void CItemThread::run()
{
	int32 tick_count = GetTickCount();
	while(TRUE)
	{
		if((GetTickCount() - tick_count) >= 5000)
		{
			ItemManager.CleanUp();
		}
		Sleep(1000);
	}
}

void CItemManager::Run()
{
	this->ItemThread.start();
}

void CItemManager::Quit()
{
	this->ItemThread.quit();
}

bool CItemManager::HaveGuid(uint32 guid)
{
	this->map_mutex.lock();
	MapType::iterator it = this->ItemMap.find(guid);
	this->map_mutex.unlock();
	if(it != this->ItemMap.end())
	{
		return true;
	}
	return false;
}

bool CItemManager::LoadItemData(DATA_ITEM* item, int guid)
{
	bool exist = false;
	QSqlQuery q;
	if(item)
	{
		MainDB.Lock();
		q.exec(Query("SELECT `slot`, `type`, `level`, `durability`, `option1`, `option2`, `option3`, `newoption`, `setoption`, `petitem_level`, `petitem_exp`, `joh_option`, `optionex` FROM `character_items` WHERE `guid` = %u;", guid).c_str());
		while(q.next())
		{
			exist = true;
			item->guid = guid;
			item->slot = q.value(0).toInt();
			item->type = q.value(1).toInt();
			item->level = q.value(2).toInt();
			item->durability = q.value(3).toDouble();
			item->option1 = q.value(4).toInt();
			item->option2 = q.value(5).toInt();
			item->option3 = q.value(6).toInt();
			item->newoption = q.value(7).toInt();
			item->setoption = q.value(8).toInt();
			item->petitem_level = q.value(9).toInt();
			item->petitem_exp = q.value(10).toInt();
			item->joh_option = q.value(11).toInt();
			item->optionex = q.value(12).toInt();
			break;
		}
		MainDB.Unlock();
		if(exist)
		{
			return true;
		}
	}
	return false;
}

/*bool CItemManager::Instanciate(const CItem* item)
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
}*/

bool CItemManager::SaveItem(CItem *item, uint32 slot)
{
	uint32 old_guid = item->guid;
	QSqlQuery q;
	bool result = false;
	switch(item->status)
	{
	case ITEM_CHANGED:
		{
			MainDB.Lock();
			result = q.exec(Query("UPDATE `character_items` SET `slot` = %u, `type` = %u, `level` = %u, `durability` = %f, `option1` = %u, `option2` = %u, `option3` = %u, `newoption` = %u, `setoption` = %u, `petitem_level` = %u, `petitem_exp` = %u, `joh_option` = %u, `optionex` = %u WHERE `guid` = %u;", slot, item->type, item->level, item->durability, item->m_Option1, item->m_Option2, item->m_Option3, item->m_NewOption, item->m_SetOption, item->m_PetItem_Level, item->m_PetItem_Exp, item->m_JewelOfHarmonyOption, item->m_ItemOptionEx, item->guid).c_str());
			MainDB.Unlock();
			item->status = ITEM_UNCHANGED;
			break;
		}
	case ITEM_NEW:
		{
			uint32 new_guid = old_guid;
			MainDB.Lock();
			while(TRUE)
			{
				result = q.exec(Query("SELECT `id` FROM `character_items` WHERE `guid` = %u;", new_guid).c_str());
				uint32 count = 0;
				while(q.next())
				{
					count++;
				}
				if((count == 0) && (new_guid == old_guid ? true : (!this->HaveGuid(new_guid))))
				{
					break;
				}
				else
				{
					new_guid = rand();
				}
			}
			MainDB.Unlock();
			this->map_mutex.lock();
			//this->ItemMap.erase(this->ItemMap.find(item->guid));
			this->ItemMap.erase(item->guid);
			item->guid = new_guid;
			this->ItemMap.insert(MapType::value_type(new_guid, item));
			this->map_mutex.unlock();
			MainDB.Lock();
			result = q.exec(Query("INSERT IGNORE INTO `character_items` (`guid`, `slot`, `type`, `level`, `durability`, `option1`, `option2`, `option3`, `newoption`, `setoption`, `petitem_level`, `petitem_exp`, `joh_option`, `optionex`) VALUES (%u, %u, %u, %u, %f, %u, %u, %u, %u, %u, %u, %u, %u, %u);", item->guid, slot, item->type, item->level, item->durability, item->m_Option1, item->m_Option2, item->m_Option3, item->m_NewOption, item->m_SetOption, item->m_PetItem_Level, item->m_PetItem_Exp, item->m_JewelOfHarmonyOption, item->m_ItemOptionEx).c_str());
			MainDB.Unlock();
			item->status = ITEM_UNCHANGED;
			break;
		}
	default:
		break;
	}
	if(!result)
	{
		Log.String("Save item %u failed: %u.", item->guid, q.lastError().type());
		return false;
	}
	return true;
}

bool CItemManager::DeleteFromDB(uint32 guid)
{
	if(guid < 0)
	{
		return false;
	}
	QSqlQuery q;
	MainDB.Lock();
	bool result = q.exec(Query("DELETE FROM `character_items` WHERE `guid` = %u;", guid).c_str());
	MainDB.Unlock();
	return result;
}