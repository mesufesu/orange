#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include ".\\WhatsUpDummyServer.h"

/*CHeartbeatServer::CHeartbeatServer()
{
	WSADATA wsaData;
	this->m_socket = INVALID_SOCKET;
	this->m_wPORT = 0;
	this->m_lpOldProc = 0;
	WSAStartup(0x202, &wsaData);
}

CHeartbeatServer::~CHeartbeatServer()
{
	if(this->m_socket != INVALID_SOCKET)
	{
		closesocket(this->m_socket);
	}
}*/