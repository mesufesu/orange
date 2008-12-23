#ifndef _DSERVERCLI_H_
#define _DSERVERCLI_H_

#include ".\\WinsockBase.h"

class DServerCli : public WinsockBase
{
private:
  /*<thisrel this+0x1c>*/ /*|0xc8000|*/ unsigned char m_SendBuf[819200];
  /*<thisrel this+0xc801c>*/ /*|0x4|*/ int m_SendBufLen;
  /*<thisrel this+0xc8020>*/ /*|0xc8000|*/ unsigned char m_RecvBuf[819200];
  /*<thisrel this+0x190020>*/ /*|0x4|*/ int m_RecvBufLen;
  /*<thisrel this+0x190024>*/ /*|0x4|*/ void  (*ProtocolCore)(unsigned char, unsigned char*, size_t);
public:
  void SetProtocolCore(void  (*pc)(unsigned char, unsigned char*, size_t));
  bool FDWRITE_MsgDataSend();
  int DataRecv();
  bool DataSend(char* buf, int len);
  bool Connect(char* ip_addr, unsigned short port, unsigned long WinMsgNum);
  DServerCli();
  virtual /*<vtableoff 0x0>*/ ~DServerCli();
};
// <size 0x190028>

extern DServerCli DataCli;
extern DServerCli RankingServerCli;
extern DServerCli EventServerCli;

#endif