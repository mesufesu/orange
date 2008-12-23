#ifndef _JOINSERVER_H_
#define _JOINSERVER_H_

#include ".\\DServerCli.h"

void JoinServerLogin();
bool JoinServerConnect(char* ConnectServer, unsigned long wMsg);
void JoinProtocolCore(unsigned char head, unsigned char * buf, size_t len);

extern DServerCli JoinServerCli;

#endif