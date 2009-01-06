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