#ifndef _CSSOCKET_H_
#define _CSSOCKET_H_

#include ".\\sockets_lib\\UdpSocket.h"
#include <QtCore\\QThread>

class CSThread : public QThread
{
public:
	void run();
};

class CSUdp : public UdpSocket
{
public:
	CSUdp(ISocketHandler&);
};

extern CSThread CSSocketThread;

#endif