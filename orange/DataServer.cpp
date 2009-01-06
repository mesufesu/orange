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
#include ".\\DataServer.h"

char ip[] = "127.0.0.1";

CDSHandler DataServerCli;

CDSHandler::CDSHandler()
{
	this->m_ActiveServer = -1;
}

CDSHandler::~CDSHandler()
{
}

void CDSHandler::Connect()
{
	if(this->DS[0].GetSocket() == INVALID_SOCKET)
	{
		this->DS[0].CreateSocket(NULL);
		this->DS[0].SetProtocolCore(&DataServerProtocolCore);
		int result = this->DS[0].Connect(ip, 55960, 1034);
		if(result)
		{
			printf_s("DataServer[%d] connected.\n", 55960);
			this->m_ActiveServer = 0;
			DataServerLogin(0);
		}
		else
		{
			printf_s("DataServer[%d] connection failed.\n", 55960);
			this->DS[0].Close();
		}
	}
	if(this->DS[1].GetSocket() == INVALID_SOCKET)
	{
		this->DS[1].CreateSocket(NULL);
		this->DS[1].SetProtocolCore(&DataServerProtocolCore);
		int result = this->DS[1].Connect(ip, 55962, 1035);
		if(result)
		{
			printf_s("DataServer[%d] connected.\n", 55962);
			if(this->m_ActiveServer == -1)
			{
				this->m_ActiveServer = 1;
			}
			DataServerLogin(1);
		}
		else
		{
			printf_s("DataServer[%d] connection failed.\n", 55962);
			this->DS[1].Close();
		}
	}
	//exdb won't be here
}

void CDSHandler::ActiveChange()
{
	if(this->m_ActiveServer == 0)
	{
		this->m_ActiveServer = 1;
		printf_s("DataServer: Active Changed -> 1\n");
	}
	else
	{
		this->m_ActiveServer = 0;
		printf_s("DataServer: Active Changed -> 0\n");
	}
}

bool CDSHandler::Send(char *buf, size_t len, int server)
{
	int result = 0;
	if(server == -1)
	{
		if(this->m_ActiveServer != -1)
		{
			result = this->DS[this->m_ActiveServer].DataSend(buf, len);
			if(result <= 0)
			{
				this->ActiveChange();
				this->DS[this->m_ActiveServer].DataSend(buf, len);
				return true;
			}
		}
		return false;
	}
	else
	{
		result = this->DS[server].DataSend(buf, len);
		if(result <= 0)
		{
			this->ActiveChange();
			return false;
		}
		return true;
	}
	return false;
}

void CDSHandler::MsgProc(int line, unsigned int wParam, long lParam)
{
	switch(lParam)
	{
	case 1:
		{
			this->DS[this->m_ActiveServer].DataRecv();
			break;
		}
	case 2:
		{
			this->DS[this->m_ActiveServer].FDWRITE_MsgDataSend();
			break;
		}
	case 32:
		{
			this->DS[this->m_ActiveServer].Close();
			break;
		}
	}
}

void DataServerProtocolCore(unsigned char head, unsigned char* buff, size_t len)
{
}

void DataServerLogin(int server)
{
	SDHP_SERVERINFO pInfo;
	pInfo.h.c = 0xC1;
	pInfo.h.headcode = 0x00;
	pInfo.h.size = sizeof(SDHP_SERVERINFO);
	pInfo.Port = 55901;
	pInfo.ServerCode = 0;
	pInfo.Type = 1;
	strcpy_s(pInfo.ServerName, sizeof(pInfo.ServerName), "Test Server");
	DataServerCli.Send((char*)&pInfo, pInfo.h.size, server);
}