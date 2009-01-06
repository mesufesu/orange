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