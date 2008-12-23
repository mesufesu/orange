#ifndef _CBATTLEGROUND_H_
#define _CBATTLEGROUND_H_

class CBattleGround
{
private:
  /*<thisrel this+0x4>*/ /*|0x9|*/ char m_szTeamName1[9];
  /*<thisrel this+0xd>*/ /*|0x9|*/ char m_szTeamName2[9];
  /*<thisrel this+0x18>*/ /*|0x4|*/ int m_Score1;
  /*<thisrel this+0x1c>*/ /*|0x4|*/ int m_Score2;
  /*<thisrel this+0x20>*/ /*|0xb|*/ char m_szID1[11];
  /*<thisrel this+0x2b>*/ /*|0xb|*/ char m_szID2[11];
  /*<thisrel this+0x38>*/ /*|0x10|*/ tagRECT m_rect;
  /*<thisrel this+0x48>*/ /*|0x4|*/ int m_Set;
  /*<thisrel this+0x4c>*/ /*|0x4|*/ int m_Type;
  /*<thisrel this+0x50>*/ /*|0x4|*/ bool m_Used;
  /*<thisrel this+0x54>*/ /*|0x4|*/ int m_MapNumber;
  /*<thisrel this+0x58>*/ /*|0x4|*/ int m_nTimer;
  /*<thisrel this+0x5c>*/ /*|0x4|*/ unsigned long m_dwCurTimer;

public:
  CBattleGround();
  void SetGroundRect(int map, int x, int y, int xl, int yl);
  void SetBattleType(int type);
  void Enable(bool enable);
  bool GetUsed();
  void SetTeamMaster(int n, char* szId);
  void SetTeamName(int n, char* szName);
  char* GetTeamName(int n);
  void SetTimer(int g_time);
  int GetTimer();
  int GetScore(int team);
  void SetScore(int team, int score);

  virtual /*<vtableoff 0x0>*/ ~CBattleGround();
};
// <size 0x60>

#endif