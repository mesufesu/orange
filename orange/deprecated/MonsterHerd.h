#ifndef __MONSTERHERD_H_
#define __MONSTERHERD_H

struct _MONSTER_HERD_DATA
{
  /*<thisrel this+0x0>*/ /*|0x4|*/ int m_iIndex;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int m_iType;
  /*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char m_iX;
  /*<thisrel this+0x9>*/ /*|0x1|*/ unsigned char m_iY;
  /*<thisrel this+0xc>*/ /*|0x4|*/ int m_bRegen;
  _MONSTER_HERD_DATA();
};
// <size 0x10>

class MonsterHerd
{
public:
  /*<thisrel this+0x4>*/ /*|0x4|*/ int m_iHerdIndex;
  /*<thisrel this+0x8>*/ /*|0x4|*/ int m_iMapNumber;
  /*<thisrel this+0xc>*/ /*|0x4|*/ int m_iCUR_X;
  /*<thisrel this+0x10>*/ /*|0x4|*/ int m_iCUR_Y;
  /*<thisrel this+0x14>*/ /*|0x4|*/ int m_iRADIUS;
  /*<thisrel this+0x18>*/ /*|0x4|*/ int m_bHasInfo;
  /*<thisrel this+0x1c>*/ /*|0x4|*/ int m_bHerdActive;
  /*<thisrel this+0x20>*/ /*|0x10|*/ char m_mapMonsterHerd[0x10];//std::map<int,_MONSTER_HERD_DATA> m_mapMonsterHerd;
  /*<thisrel this+0x30>*/ /*|0x18|*/ CRITICAL_SECTION m_critMonsterHerd;
  MonsterHerd();

  // virtual functions ------------------------------
  virtual /*<vtableoff 0x0>*/ ~MonsterHerd();
};
// <size 0x48>

#endif