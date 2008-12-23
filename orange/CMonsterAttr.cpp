#include "stdafx.h"
#include ".\\CMonsterAttr.h"

CMonsterAttr gMAttr;

CMonsterAttr::CMonsterAttr()
{
	ZeroMemory(&this->m_MonsterAttr, sizeof(this->m_MonsterAttr));
}

CMonsterAttr::~CMonsterAttr()
{
}

MONSTER_ATTRIBUTE* CMonsterAttr::GetAttr(int aClass)
{
	for(int i = 0; i < MAX_UNITS; ++i)
	{
		if(this->m_MonsterAttr[i].m_Index == aClass)
		{
			return &this->m_MonsterAttr[i];
		}
	}
	return NULL;
}