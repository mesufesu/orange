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
#include "DataBase.h"
#include "ItemManager.h"

CItemManager ItemManager;

CItemManager::CItemManager()
{
	this->ItemMap.clear();
}

CItem* const CItemManager::CreateItem()
{
	std::pair<MapType::iterator, bool> pr;
	uint32 guid = 0;
	CItem* new_item = NULL;
	if(!new_item)
	{
		return NULL;
	}
	uint32 count = 0;
	this->rwl.lockForWrite();
	while(true && count < 0x0fffffff)
	{
		guid = rand();
		pr = this->ItemMap.insert(MapType::value_type(guid, new_item));
		if(pr.second == true)
		{
			pr.first->second = new CItem;
			new_item = pr.first->second;
			new_item->guid = guid;
			new_item->status = ITEM_NEW;
			break;
		}
		++count;
	}
	this->rwl.unlock();
	return new_item;
}

void CItemManager::CleanUp()
{
	MapType::iterator it;
	this->rwl.lockForWrite();
	for(it = this->ItemMap.begin(); it != this->ItemMap.end(); true)
	{
		MapType::iterator current = it;
		++it;
		if(current->second)
		{
			switch(current->second->status)
			{
			case ITEM_DELETED:
				{
					if(current->second->dbuid)
					{
						QSqlQuery q(accounts_db.db);
						accounts_db.LockForWrite();
						q.exec(Query("DELETE FROM `character_items` WHERE `dbuid` = %u;", it->second->dbuid).c_str());
						accounts_db.Unlock();
					}
					CItem* item = current->second;
					delete item;
					break;
				}
			}
		}
	}
	this->rwl.unlock();
}

void CItemThread::run()
{
	CTimer timer(10 * SECOND);
	while(true)
	{
		if(timer.Passed())
		{
			ItemManager.CleanUp();
		}
		this->msleep(SECOND);
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
	bool ret = false;
	this->rwl.lockForRead();
	MapType::iterator it = this->ItemMap.find(guid);
	if(it != this->ItemMap.end())
	{
		ret = true;
	}
	this->rwl.unlock();
	return ret;
}

bool CItemManager::LoadItemData(DATA_ITEM* item, int dbuid)
{
	bool exist = false;
	QSqlQuery q(accounts_db.db);
	if(item)
	{
		accounts_db.LockForRead();
		q.exec(Query("SELECT `slot`, `type`, `level`, `durability`, `option1`, `option2`, `option3`, `newoption`, `setoption`, `petitem_level`, `petitem_exp`, `joh_option`, `optionex` FROM `character_items` WHERE `guid` = %u;", dbuid).c_str());
		while(q.next())
		{
			exist = true;
			item->dbuid = dbuid;
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
		accounts_db.Unlock();
		if(exist)
		{
			return true;
		}
	}
	return false;
}

bool CItemManager::SaveItem(CItem *item, uint32 slot)
{
	QSqlQuery q(accounts_db.db);
	bool result = false;
	switch(item->status)
	{
	case ITEM_CHANGED:
		{
			accounts_db.LockForWrite();
			result = q.exec(Query("UPDATE `character_items` SET `slot` = %u, `type` = %u, `level` = %u, `durability` = %f, `option1` = %u, `option2` = %u, `option3` = %u, `newoption` = %u, `setoption` = %u, `petitem_level` = %u, `petitem_exp` = %u, `joh_option` = %u, `optionex` = %u WHERE `dbuid` = %u;", slot, item->type, item->level, item->durability, item->option1, item->option2, item->option3, item->option_new, item->m_SetOption, item->m_PetItem_Level, item->m_PetItem_Exp, item->m_JewelOfHarmonyOption, item->m_ItemOptionEx, item->dbuid).c_str());
			accounts_db.Unlock();
			item->status = ITEM_UNCHANGED;
			break;
		}
	case ITEM_NEW:
		{
			init_genrand(GetTicks());
			accounts_db.LockForWrite();
			uint32 ncount = 0;
			uint32 temp_dbuid = 0;
			while(ncount < RETRIES)
			{
				++ncount;
				temp_dbuid = genrand_int32();
				result = q.exec(Query("SELECT `id` FROM `character_items` WHERE `dbuid` = %u;", temp_dbuid).c_str());
				assert(result);
				if(!q.next())
				{
					break;
				}
			}
			assert(ncount != 0x0fffffff);
			item->dbuid = temp_dbuid;
			result = q.exec(Query("INSERT IGNORE INTO `character_items` (`dbuid`, `slot`, `type`, `level`, `durability`, `option1`, `option2`, `option3`, `newoption`, `setoption`, `petitem_level`, `petitem_exp`, `joh_option`, `optionex`) VALUES (%u, %u, %u, %u, %f, %u, %u, %u, %u, %u, %u, %u, %u, %u);", item->dbuid, slot, item->type, item->level, item->durability, item->option1, item->option2, item->option3, item->option_new, item->m_SetOption, item->m_PetItem_Level, item->m_PetItem_Exp, item->m_JewelOfHarmonyOption, item->m_ItemOptionEx).c_str());
			assert(result);
			item->status = ITEM_UNCHANGED;
			accounts_db.Unlock();
		}
	default:
		break;
	}
	if(!result)
	{
		Log.String("Save item %u db: %u failed: %u.", item->guid, item->dbuid, q.lastError().type());
		return false;
	}
	return true;
}

bool CItemManager::DeleteFromDB(uint32 dbuid)
{
	QSqlQuery q(accounts_db.db);
	accounts_db.LockForWrite();
	bool result = q.exec(Query("DELETE FROM `character_items` WHERE `dbuid` = %u;", dbuid).c_str());
	accounts_db.Unlock();
	return result;
}