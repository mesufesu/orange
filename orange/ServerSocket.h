#ifndef _SERVERSOCKET_H_
#define _SERVERSOCKET_H_

#include "..\\Include\\TcpSocket.h"
#include "..\\Include\\ISocketHandler.h"

class ServerSocket : public TcpSocket
{
public:
	ServerSocket(ISocketHandler& h);

	void OnAccept();
	void OnRead();
	void OnDisconnect();
	void CThreeHandler();
	void COneHandler();
	void CloseClient();
};

void WINAPI ServerSocketProc(port_t port);

#endif