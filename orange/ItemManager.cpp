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
	while(TRUE)
	{
		guid = rand();
		this->map_mutex.Lock();
		pr = this->ItemMap.insert(MapType::value_type(guid, new_item));
		this->map_mutex.Unlock();
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
		std::pair<MapType::iterator, bool> pr;
		this->map_mutex.Lock();
		pr = this->ItemMap.insert(MapType::value_type(guid, new_item));
		this->map_mutex.Unlock();
		if(pr.second == true)
		{
			return new_item;
		}
	}
	return NULL;
}

void CItemManager::DeleteItem(CItem *item)
{
	if(item)
	{
		this->map_mutex.Lock();
		this->ItemMap.erase(item->guid);
		this->map_mutex.Unlock();
	}
}

void CItemManager::DeleteItem(uint32 guid)
{
	if(guid)
	{
		this->map_mutex.Lock();
		this->ItemMap.erase(guid);
		this->map_mutex.Unlock();
	}
}

void CItemManager::CleanUp()
{
	this->map_mutex.Lock();
	for(MapType::iterator it = this->ItemMap.begin(); it != this->ItemMap.end(); ++it)
	{
		if(it->second && it->first)
		{
			switch(it->second->status)
			{
			case ITEM_DELETED:
				{
					break;
				}
			case ITEM_NOTEXIST:
				{
					break;
				}
			default:
				break;
			}
		}
	}
}

void WINAPI CItemManager::ItemProc(CItemManager* mang)
{
	uint32 tick_count = GetTickCount();
	while(TRUE)
	{
		if((GetTickCount() - tick_count) >= 5000)
		{
			mang->CleanUp();
		}
		Sleep(1000);
	}
}

void CItemManager::Run()
{
	uint32 id;
	this->procHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CItemManager::ItemProc, (LPVOID)this, 0, (LPDWORD)&id);
}

bool CItemManager::LoadItem(DATA_ITEM* item, int guid)
{
	bool exist = false;
	QSqlQuery q;
	if(item)
	{
		MainDB.Lock();
		q.prepare("SELECT `slot`, `type`, `level`, `durability`, `option1`, `option2`, `option3`, `newoption`, `setoption`, `petitem_level`, `petitem_exp`, `joh_option`, `optionex` FROM `character_items` WHERE `guid` = :guid;");
		q.bindValue(":guid", guid);
		q.exec();
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
	QSqlQuery q;
	bool result = false;
	switch(item->status)
	{
	case ITEM_NEW:
		{
			uint32 new_guid = item->guid;
			MainDB.Lock();
			while(TRUE)
			{
				q.prepare("SELECT `id` FROM `character_items` WHERE `guid` = ':guid'");
				q.bindValue(":guid", new_guid);
				result = q.exec();
				uint32 count = 0;
				while(q.next())
				{
					count++;
				}
				if(count == 0)
				{
					break;
				}
				else
				{
					while(TRUE)
					{
						new_guid = rand();
						this->map_mutex.Lock();
						MapType::iterator it = this->ItemMap.find(new_guid);
						this->map_mutex.Unlock();
						if(it == this->ItemMap.end())
						{
							break;
						}
					}
				}
			}
			MainDB.Unlock();
			this->map_mutex.Lock();
			this->ItemMap.erase(this->ItemMap.find(item->guid));
			item->guid = new_guid;
			this->ItemMap.insert(MapType::value_type(new_guid, item));
			this->map_mutex.Unlock();
			MainDB.Lock();
			q.prepare("INSERT IGNORE INTO `character_items` (`guid`, `slot`, `type`, `level`, `durability`, `option1`, `option2`, `option3`, `newoption`, `setoption`, `petitem_level`, `petitem_exp`, `joh_option`, `optionex`) VALUES (:guid, :slot, :type, :level, :durability, :option1, :option2, :option3, :newoption, :setoption, :petlevel, :petexp, :joh, :optionex);");
			q.bindValue(":guid", item->guid);
			q.bindValue(":slot", slot);
			q.bindValue(":type", item->type);
			q.bindValue(":level", item->level);
			q.bindValue(":durability", item->durability);
			q.bindValue(":option1", item->m_Option1);
			q.bindValue(":option2", item->m_Option2);
			q.bindValue(":option3", item->m_Option3);
			q.bindValue(":newoption", item->m_NewOption);
			q.bindValue(":setoption", item->m_SetOption);
			q.bindValue(":petlevel", item->m_PetItem_Level);
			q.bindValue(":petexp", item->m_PetItem_Exp);
			q.bindValue(":joh", item->m_JewelOfHarmonyOption);
			q.bindValue(":optionex", item->m_ItemOptionEx);
			result = q.exec();
			MainDB.Unlock();
			item->status = ITEM_UNCHANGED;
			break;
		}
	case ITEM_CHANGED:
		{
			MainDB.Lock();
			q.prepare("UPDATE `character_items` SET `slot` = :slot, `type` = :type, `level` = :level, `durability` = :durability, `option1` = :option1, `option2` = :option2, `option3` = :option3, `newoption` = :newoption, `setoption` = :setoption, `petitem_level` = :petlevel, `petitem_exp` = :petexp, `joh_option` = :joh, `optionex` = :optionex WHERE `guid` = :guid;");
			q.bindValue(":slot", slot);
			q.bindValue(":type", item->type);
			q.bindValue(":level", item->level);
			q.bindValue(":durability", item->durability);
			q.bindValue(":option1", item->m_Option1);
			q.bindValue(":option2", item->m_Option2);
			q.bindValue(":option3", item->m_Option3);
			q.bindValue(":newoption", item->m_NewOption);
			q.bindValue(":setoption", item->m_SetOption);
			q.bindValue(":petlevel", item->m_PetItem_Level);
			q.bindValue(":petexp", item->m_PetItem_Exp);
			q.bindValue(":joh", item->m_JewelOfHarmonyOption);
			q.bindValue(":optionex", item->m_ItemOptionEx);
			q.bindValue(":guid", item->guid);
			result = q.exec();
			MainDB.Unlock();
			break;
		}
	default:
		break;
	}
	if(!result)
	{
		printf_s("Save item %u failed: %u.\n", item->guid, q.lastError().type());
		return false;
	}
	return true;
}