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

#ifndef _CMONSTERITEMMNG_H_
#define _CMONSTERITEMMNG_H_

#include ".\\Item.h"

#define MON_LEVELS 150

class CMonsterItemMng
{
public:
  /*<thisrel this+0x4>*/ /*|0x258|*/ CItem* m_MonsterInvenItems[MON_LEVELS];
  /*<thisrel this+0x25c>*/ /*|0x258|*/ int m_iMonsterInvenItemCount[MON_LEVELS];
  /*<thisrel this+0x4b4>*/ /*|0xff|*/ char MonsterName[255];

  CMonsterItemMng();
  void Init();
  void Clear();
  unsigned char InsertItem(int monsterlevel, int type, int index, int itemlevel, int op1, int op2, int op3);
  CItem* GetItem(int monsterlevel);
  void gObjGiveItemSearch(int monsterlevel, int maxlevel);

  virtual /*<vtableoff 0x0>*/ ~CMonsterItemMng();
};

extern CMonsterItemMng g_MonsterItemMng;
// <size 0x5b4>

#endif