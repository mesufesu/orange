#ifndef _HEARTBEATSERVER_H_
#define _HEARTBEATSERVER_H_

#include "..\\Include\\TcpSocket.h"
#include "..\\Include\\ISocketHandler.h"

class HeartbeatSocket : public TcpSocket
{
public:
	HeartbeatSocket(ISocketHandler& h);

	void OnAccept();
	void OnRead();
	void OnDisconnect();
};

void WINAPI HeartbeatServerProc(port_t port);

#endif