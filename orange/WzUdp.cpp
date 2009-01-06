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
#include ".\\WzUdp.h"

WzUdp gUdpSoc;
WzUdp gUdpSocCER;
WzUdp gUdpSocCE;

WzUdp::WzUdp()
{
	this->Init();
}

WzUdp::~WzUdp()
{
	this->Close();
}

bool WzUdp::Init()
{
	WSADATA wsa;
	if(WSAStartup(0x202, &wsa))
	{
		return false;
	}
	this->m_Socket = -1;
	this->m_dwLength = 4096;
	this->m_dwRecvOfs = 0;
	this->m_ThreadHandle = 0;
	this->ProtocolCore = 0;
	return true;
}

bool WzUdp::Close()
{
	TerminateThread(this->m_ThreadHandle, 0);
	if(this->m_ThreadHandle)
	{
		WaitForSingleObject(this->m_ThreadHandle, INFINITE);
		CloseHandle(this->m_ThreadHandle);
		this->m_ThreadHandle = 0; //0
	}
	HeapFree(GetProcessHeap(), 0, (LPVOID)&(this->m_dwRecvOfs)); //?
	return true;
}

bool WzUdp::CreateSocket()
{
	if(this->m_Socket != SOCKET_ERROR)
	{
		closesocket(this->m_Socket);
		this->m_Socket = SOCKET_ERROR;
	}
	this->m_Socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_IP, 0, 0, 0);
	return (this->m_Socket != SOCKET_ERROR);
}

bool WzUdp::SendSet(char *ip, int port)
{
	this->m_Port = port;
	this->m_SockAddr.sin_family = AF_INET;
	this->m_SockAddr.sin_port = htons(port);
	this->m_SockAddr.sin_addr.S_un.S_addr = inet_addr(ip);
	if(this->m_SockAddr.sin_addr.S_un.S_addr == -1)
	{
		hostent * h = gethostbyname(ip);
		if(!h)
		{
			return false;
		}
		memcpy(&this->m_SockAddr.sin_addr, *h->h_addr_list, h->h_length);
	}
	return true;
}

bool WzUdp::SetProtocolCore(void (*pc )(unsigned char, unsigned char *, int))
{
	this->ProtocolCore = pc;
	return true;
}

bool WzUdp::RecvSet(int port)
{
	this->m_Port = port;
	this->m_SockAddr.sin_port = htons(port);
	this->m_SockAddr.sin_family = AF_INET;
	this->m_SockAddr.sin_addr.S_un.S_addr = NULL;
	if(bind(this->m_Socket, (sockaddr*)&this->m_SockAddr, 16) == SOCKET_ERROR)
	{
		return false;
	}
	this->m_Recvbuf = (unsigned char*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, this->m_dwLength);
	if(!this->m_Recvbuf)
	{
		return false;
	}
	return true;
}

int WzUdp::SendData(unsigned char *SendData, unsigned long nSendDataLen)
{
	memset(&this->m_PerIoSendData, 0x00, sizeof(this->m_PerIoSendData));
	memcpy(this->m_PerIoSendData.Buffer, SendData, nSendDataLen);
	this->m_PerIoSendData.lOfs = nSendDataLen;
	this->m_PerIoSendData.DataBuf.buf = this->m_PerIoSendData.Buffer;
	this->m_PerIoSendData.DataBuf.len = this->m_PerIoSendData.lOfs;
	int ret = WSASendTo(this->m_Socket, &this->m_PerIoSendData.DataBuf, 1, &nSendDataLen, NULL, (const sockaddr*)&this->m_SockAddr, 16, &(this->m_PerIoSendData.Overlapped), NULL);
	if(ret != SOCKET_ERROR || WSAGetLastError() == WSA_IO_PENDING)
	{
		return TRUE;
	}
	else
	{
		printf_s("udp send failed %d\n", WSAGetLastError());
		return -1;
	}
}

int WzUdp::MuProtocolParse(unsigned char *RecvData, int *nRecvDataLen)
{
	size_t lOfs = 0;
	int size = 0;
	if(this->ProtocolCore)
	{
		unsigned char headcode;
		while(TRUE)
		{
			if(RecvData[lOfs] == 0xC1)
			{
				size = RecvData[lOfs + 1];
				headcode = RecvData[lOfs + 2];
			}
			else
			{
				if(RecvData[lOfs] != 0xC2)
				{
					this->m_dwRecvOfs = 0;
					return FALSE;
				}
				size = ((256 * RecvData[lOfs + 1]) + RecvData[lOfs + 2]);
				headcode = RecvData[lOfs + 3];
			}
			if(size <= 0)
			{
				return FALSE;
			}
			if(size > *nRecvDataLen)
			{
				break;
			}
			this->ProtocolCore(headcode, &RecvData[lOfs], size);
			lOfs += size;
			this->m_dwRecvOfs -= size;
			if(this->m_dwRecvOfs <= 0)
			{
				return TRUE;
			}
		}
		if(lOfs <= 0)
		{
			return TRUE;
		}
		if(this->m_dwRecvOfs >= 1)
		{
			memcpy(RecvData, &RecvData[lOfs], this->m_dwRecvOfs);
			return TRUE;
		}
		return true; //unneeded
	}
	else
	{
		return 0;
	}
}

bool WzUdp::Run()
{
	this->m_ThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WzUdpRecvThread, this, 0, &this->m_ThreadID);
	if(this->m_ThreadHandle == 0)
	{
		return false;
	}
	return true;
}

int WzUdp::RecvThread()
{
	unsigned long dwSenderSize = 16;
	int ret = 0;
	sockaddr_in sender;
	while(TRUE)
	{
		do
		{
			ret = recvfrom(this->m_Socket, (char*)&this->m_Recvbuf[this->m_dwRecvOfs], 4096 - this->m_dwRecvOfs, 0, (sockaddr*)&sender, (int*)&dwSenderSize);
		}
		while(ret == -1);
		if(ret)
		{
			this->m_dwLength = ret;
			this->m_dwRecvOfs += ret;
			this->MuProtocolParse(this->m_Recvbuf, &this->m_dwLength);
		}
	}
}

unsigned long WINAPI WzUdpRecvThread(WzUdp* lpWzUdp)
{
	lpWzUdp->RecvThread();
	return TRUE;
}