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

#ifndef _SERVERSOCKET_H_
#define _SERVERSOCKET_H_

#include <TcpSocket.h>
#include <ISocketHandler.h>
#include <QtCore\\QThread>

class MainSocketThread : public QThread
{
	Q_OBJECT
public:
	void run();
	void Shutdown();
private:
	bool shutting_down;
};

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
	static void StartThread();
};

extern MainSocketThread _SocketThread;

#endif