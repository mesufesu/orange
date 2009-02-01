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
#include ".\\sockets_lib\\ListenSocket.h"
#include ".\\sockets_lib\\SocketHandler.h"
#include ".\\HeartbeatServer.h"

HBThread HeartBeatThread;

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

void HBThread::run()
{
	SocketHandler hb_handler;
	ListenSocket<HeartbeatSocket> hb_lsocket(hb_handler);
	if(hb_lsocket.Bind(55902))
	{
		Log.String("Heartbeat Server socket binding failed.");
		return;
	}
	hb_handler.Add(&hb_lsocket);
	hb_handler.Select(1, 0);
	while(TRUE)
	{
		hb_handler.Select(1, 0);
	}
}