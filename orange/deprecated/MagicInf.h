#ifndef __MAGICINF_H_
#define __MAGICINF_H_

class CMagicInf
{
public:
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char m_Level;
  /*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char m_Skill;
  /*<thisrel this+0x8>*/ /*|0x4|*/ int m_DamageMin;
  /*<thisrel this+0xc>*/ /*|0x4|*/ int m_DamageMax;

  CMagicInf();
  int IsMagic();
  void Init();
  void Clear();
  int Set(unsigned char aSkill, unsigned char aLevel);
  int Set(unsigned char aType, unsigned char aIndex, unsigned char aLevel);
  int GetDamage();
  virtual ~CMagicInf();
};

class TDurMagicKeyChecker
{
public:
  /*<thisrel this+0x0>*/ /*|0xf0|*/ unsigned long m_dwDurationTime[60];
  /*<thisrel this+0xf0>*/ /*|0x3c|*/ unsigned char m_btValidCount[60];

  int IsValidDurationTime(unsigned char btMagicKey);
  int IsValidCount(unsigned char btMagicKey);
  void SetDurationTime(unsigned char btMagicKey, unsigned long dwCurrentTickCount);
  unsigned char DecValidCount(unsigned char);
  int GetValidDurationTime(unsigned char btMagicKey);
  int GetValidCount(unsigned char btMagicKey);
};
// <size 0x12c

#endif