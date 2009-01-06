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
#include ".\\WinsockBase.h"

WinsockBase::WinsockBase()
{
	this->m_socket = INVALID_SOCKET; //-1 by wz, i prefer INVALID_SOCKET
	this->Startup();
}

WinsockBase::~WinsockBase()
{
	WSACleanup();
}

bool WinsockBase::Startup()
{
	WSADATA wsaData;
	int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(err != 0)
	{
		MessageBox(NULL, "WSB WSAStartup failed.", "Error", MB_OK | MB_ICONSTOP);
		WSACleanup();
		return false;
	}
	//webzen have stupid check for ws version here, not needed.
	this->m_socket = INVALID_SOCKET;
	this->m_iMaxSockets = wsaData.iMaxSockets;
	this->m_Connect = false;
	return true;
}

bool WinsockBase::CreateSocket(HWND hWnd)
{
	//size_t size = 4;
	this->m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_HOPOPTS); //IPPROTO ~ 0 by wz
	if(this->m_socket != INVALID_SOCKET)
	{
		this->m_hWnd = hWnd;
		return true;
	}
	else
	{
		return false;
	}
}

void WinsockBase::Close()
{
	closesocket(this->m_socket);
	this->m_socket = INVALID_SOCKET;
	this->m_Connect = false;
}

void WinsockBase::CloseReceive(SOCKET socket)
{
	shutdown(socket, SD_RECEIVE);
	closesocket(socket);
	this->m_socket = INVALID_SOCKET;
	this->m_Connect = false;
}

void WinsockBase::CloseSend(SOCKET socket)
{
	shutdown(socket, SD_SEND);
	closesocket(socket);
	this->m_socket = INVALID_SOCKET;
	this->m_Connect = false;
}

SOCKET WinsockBase::GetSocket()
{
	return (this->m_socket);
}

size_t WinsockBase::GetRecvBuffSize()
{
	return (this->m_recvbufsize);
}

size_t WinsockBase::GetSendBuffSize()
{
	return (this->m_sendbufsize);
}

bool WinsockBase::GetConnect()
{
	return (this->m_Connect);
}

void WinsockBase::SetConnect(bool connected)
{
	this->m_Connect = connected;
}