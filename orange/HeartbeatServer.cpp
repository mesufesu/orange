#include "stdafx.h"
#include "..\\Include\\ListenSocket.h"
#include "..\\Include\\SocketHandler.h"
#include ".\\HeartbeatServer.h"

HeartbeatSocket::HeartbeatSocket(ISocketHandler &h) : TcpSocket(h)
{
}

void HeartbeatSocket::OnAccept()
{
	printf_s("Connected from: %s:%d\n", this->GetRemoteAddress().c_str(), this->GetRemotePort());
}

void HeartbeatSocket::OnRead()
{
	TcpSocket::OnRead();
	int n = ibuf.GetLength();
	if(n)
	{
		char temp[2048];
		ZeroMemory(temp ,2048);
		ibuf.Read(temp, n);
	}
}

void HeartbeatSocket::OnDisconnect()
{
	printf_s("Disconnected: %s:%d\n", this->GetRemoteAddress().c_str(), this->GetRemotePort());
}

void WINAPI HeartbeatServerProc(port_t port)
{
	SocketHandler hb_handler;
	ListenSocket<HeartbeatSocket> hb_lsocket(hb_handler);
	if(hb_lsocket.Bind(port))
	{
		printf_s("Heartbeat Server socket binding failed.\n");
		return;
	}
	hb_handler.Add(&hb_lsocket);
	hb_handler.Select(1, 0);
	while(TRUE)
	{
		hb_handler.Select(1, 0);
	}
}