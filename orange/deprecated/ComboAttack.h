#ifndef __COMBOATTACK_H_
#define __COMBOATTACK_H_

struct ComboSkillData
{
  /*<thisrel this+0x0>*/ /*|0x4|*/ unsigned long dwTime;
  /*<thisrel this+0x4>*/ /*|0x3|*/ unsigned char Skill[3];
  /*<thisrel this+0x8>*/ /*|0x4|*/ int ProgressIndex;

  void Init();
};
// <size 0xc>

struct tagActionState
{
  /*<bitfield this+0x0>*/ /*|0x4|*/ unsigned long Rest:1;
  /*<bitfield this+0x0>*/ /*|0x4|*/ unsigned long Attack:1;
  /*<bitfield this+0x0>*/ /*|0x4|*/ unsigned long Move:1;
  /*<bitfield this+0x0>*/ /*|0x4|*/ unsigned long Escape:1;
  /*<bitfield this+0x0>*/ /*|0x4|*/ unsigned long Emotion:4;
  /*<bitfield this+0x0>*/ /*|0x4|*/ unsigned long EmotionCount:8;

};
// <size 0x4>


#endif