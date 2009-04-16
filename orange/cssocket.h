#ifndef _CSSOCKET_H_
#define _CSSOCKET_H_

#include <UdpSocket.h>
#include <QtCore/QThread>

class CSThread : public QThread
{
	Q_OBJECT
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