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
#include ".\\DServerCli.h"

DServerCli DataCli;
DServerCli RankingServerCli;
DServerCli EventServerCli;

DServerCli::DServerCli()
{
}

DServerCli::~DServerCli()
{
}

void DServerCli::SetProtocolCore(void (*pc)(unsigned char, unsigned char *, size_t))
{
	this->ProtocolCore = pc;
}

bool DServerCli::Connect(char *ip_addr, unsigned short port, unsigned long WinMsgNum)
{
	hostent* host = 0;
	if(this->m_socket == NULL)
	{
		printf_s("m_socket == NULL\n");
		return false;
	}
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(ip_addr);
	if(addr.sin_addr.S_un.S_addr == -1)
	{
		host = gethostbyname(ip_addr);
		if(host == NULL)
		{
			printf_s("addr resolv failed.\n");
		}
		memcpy(&addr.sin_addr.S_un.S_addr, *host->h_addr_list, host->h_length);
	}
	int nResult = connect(this->m_socket, (sockaddr*)&addr, 16);
	if(nResult == SOCKET_ERROR && (WSAGetLastError() != WSAEWOULDBLOCK))
	{
		this->CloseReceive(this->m_socket);
		return false;
	}
	//nResult = WSAAsyncSelect(this->m_socket, this->m_hWnd, WinMsgNum, 35);
	if(nResult == SOCKET_ERROR)
	{
		closesocket(this->m_socket);
		printf_s("WSAAsyncSelect() failed with %d\n", WSAGetLastError());
		return false;
	}
	this->m_SendBufLen = 0;
	this->SetConnect(true);
	return true;
}

bool DServerCli::DataSend(char *buf, int len)
{
	if((len <= 0) || this->m_socket == INVALID_SOCKET)
	{
		return false;
	}
	int nDx = 0;
	unsigned char * sendbuf = this->m_SendBuf;
	int * sendbuflen = &len;
	if(this->m_SendBufLen > 0)
	{
		if(this->m_SendBufLen < 819200)
		{
			memcpy(&this->m_SendBuf[this->m_SendBufLen], buf, len); //strange
			this->m_SendBufLen += len;
			return true; //rave
		}
		this->Close();
		return false;
	}
	int nLeft = *sendbuflen;
	while(TRUE)
	{
		int nResult = send(this->m_socket, &buf[nDx], *sendbuflen - nDx, 0);
		if(nResult == SOCKET_ERROR)
		{
			if(WSAGetLastError() != WSAEWOULDBLOCK)
			{
				printf_s("send failed %d\n", WSAGetLastError());
				*sendbuflen = 0;
				this->CloseReceive(this->m_socket);
				return false;
			}
			if((nLeft + *sendbuflen) > 819200)
			{
				printf_s("send failed, too large\n");
				*sendbuflen = 0;
				this->CloseReceive(this->m_socket);
				return false;
			}
			if(nDx >= 0)
			{
				memcpy(&this->m_SendBuf[this->m_SendBufLen], &buf[nDx], nLeft);
				printf_s("send failed, nDx = %d\n", nDx);
				return true;
			}
		}
		else if(nResult == 0)
		{
			printf_s("nResult == 0, error = %d\n", WSAGetLastError());
			return true;
		}
		else if(nResult > 0)
		{
			nDx += nResult;
			nLeft -= nResult;
			*sendbuflen -= nResult;
		}
		if(nLeft <= 0)
		{
			return true;
		}
	}
}

bool DServerCli::FDWRITE_MsgDataSend()
{
	int nDx = 0;
	unsigned char * sendbuf = this->m_SendBuf;
	int* sendbuflen = &this->m_SendBufLen;
	if(*sendbuflen >= 1)
	{
		while(*sendbuflen > 0)
		{
			int nResult = send(this->m_socket, (const char*)&sendbuf[nDx], *sendbuflen - nDx, 0);
			if(nResult == SOCKET_ERROR)
			{
				if(WSAGetLastError() != WSAEWOULDBLOCK)
				{
					printf_s("FDWRITE send() %d %d\n", *sendbuflen, WSAGetLastError());
					this->Close();
					return false;
				}
				printf_s("FDWRITE send WSAEWOUDBLOCK %d\n", WSAGetLastError());
				break;
			}
			if(nResult <= 0)
			{
				printf_s("FDWRITE send() result is zero %d\n", WSAGetLastError());
				break;
			}
			printf_s( "error-L3 : nDx %d m_SendBufLen %d", nDx, this->m_SendBufLen);
			if(nResult > 0)
			{
				nDx += nResult;
				*sendbuflen -= nResult;
			}
			printf_s( "error-L3 : nDx %d m_SendBufLen %d", nDx, this->m_SendBufLen);
		}
		return true;
	}
	else
	{
		return true; //wz have 1 here
	}
}

int DServerCli::DataRecv()
{
	unsigned char* recvbuf = this->m_RecvBuf;
	int* recvbuflen = &this->m_RecvBufLen;
	int nResult = recv(this->m_socket, (char*)&this->m_RecvBuf[this->m_RecvBufLen], 819200 - this->m_RecvBufLen, 0);
	if(nResult)
	{
		if(nResult == SOCKET_ERROR)
		{
			if(WSAGetLastError() == WSAEWOULDBLOCK)
			{
				return true;
			}
			else
			{
				printf_s("recv error %d\n", WSAGetLastError());
				return true;
			}
		}
		else
		{
			*recvbuflen += nResult;
			if(*recvbuflen < 3)
			{
				return 3;
			}
			size_t lOfs = 0;
			size_t size = 0;
			unsigned char headcode = 0;
			while(TRUE)
			{
				switch(recvbuf[lOfs])
				{
				case 0xC1:
					{
						size = recvbuf[lOfs + 1];
						headcode = recvbuf[lOfs + 2];
						break;
					}
				case 0xC2:
					{
						size = (recvbuf[lOfs + 1] * 256) + recvbuf[lOfs + 2];
						headcode = recvbuf[lOfs + 3];
						break;
					}
				default:
					{
						printf_s("recv headcode error %d\n", recvbuf[lOfs]);
						return false;
					}
				}
				if(size > *recvbuflen)
				{
					break;
				}
				if(this->ProtocolCore) //security
				{
					this->ProtocolCore(headcode, &recvbuf[lOfs], size);
				}
				lOfs += size;
				if(*recvbuflen <= 0)
				{
					return false;
				}
			}
			if((lOfs > 0) && (*recvbuflen >= 1))
			{
				memcpy(recvbuf, &recvbuf[lOfs], *recvbuflen);
			}
			return false;
		}
	}
	else
	{
		printf_s("error-L3 : closed %d - buff:%d(%d)\n", 819200 - *recvbuflen, this->m_RecvBufLen, WSAGetLastError());
		return true;
	}
}