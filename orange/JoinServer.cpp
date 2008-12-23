#include "stdafx.h"
#include ".\\packets.h"
#include ".\\JoinServer.h"

DServerCli JoinServerCli;

void JoinProtocolCore(unsigned char head, unsigned char * buf, size_t len)
{
	for(uint32 i = 0; i < len; ++i)
	{
		printf_s("%02x\n", buf[i]);
	}
}

bool JoinServerConnect(char* ConnectServer, unsigned long wMsg)
{
	char ip[] = "87.224.153.99";
	JoinServerCli.SetProtocolCore(&JoinProtocolCore);
	if(JoinServerCli.Connect(ip, 55970, wMsg))
	{
		JoinServerLogin();
		printf_s("Connected to Join Server\n");
		return true;
	}
	return false;
}

void JoinServerLogin()
{
	SDHP_SERVERINFO pInfo;
	pInfo.h.c = 0xC1;
	pInfo.h.headcode = 0x00;
	pInfo.h.size = sizeof(SDHP_SERVERINFO);
	pInfo.Port = 55901;
	pInfo.ServerCode = 0;
	pInfo.Type = 1;
	strcpy_s(pInfo.ServerName, sizeof(pInfo.ServerName), "Test Server");
	JoinServerCli.DataSend((char*)&pInfo, pInfo.h.size);
}