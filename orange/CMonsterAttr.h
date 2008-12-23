#ifndef _CMONSTERATTR_H_
#define _CMONSTERATTR_H_

#define MAX_UNITS 512

struct MONSTER_ATTRIBUTE
{
  /*<thisrel this+0x0>*/ /*|0x4|*/ int m_Index;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int m_Rate;
  /*<thisrel this+0x8>*/ /*|0x14|*/ char m_Name[20];
  /*<thisrel this+0x1c>*/ /*|0x4|*/ int m_Level;
  /*<thisrel this+0x20>*/ /*|0x4|*/ int m_iAINumber;
  /*<thisrel this+0x24>*/ /*|0x4|*/ int m_iScriptHP;
  /*<thisrel this+0x28>*/ /*|0x4|*/ int m_Hp;
  /*<thisrel this+0x2c>*/ /*|0x4|*/ int m_Mp;
  /*<thisrel this+0x30>*/ /*|0x4|*/ int m_DamageMin;
  /*<thisrel this+0x34>*/ /*|0x4|*/ int m_DamageMax;
  /*<thisrel this+0x38>*/ /*|0x4|*/ int m_Defense;
  /*<thisrel this+0x3c>*/ /*|0x4|*/ int m_MagicDefense;
  /*<thisrel this+0x40>*/ /*|0x4|*/ int m_AttackRating;
  /*<thisrel this+0x44>*/ /*|0x4|*/ int m_Successfulblocking;
  /*<thisrel this+0x48>*/ /*|0x4|*/ int m_MoveRange;
  /*<thisrel this+0x4c>*/ /*|0x4|*/ int m_AttackRange;
  /*<thisrel this+0x50>*/ /*|0x4|*/ int m_AttackType;
  /*<thisrel this+0x54>*/ /*|0x4|*/ int m_ViewRange;
  /*<thisrel this+0x58>*/ /*|0x4|*/ int m_MoveSpeed;
  /*<thisrel this+0x5c>*/ /*|0x4|*/ int m_AttackSpeed;
  /*<thisrel this+0x60>*/ /*|0x4|*/ int m_RegenTime;
  /*<thisrel this+0x64>*/ /*|0x4|*/ int m_Attribute;
  /*<thisrel this+0x68>*/ /*|0x4|*/ int m_ItemRate;
  /*<thisrel this+0x6c>*/ /*|0x4|*/ int m_MoneyRate;
  /*<thisrel this+0x70>*/ /*|0x4|*/ int m_MaxItemLevel;
  /*<thisrel this+0x74>*/ /*|0x7|*/ unsigned char m_Resistance[7];
  /*<thisrel this+0x7c>*/ /*|0x4|*/ unsigned long m_MonsterSkill;
};
// <size 0x80>

class CMonsterAttr
{
private:
  /*<thisrel this+0x4>*/ /*|0x10000|*/ MONSTER_ATTRIBUTE m_MonsterAttr[MAX_UNITS];
public:
  MONSTER_ATTRIBUTE* GetAttr(int aClass);
  void LoadAttr(char* Buffer, int iSize);
  void LoadAttr(char* filename);
  CMonsterAttr();

  virtual /*<vtableoff 0x0>*/ ~CMonsterAttr();
};
// <size 0x10004>

extern CMonsterAttr gMAttr;

#endif