#ifndef _WINSOCKBASE_H_
#define _WINSOCKBASE_H_

#include <winsock2.h>

class WinsockBase
{
protected:
  /*<thisrel this+0x0>*/ /*|0x4|*/ int m_iMaxSockets;
  /*<thisrel this+0x4>*/ /*|0x4|*/ HWND m_hWnd;
  /*<thisrel this+0x8>*/ /*|0x4|*/ SOCKET m_socket;
  /*<thisrel this+0xc>*/ /*|0x4|*/ size_t m_sendbufsize;
  /*<thisrel this+0x10>*/ /*|0x4|*/ size_t m_recvbufsize;
  /*<thisrel this+0x14>*/ /*|0x4|*/ bool m_Connect;
public:
  bool Startup();
  bool CreateSocket(HWND hWnd);
  void CloseReceive(SOCKET socket);
  void Close();
  void CloseSend(SOCKET socket);
  SOCKET GetSocket();
  size_t GetSendBuffSize();
  size_t GetRecvBuffSize();
  bool GetConnect();
  void SetConnect(bool connected);
  WinsockBase();
  ~WinsockBase();
};
// <size 0x18>

#endif