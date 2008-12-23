#ifndef __CSAUTH_H_
#define __CSAUTH_H_

struct _GG_AUTH_PROTOCOL
{
};
// <size 0x0>

struct _GG_AUTH_DATA
{
  /*<thisrel this+0x0>*/ /*|0x4|*/ unsigned long dwIndex;
  /*<thisrel this+0x4>*/ /*|0x4|*/ unsigned long dwValue1;
  /*<thisrel this+0x8>*/ /*|0x4|*/ unsigned long dwValue2;
  /*<thisrel this+0xc>*/ /*|0x4|*/ unsigned long dwValue3;
};
// <size 0x10>

class CCSAuth2
{
public:
  /*<thisrel this+0x0>*/ /*|0x4|*/ _GG_AUTH_PROTOCOL* m_pProtocol;
  /*<thisrel this+0x4>*/ /*|0x4|*/ unsigned long m_bPrtcRef;
  /*<thisrel this+0x8>*/ /*|0x4|*/ unsigned long m_dwUserFlag;
  /*<thisrel this+0xc>*/ /*|0x10|*/ _GG_AUTH_DATA m_AuthQuery;
  /*<thisrel this+0x1c>*/ /*|0x10|*/ _GG_AUTH_DATA m_AuthAnswer;
  CCSAuth2();
  ~CCSAuth2();
  void Init();
  unsigned long GetAuthQuery();
  unsigned long CheckAuthAnswer();
};
// <size 0x2c>

#endif