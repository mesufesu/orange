#ifndef _CMONSTERSETBASE_H_
#define _CMONSTERSETBASE_H_

#include ".\\user.h"

enum _ARRANGETYPE
{
	STAND = 0,
	DEVIL_SQUARE = 1,
	GENERAL = 2,
	EVENT = 3,
	BLOOD_CASTLE = 4,
};

struct MONSTER_POSITION
{
  /*<thisrel this+0x0>*/ /*|0x1|*/ unsigned char m_ArrangeType;
  /*<thisrel this+0x2>*/ /*|0x2|*/ unsigned short m_Type;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char m_MapNumber;
  /*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char m_Dis;
  /*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char m_X;
  /*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char m_Y;
  /*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char m_Dir;
  /*<thisrel this+0x9>*/ /*|0x1|*/ unsigned char m_W;
  /*<thisrel this+0xa>*/ /*|0x1|*/ unsigned char m_H;
};
// <size 0xc

class CMonsterSetBase
{
public:
  /*<thisrel this+0x4>*/ /*|0x10fe0|*/ MONSTER_POSITION m_Mp[OBJ_MONSTER_MAX];
  /*<thisrel this+0x10fe4>*/ /*|0x4|*/ int m_Count;
public:
  void LoadSetBase(char* Buffer, int iSize);
  void LoadSetBase(char* filename);
  CMonsterSetBase();
  bool GetPosition(int TableNum, short MapNumber, short& x, short& y);
  bool GetBoxPosition(int mapnumber, int ax, int ay, int aw, int ah, short& mx, short& my);
  void SetBoxPosition(int TableNum, int mapnumber, int ax, int ay, int aw, int ah);

  virtual /*<vtableoff 0x0>*/ ~CMonsterSetBase();
};
// <size 0x10fe8>

extern CMonsterSetBase gMSetBase;

void GameMonsterAllAdd();

#endif