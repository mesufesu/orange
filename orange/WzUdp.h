#ifndef _WZUDP_H_
#define _WZUDP_H_

#include <winsock2.h>

typedef void (*_PPROTOCOLCORE)(unsigned char, unsigned char*, int);

struct PER_IO_OPERATION_DATA
{
  /*<thisrel this+0x0>*/ /*|0x14|*/ OVERLAPPED Overlapped;
  /*<thisrel this+0x14>*/ /*|0x8|*/ WSABUF DataBuf;
  /*<thisrel this+0x1c>*/ /*|0x800|*/ char Buffer[2048];
  /*<thisrel this+0x81c>*/ /*|0x4|*/ unsigned long Bytes;
  /*<thisrel this+0x820>*/ /*|0x4|*/ int lOfs;
};
// <size 0x824>

class WzUdp
{
public:
  /*<thisrel this+0x4>*/ /*|0x4|*/ int m_Port;
  /*<thisrel this+0x8>*/ /*|0x4|*/ HANDLE m_ThreadHandle;
  /*<thisrel this+0xc>*/ /*|0x4|*/ unsigned long m_ThreadID;
  /*<thisrel this+0x10>*/ /*|0x4|*/ SOCKET m_Socket;
  /*<thisrel this+0x14>*/ /*|0x4|*/ unsigned char* m_Recvbuf;
  /*<thisrel this+0x18>*/ /*|0x4|*/ unsigned char* m_Sendbuf;
  /*<thisrel this+0x1c>*/ /*|0x4|*/ int m_dwLength;
  /*<thisrel this+0x20>*/ /*|0x4|*/ int m_dwRecvOfs;
  /*<thisrel this+0x24>*/ /*|0x4|*/ int m_dwSendLength;
  /*<thisrel this+0x28>*/ /*|0x824|*/ PER_IO_OPERATION_DATA m_PerIoSendData;
  /*<thisrel this+0x84c>*/ /*|0x10|*/ sockaddr_in m_SockAddr;
  /*<thisrel this+0x85c>*/ /*|0x4|*/ _PPROTOCOLCORE ProtocolCore;

  WzUdp();
  bool Init();
  bool CreateSocket();
  bool Run();
  int SendData(unsigned char* SendData, unsigned long nSendDataLen);
  int MuProtocolParse(unsigned char* RecvData, int* nRecvDataLen);
  bool Close();
  bool SendSet(char* ip, int port);
  bool RecvSet(int port);
  int RecvThread();
  bool SetProtocolCore(_PPROTOCOLCORE pc);

  virtual /*<vtableoff 0x0>*/ ~WzUdp();
};
// <size 0x860>

unsigned long WINAPI WzUdpRecvThread(WzUdp* lpWzUdp);

extern WzUdp gUdpSoc;
extern WzUdp gUdpSocCER;
extern WzUdp gUdpSocCE;

#endif