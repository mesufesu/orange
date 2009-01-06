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