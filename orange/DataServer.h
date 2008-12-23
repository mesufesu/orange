#ifndef _DATASERVER_H_
#define _DATASERVER_H_

#include ".\\DServerCli.h"

class CDSHandler
{
private:
  /*<thisrel this+0x4>*/ /*|0x320050|*/ DServerCli DS[2];
  /*<thisrel this+0x320054>*/ /*|0x4|*/ int m_ActiveServer;
public:
  CDSHandler();
  void Connect();
  void ActiveChange();
  //int Send(int server, char* buf, int len);
  bool Send(char* buf, size_t len, int server = -1);
  void MsgProc(int line, unsigned int wParam, long lParam);
  int GetActiveDS();

  virtual /*<vtableoff 0x0>*/ ~CDSHandler();
};
// <size 0x320058>

extern CDSHandler DataServerCli;

void DataServerProtocolCore(unsigned char head, unsigned char* buff, size_t len);
void DataServerLogin(int server);

#endif