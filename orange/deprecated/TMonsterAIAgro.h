#ifndef __TMAA_H_
#define __TMAA_H_

class TMonsterAIAgroInfo
{
public:
  TMonsterAIAgroInfo();
  void Reset();
  int GetUserIndex();
  int GetAgroValue();
  void SetAgro(int iTargetIndex, int iValue);
  int IncAgro(int iIncValue);
  int DecAgro(int iDecValue);
private:
	  /*<thisrel this+0x0>*/ /*|0x4|*/ int m_iUserIndex;
	  /*<thisrel this+0x4>*/ /*|0x4|*/ int m_iAgroValue;
};
// <size 0x8>

class TMonsterAIAgro
{
public:
  /*<thisrel this+0x4>*/ /*|0x320|*/ TMonsterAIAgroInfo m_Agro[100];

  TMonsterAIAgro();
  void ResetAll();
  int _SetAgro(int iTargetIndex, int iValue);
  int DelAgro(int iTargetIndex);
  int GetAgro(int iTargetIndex);
  int IncAgro(int iTargetIndex, int iIncValue);
  int DecAgro(int iTargetIndex, int iDecValue);
  void DecAllAgro(int iDecValue);
  int GetMaxAgroUserIndex(int iMonsterIndex);

  virtual ~TMonsterAIAgro();
};
// <size 0x324>

#endif