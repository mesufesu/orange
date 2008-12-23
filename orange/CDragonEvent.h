#ifndef _CDRAGONEVENT_H_
#define _CDRAGONEVENT_H_

class CDragonEvent
{
public:
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char EventState;
  /*<thisrel this+0x8>*/ /*|0x4|*/ unsigned long EventStartTime;
  /*<thisrel this+0xc>*/ /*|0x1|*/ unsigned char m_MapNumber;
  /*<thisrel this+0x10>*/ /*|0x4|*/ bool m_bManualStart;

  CDragonEvent();
  unsigned char GetState();
  unsigned char GetMapNumber();
  void Init();
  void Start();
  void End();
  void Run();
  void DragonActive();
  void SetManualStart(bool bManualStart);
  void Start_Manual();
  void End_Manual();

  virtual /*<vtableoff 0x0>*/ ~CDragonEvent();
};
// <size 0x14>

extern CDragonEvent * pDragonEvent;

#endif