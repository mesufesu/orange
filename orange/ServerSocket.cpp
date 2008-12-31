#include "stdafx.h"
#include "..\\Include\\ListenSocket.h"
#include "..\\Include\\SocketHandler.h"
#include "..\\Deathway\\SimpleModulus\\SimpleModulus.h"
#include "..\\Deathway\\spe.h"
#include ".\\objectmanager.h"
#include ".\\protocol.h"
#include ".\\ServerSocket.h"

ServerSocket::ServerSocket(ISocketHandler &h) : TcpSocket(h)
{
}

void ServerSocket::OnAccept()
{
	printf_s("Connected from: %s:%d\n", this->GetRemoteAddress().c_str(), this->GetRemotePort());
	CPlayer * newPlayer = ObjManager.CreatePlayer(this);
	newPlayer->status = PLAYER_CONNECTED;
	TestJoinSend(newPlayer, 1);
}

void ServerSocket::OnRead()
{
	TcpSocket::OnRead();
	unsigned char head;
	unsigned char sub[4];
	int n = ibuf.GetLength();
	if(n)
	{
		while(TRUE)
		{
			if(!ibuf.GetLength())
			{
				return;
			}
			ibuf.SoftRead((char*)&head, 1);
			switch(head)
			{
			case 0xC1:
				{
					this->COneHandler();
					break;
				}
			case 0xC2:
				{
					ibuf.SoftRead((char*)sub, 4);
					printf_s("Unhandled %02x %02x %02x\n", head, sub[2], sub[3]);
					break;
				}
			case 0xC3:
				{
					this->CThreeHandler();
					break;
				}
			case 0xC4:
				{
					ibuf.SoftRead((char*)sub, 4);
					printf_s("Unhandled %02x %02x %02x\n", head, sub[2], sub[3]);
					break;
				}
			default:
				{
					printf_s("recv wrong packet %02x\n", head);
				}
			}
		}
	}
}

void ServerSocket::OnDisconnect()
{
	printf_s("Disconnected: %s:%d\n", this->GetRemoteAddress().c_str(), this->GetRemotePort());
	CPlayer* player = ObjManager.FindPlayerBySocket(this);
	if(player->status == PLAYER_PLAYING)
	{
		player->SavePlayer();
	}
	player->SetStatus(0);
	player->status = PLAYER_EMPTY;
	player->type = VOID_PLAYER;
}

void ServerSocket::CThreeHandler()
{
	std::vector<unsigned char> buffer;
	buffer.clear();
	buffer.resize(2);
	if(ibuf.GetLength() < 3)
	{
		return;
	}
	ibuf.Read((char*)&buffer[0], 2);
	size_t packet_size = buffer.at(1);
	if(ibuf.GetLength() < (packet_size - 2))
	{
		return;
	}
	buffer.resize(packet_size);
	ibuf.Read((char*)&buffer[2], (packet_size - 2));
	//================================//
	unsigned char dec_buffer[7024];
	ZeroMemory(dec_buffer, sizeof(dec_buffer));
	int ret = g_SimpleModulusCS.Decrypt(&dec_buffer[2], &buffer[2], packet_size - 2);
	unsigned char* pDecBuf = &dec_buffer[1];
	unsigned char headcode = pDecBuf[2];
	unsigned char subhead = dec_buffer[2];
	dec_buffer[1] = 0xC1;
	dec_buffer[2] = (ret&0xFF)+2;
	CStreamPacketEngine_Server PacketStream;
	PacketStream.Clear();
	if(!PacketStream.AddData(&dec_buffer[1], ret +2))
	{
		return;
	}
	if(PacketStream.ExtractPacket(dec_buffer) != 0)
	{
		return;
	}
	//=====//
	dec_buffer[1]--;
	ret++;
	//=====//
	ProtocolCore(ObjManager.FindPlayerBySocket(this), headcode, dec_buffer, ret, true, subhead);
}

void ServerSocket::COneHandler()
{
	std::vector<unsigned char> buffer;
	buffer.clear();
	buffer.resize(2);
	if(ibuf.GetLength() < 3)
	{
		return;
	}
	ibuf.Read((char*)&buffer[0], 2);
	size_t packet_size = buffer.at(1);
	if(ibuf.GetLength() < (packet_size - 2))
	{
		return;
	}
	buffer.resize(packet_size);
	ibuf.Read((char*)&buffer[2], (packet_size - 2));
	//======================//
	unsigned char packet_buffer[16384];
	ZeroMemory(packet_buffer, sizeof(packet_buffer));
	CStreamPacketEngine_Server PacketStream;
	PacketStream.Clear();
	if(!PacketStream.AddData(&buffer[0], packet_size))
	{
		return;
	}
	if(PacketStream.ExtractPacket(packet_buffer) != 0)
	{
		return;
	}
	ProtocolCore(ObjManager.FindPlayerBySocket(this), packet_buffer[2], packet_buffer, packet_size, false, -1);
}

void WINAPI ServerSocketProc(port_t port)
{
	SocketHandler server_handler;
	ListenSocket<ServerSocket> server_lsocket(server_handler);
	if(server_lsocket.Bind(port))
	{
		printf_s("Server socket binding failed.\n");
		return;
	}
	server_handler.Add(&server_lsocket);
	server_handler.Select(1, 0);
	while(TRUE)
	{
		server_handler.Select(1, 0);
	}
}