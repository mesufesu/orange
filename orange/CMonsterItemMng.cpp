#include "stdafx.h"
#include ".\\CMonsterItemMng.h"
#include ".\\CMonsterAttr.h"

CMonsterItemMng g_MonsterItemMng;

CMonsterItemMng::CMonsterItemMng()
{
}

CMonsterItemMng::~CMonsterItemMng()
{
	this->Clear();
}

void CMonsterItemMng::Init()
{
	ZeroMemory(&this->m_iMonsterInvenItemCount, sizeof(this->m_iMonsterInvenItemCount));
	for(int i = 0; i < MON_LEVELS; ++i)
	{
		CItem * pItems = new CItem[1000];
		this->m_MonsterInvenItems[i] = pItems;
	}
	for(int i = 0; i < MAX_UNITS; ++i) //хренота какаято мать их
	{
		MONSTER_ATTRIBUTE * lpm = gMAttr.GetAttr(i);
		if(lpm)
		{
			strcpy_s(this->MonsterName, sizeof(this->MonsterName), lpm->m_Name);
			if(lpm->m_Level)
			{
				this->gObjGiveItemSearch(lpm->m_Level, lpm->m_MaxItemLevel);
			}
		}
	}
}

void CMonsterItemMng::Clear()
{
	ZeroMemory(&this->m_iMonsterInvenItemCount, sizeof(this->m_iMonsterInvenItemCount));
	for(int i = 0; i < MON_LEVELS; ++i)
	{
		delete [] this->m_MonsterInvenItems[i];
	}
}

unsigned char CMonsterItemMng::InsertItem(int monsterlevel, int type, int index, int itemlevel, int op1, int op2, int op3)
{
	/*if(monsterlevel >= 0 && monsterlevel < MON_LEVELS)
	{
		int itemcount = this->m_iMonsterInvenItemCount[monsterlevel];
		if(itemcount < 1000)
		{
			CItem * item = &(this->m_MonsterInvenItems[monsterlevel])[itemcount];
			int item_type = index + 512 * type;
			item->m_Level = itemlevel;
			item->Convert(item_type, op1, op2, op3, 0, 0, 0, 3);
			if(type == 13 && index == 10)
			{
				item->m_Durability = (rand() % 100) + 100.0f;
			}
			else
			{
				item->m_Durability = item->m_BaseDurability;
			}
			itemcount++;
			this->m_iMonsterInvenItemCount[monsterlevel] = itemcount;
			return 0;
		}
		else
		{
			return -1;
		}
	}*/
	return -1;
}

CItem* CMonsterItemMng::GetItem(int monsterlevel)
{
	if(monsterlevel >= 0 && monsterlevel < 150)
	{
		int itemcount = this->m_iMonsterInvenItemCount[monsterlevel];
		if(itemcount > 0 && itemcount < 1000) //safe check
		{
			int itemindex = rand() % itemcount;
			return &((this->m_MonsterInvenItems[monsterlevel])[itemindex]);
		}
		else
		{
			return NULL;
		}
	}
	return NULL;
}

int MaxItemIndexOfEachType[16];

void CMonsterItemMng::gObjGiveItemSearch(int monsterlevel, int maxlevel)
{
	int incount = 0;
}