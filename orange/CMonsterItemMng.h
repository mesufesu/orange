#ifndef _CMONSTERITEMMNG_H_
#define _CMONSTERITEMMNG_H_

#include ".\\deprecated\\zzzitem.h"

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