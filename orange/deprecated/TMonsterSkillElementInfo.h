#ifndef __TMSEI_H_
#define __TMSEI_H_

class TMonsterSkillElementInfo
{
public:
  /*<thisrel this+0x0>*/ /*|0x4|*/ int m_iSkillElementDefense;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int m_iSkillElementDefenseTime;
  /*<thisrel this+0x8>*/ /*|0x4|*/ int m_iSkillElementAttack;
  /*<thisrel this+0xc>*/ /*|0x4|*/ int m_iSkillElementAttackTime;
  /*<thisrel this+0x10>*/ /*|0x4|*/ int m_iSkillElementAutoHP;
  /*<thisrel this+0x14>*/ /*|0x4|*/ int m_iSkillElementAutoHPCycle;
  /*<thisrel this+0x18>*/ /*|0x4|*/ int m_iSkillElementAutoHPTime;
  /*<thisrel this+0x1c>*/ /*|0x4|*/ int m_iSkillElementAutoMP;
  /*<thisrel this+0x20>*/ /*|0x4|*/ int m_iSkillElementAutoMPCycle;
  /*<thisrel this+0x24>*/ /*|0x4|*/ int m_iSkillElementAutoMPTime;
  /*<thisrel this+0x28>*/ /*|0x4|*/ int m_iSkillElementAutoAG;
  /*<thisrel this+0x2c>*/ /*|0x4|*/ int m_iSkillElementAutoAGCycle;
  /*<thisrel this+0x30>*/ /*|0x4|*/ int m_iSkillElementAutoAGTime;
  /*<thisrel this+0x34>*/ /*|0x4|*/ int m_iSkillElementImmuneNumber;
  /*<thisrel this+0x38>*/ /*|0x4|*/ int m_iSkillElementImmuneTime;
  /*<thisrel this+0x3c>*/ /*|0x4|*/ int m_iSkillElementResistNumber;
  /*<thisrel this+0x40>*/ /*|0x4|*/ int m_iSkillElementResistTime;
  /*<thisrel this+0x44>*/ /*|0x4|*/ int m_iSkillElementModifyStat;
  /*<thisrel this+0x48>*/ /*|0x4|*/ int m_iSkillElementModifyStatType;
  /*<thisrel this+0x4c>*/ /*|0x4|*/ int m_iSkillElementModifyStatTime;

  //static void CheckSkillElementInfoProc(OBJECTSTRUCT* lpObj);

  TMonsterSkillElementInfo();
  void Reset();
  void ResetDefense();
  void ResetAttack();
  void ResetAutoHP();
  void ResetAutoMP();
  void ResetAutoAG();
  void ResetImmune();
  void ResetResist();
  void ResetModifyStat();
  int CheckDefenseTime();
  int CheckAttackTime();
  int CheckAutoHPTime();
  int CheckAutoMPTime();
  int CheckAutoAGTime();
  int CheckImmuneTime();
  int CheckResistTime();
  int CheckModifyStatTime();
  int DecDefenseTime();
  int DecAttackTime();
  int DecAutoHPTime();
  int DecAutoMPTime();
  int DecAutoAGTime();
  int DecImmuneTime();
  int DecResistTime();
  int DecModifyStatTime();

};
// <size 0x50>

#endif