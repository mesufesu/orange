/*
	Copyright 2008-2009 Ambient.5

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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