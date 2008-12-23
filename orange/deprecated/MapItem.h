#ifndef MAPITEM_H__
#define MAPITEM_H__

#include "..\\user.h"

class CMapItem : public CItem
{
public:
  /*<thisrel this+0xb4>*/ /*|0x1|*/ unsigned char px;
  /*<thisrel this+0xb5>*/ /*|0x1|*/ unsigned char py;
  /*<thisrel this+0xb6>*/ /*|0x1|*/ unsigned char live;
  /*<thisrel this+0xb7>*/ /*|0x1|*/ unsigned char Give;
  /*<thisrel this+0xb8>*/ /*|0x4|*/ unsigned long m_State;
  /*<thisrel this+0xbc>*/ /*|0x4|*/ unsigned long m_Time;
  /*<thisrel this+0xc0>*/ /*|0x4|*/ int m_UserIndex;
  /*<thisrel this+0xc4>*/ /*|0x4|*/ unsigned long m_LootTime;
  /*<thisrel this+0xc8>*/ /*|0x384|*/ VIEWPORT_PLAYER_STRUCT VpPlayer[75];
  /*<thisrel this+0x44c>*/ /*|0x4|*/ int VPCount;

  // baseclass class CItem
  // <base data offset+0x4>
  CMapItem(void);
  void Init();
  void CreateItem(int type, int level, int x, int y, float dur, unsigned char Option1, unsigned char Option2, unsigned char Option3, unsigned char NOption, unsigned char SOption, unsigned long number, unsigned char ItemEffectEx);
  void DropCreateItem(int type, int level, int x, int y, float dur, unsigned char Option1, unsigned char Option2, unsigned char Option3, unsigned char NOption, unsigned char SOption, unsigned long number, int PetLevel, int PetExp, unsigned char ItemEffectEx);
  // virtual functions ------------------------------
  virtual /*<vtableoff 0x0>*/ ~CMapItem(void);
};
// <size 0x450>

#endif