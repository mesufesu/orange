#include "stdafx.h"
#include <SocketHandler.h>
#include "packets.h"
#include "cssocket.h"

CSThread CSSocketThread;

CSUdp::CSUdp(ISocketHandler &h) : UdpSocket(h)
{
}

void CSThread::run()
{
	uint32 last_tick = GetTicks();
	SocketHandler h;
	CSUdp CSSocket(h);
	PMSG_SERVERINFO data;
	ZeroMemory(&data, sizeof(PMSG_SERVERINFO));
	data.h.c = 0xC1;
	data.h.headcode = 0x01;
	data.h.size = sizeof(PMSG_SERVERINFO);
	data.ServerCode = 0;
	while(true)
	{
		if(GetTickDiff(last_tick) >= SECOND)
		{
			last_tick = GetTicks();
			data.Percent = 30;
			data.UserCount = 12;
			data.AccountCount = 10;
			data.PCbangCount = 10;
			data.MaxUserCount = 11;
			CSSocket.SendToBuf("127.0.0.1", 55557, (const char*)&data, data.h.size);
		}
		this->msleep(300);
	}
}