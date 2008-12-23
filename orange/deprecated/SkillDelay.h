#ifndef __SKILLDELAY_H_
#define __SKILLDELAY_H_

class CSkillDelay
{
public:
  /*<thisrel this+0x4>*/ /*|0x400|*/ unsigned long LastSkillUseTime[256];

  CSkillDelay();
  void Init();
  int Check(unsigned char skill);

  virtual ~CSkillDelay();
};
// <size 0x404>

#endif