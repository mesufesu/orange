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
#include ".\\DataBase.h"
#include ".\\utils.h"
#include ".\\WorldMap.h"
#include ".\\ItemManager.h"
#include ".\\protocol.h"
#include ".\\classdef.h"
#include ".\\commands.h"

void ProtocolCore(CPlayer* player, unsigned char opcode, unsigned char* buffer, size_t size, bool Encrypt, int serial)
{
	switch(buffer[0])
	{
	case 0xC1:
		{
			if(buffer[1] != size)
			{
				Log.String("Packet size mismatch %d", (int)(buffer[1] - size));
			}
			break;
		}
	case 0xC2:
		{
			if((buffer[1] * 256 + buffer[2]) != size)
			{
				Log.String("Packet size mismatch %d", (int)((buffer[2] + buffer[2] * 256) - size));
			}
			break;
		}
	}
	/*Log.String("Got packet %02x size %02x %02x:", opcode, size, buffer[1]);
	for(uint32 i = 0; i < size; ++i)
	{
		Log.String("%02x ", buffer[i]);
	}
	Log.String("\n");*/

	if(size)
	{
		switch(opcode)
		{
		case 0x00:
			{
				if(size > sizeof(PMSG_CHATDATA))
				{
					Log.String("PMSG_CHATDATA recieved size is larger than defined: %u", size);
				}
				Player_Chat((PMSG_CHATDATA*)buffer, player);
				break;
			}
		case 0x18:
			{
				if(size != sizeof(PMSG_ACTION))
				{
					Log.String("Size mismatch %d:%d %02X", size, sizeof(PMSG_ACTION), opcode);
				}
				World_Action((PMSG_ACTION*)buffer, player);
				break;
			}
		case 0x1D:
			{
				if(size != sizeof(PMSG_MOVE))
				{
					Log.String("Size mismatch %d:%d %02X", size, sizeof(PMSG_MOVE), opcode);
				}
				World_Move((PMSG_MOVE*) buffer, player);
				break;
			}
		case 0xF1:
			{
				switch(buffer[3])
				{
				case 0x01:
					{
						Join_LoginHandler((PMSG_IDPASS*)buffer, player);
						break;
					}
				case 0x02:
					{
						Log.String("Unhandled F1 %02x packet.", buffer[3]);
						break;
					}
				case 0x03:
					{
						Log.String("Unhandled F1 %02x packet.", buffer[3]);
						break;
					}
				default:
					{
						Log.String("Unhandled F1 %02x packet.", buffer[3]);
						break;
					}
				}
				break;
			}
		case 0xF3:
			{
				switch(buffer[3])
				{
				case 0x00:
					{
						Join_GetCharacters(player);
						break;
					}
				case 0x01:
					{
						Join_CreateCharacter((PMSG_CHARCREATE*)buffer, player);
						break;
					}
				case 0x03:
					{
						Join_WorldJoin((PMSG_CHARMAPJOIN*)buffer, player);
						break;
					}
				default:
					{
						Log.String("Unhandled F3 %02x packet.", buffer[3]);
						break;
					}
				}
				break;
			}
		case 0x0E:
			{
				Client_Time((PMSG_CLIENTTIME*)buffer, player);
				break;
			}
		default:
			{
				Log.String("Unhandled opcode %02x", opcode);
				break;
			}
		}
	}
}

void TestJoinSend(CPlayer* player, int result)
{
	PMSG_JOINRESULT data;
	data.h.c = 0xC1;
	data.h.size = sizeof(PMSG_JOINRESULT);
	data.h.headcode = 0xF1;
	data.scode = 0;
	data.result = LOBYTE(result);
	data.NumberH = HIBYTE(player->guid);
	data.NumberL = LOBYTE(player->guid);
	/*char ver[] = "1.02.19";
	char* pch = strtok(ver,".");
	data.CliVersion[0] = pch[0];
	pch = strtok(NULL,".");
	data.CliVersion[1] = pch[0];
	data.CliVersion[2] = pch[1];
	pch = strtok(NULL,".");
	data.CliVersion[3] = pch[0];
	data.CliVersion[4] = pch[1];*/
	data.CliVersion[0] = '1';
	data.CliVersion[1] = '0';
	data.CliVersion[2] = '3';
	data.CliVersion[3] = '0';
	data.CliVersion[4] = '2';
	player->Send((unsigned char*)&data, data.h.size);
}

void JoinResult(CPlayer* player, unsigned char result)
{
	PMSG_RESULT data;
	data.h.c = 0xC1;
	data.h.headcode = 0xF1;
	data.h.size = sizeof(PMSG_RESULT);
	data.subcode = 0x01;
	data.result = result;
	player->Send((unsigned char*)&data, data.h.size);
}

void Join_GetCharacters(CPlayer* player)
{
	char acc[11];
	ZeroMemory(acc, sizeof(acc));
	memcpy(acc, player->account, 10);

	QSqlQuery q;
	MainDB.Lock();
	q.exec(Query("SELECT `gmlevel` FROM `accounts` WHERE `account` = '%s';", player->account).c_str());
	MainDB.Unlock();
	q.next();
	player->gmlevel = q.value(0).toInt();

	PMSG_CHARLISTCOUNT data;
	data.h.c = 0xC1;
	data.h.headcode = 0xF3;
	data.subcode = 0;
	data.MaxClass = 5; //need calculation;
	data.MoveCnt = 0;
	PMSG_CHARLIST chars[5];
	ZeroMemory(chars, (sizeof(PMSG_CHARLIST) * 5));

	uint32 count = player->LoadSelectionScreen();
	SC_CHARINFO * info = NULL;
	for(uint32 i = 0; i < count; ++i)
	{
		info = &(player->sc_charinfo[i]);
		strcpy_s(chars[i].Name, 10, info->name.c_str());
		chars[i].Level = info->level;
		chars[i].Index = i;
		chars[i].CtlCode = player->gmlevel; //incorrect, I have different codes :)
		chars[i].CharSet[0] = (32 * info->Class) & 0xE0; //todo: I DO HAVE charset, but in wrong function \=
		switch(info->ChangeUp)
		{
		case 0:
		case 1:
			{
				chars[i].CharSet[0] |= (16 * info->ChangeUp) & 0x10;
				break;
			}
		case 2:
			{
				chars[i].CharSet[0] |= 0x18;
				break;
			}
		}
		chars[i].CharSet[12] |= 0xF0;
		chars[i].CharSet[1] = -1;
		chars[i].CharSet[13] |= 0xF0;
		chars[i].CharSet[2] = -1;
		chars[i].CharSet[13] |= 0xF;
		chars[i].CharSet[9] |= 0x80;
		chars[i].CharSet[3] |= 0xF0;
		chars[i].CharSet[14] |= 0xF0;
		chars[i].CharSet[9] |= 0x40;
		chars[i].CharSet[3] |= 0xF;
		chars[i].CharSet[14] |= 0xF;
		chars[i].CharSet[9] |= 0x20;
		chars[i].CharSet[4] |= 0xF0;
		chars[i].CharSet[15] |= 0xF0;
		chars[i].CharSet[9] |= 0x10;
		chars[i].CharSet[4] |= 0xF;
		chars[i].CharSet[15] |= 0xF;
		chars[i].CharSet[9] |= 0x8;
		chars[i].CharSet[5] |= 0xF0;
		chars[i].CharSet[5] |= 0xC;
		chars[i].CharSet[5] |= 0x3;
	}

	data.Count = count;
	data.h.size = (sizeof(PMSG_CHARLISTCOUNT) + count * sizeof(PMSG_CHARLIST));

	unsigned char buffer[2048];
	ZeroMemory(buffer, sizeof(buffer));
	memcpy(&buffer[0], &data, sizeof(PMSG_CHARLISTCOUNT));
	size_t offs = sizeof(PMSG_CHARLISTCOUNT);
	for(uint32 i = 0; i < count; ++i)
	{
		memcpy(&buffer[offs], &chars[i], sizeof(PMSG_CHARLIST));
		offs += sizeof(PMSG_CHARLIST);
	}
	player->Send((unsigned char*)buffer, data.h.size);
}

void Join_WorldJoin(PMSG_CHARMAPJOIN* data, CPlayer* player)
{
	int32 num = -1;
	std::string name = data->Name;
	for(uint32 i = 0; i < 5; ++i)
	{
		if(name == player->sc_charinfo[i].name)
		{
			num = i;
			break;
		}
	}
	SC_CHARINFO * sc = &(player->sc_charinfo[num]);
	if(!(player->LoadCharacterData(sc)))
	{
		player->Close();
		return;
	}
	PMSG_CHARMAPJOINRESULT result;
	ZeroMemory(&result, sizeof(result));
	result.h.c = 0xC3;
	result.h.size = sizeof(PMSG_CHARMAPJOINRESULT);
	result.h.headcode = 0xF3;
	result.subcode = 0x03;

	result.MapX = player->x;
	result.MapY = player->y;
	result.MapNumber = player->map;
	result.Dir = player->dir;
	result.Exp = player->experience;
	result.NextExp = levelexp[player->level];
	result.LevelUpPoint = player->leveluppoint;
	result.Str = player->strength;
	result.Dex = player->dexterity;
	result.Vit = player->vitality;
	result.Energy = player->energy;
	result.Life = (uint16)player->life;
	result.MaxLife = (uint16)player->maxlife;
	result.Mana = (uint16)player->mana;
	result.MaxMana = (uint16)player->maxmana;
	result.wShield = (uint16)player->shield;
	result.wMaxShield = (uint16)player->maxshield;
	result.BP = (uint16)player->bp;
	result.MaxBP = (uint16)player->maxbp;
	result.Money = player->money;
	result.PkLevel = player->pklevel;
	result.CtlCode = 0;
	result.AddPoint = player->addpoint;
	result.MaxAddPoint = player->maxaddpoint;
	result.wMinusPoint = player->minuspoint;
	result.wMaxMinusPoint = player->maxminuspoint;
	result.unk3 = 0x005c; //1.3.2 sniffed from war 12 lvl
	//a lot of trash must be done here

	player->Send((unsigned char*)&result, result.h.size);
	player->CookCharset();
	player->SendInventory();
	player->status = PLAYER_PLAYING;
	player->tick_count = 0xFFFFFFFF;
	//and here =)
}

void Join_LoginHandler(PMSG_IDPASS* data, CPlayer* player)
{
	QSqlQuery q;
	int status = 0;
	char pass[11];
	char account[11];
	ZeroMemory(pass, sizeof(pass));
	ZeroMemory(account, sizeof(account));
	memcpy(pass, data->Pass, 10);
	memcpy(account, data->Id, 10);
	xor3((unsigned char*)pass, 10);
	xor3((unsigned char*)account, 10);
	MainDB.Lock();
	/*q.prepare("SELECT `status` FROM `accounts` WHERE `account` = '?'");
	q.bindValue(0, "amb5");
	q.exec();*/
	q.exec(Query("SELECT `status` FROM `accounts` WHERE `account` = '%s';", account).c_str());
	//QSqlError err = q.lastError();
	//QString query_ = q.lastQuery();
	if(q.next())
	{
		status = q.value(0).toInt();
	}
	MainDB.Unlock();
	if(status != 0)
	{
		player->failed_attempts++;
		if(player->failed_attempts > 3)
		{
			JoinResult(player, 0x08);
		}
		else
		{
			JoinResult(player, 15);
		}
		return;
	}
	/*char temp[2048];
	ZeroMemory(temp, sizeof(temp));
	sprintf_s(temp, sizeof(temp), "SELECT password FROM `test_db`.`account_test` WHERE account = '%s'", account);*/
	std::string result;
	MainDB.Lock();
	/*q.prepare("SELECT password FROM `accounts` WHERE account = ':account'"); //INSERT IGNORE INTO `accounts` (`account`, `password`) VALUES ('amb5', 'test');
	q.bindValue(":account", account);
	q.exec();*/
	q.exec(Query("SELECT `password` FROM `accounts` WHERE `account` = '%s'", account).c_str());
	if(q.next())
	{
		result = q.value(0).toString().toStdString();
	}
	MainDB.Unlock();
	std::string passw;
	passw.clear();
	passw = pass;
	//passw.append(pass);
	if(!result.empty())
	{
		if(result == passw)
		{
			ZeroMemory(player->account, 10);
			strcpy_s(player->account, 10, account);
			//obj procs here
			player->status = PLAYER_LOGGED;
			player->SetStatus(1);
			JoinResult(player, 0x01);
			return;
		}
	}
	player->failed_attempts++;
	if(player->failed_attempts > 3)
	{
		JoinResult(player, 0x08);
		return;
	}
	JoinResult(player, 0x02);
	return;
}

void Join_CreateCharacter(PMSG_CHARCREATE * data, CPlayer* player)
{
	unsigned char Eq[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x74};
	PMSG_CHARCREATERESULT packet;
	ZeroMemory(&packet, sizeof(PMSG_CHARCREATERESULT));
	packet.h.c = 0xC1;
	packet.h.size = sizeof(PMSG_CHARCREATERESULT);
	packet.h.headcode = 0xF3;
	packet.subcode = 0x01;
	//packet.Class = 0x00;
	packet.Level = 1;
	uint8 char_class = data->ClassSkin / 16;
	DEFAULTCLASSTYPE * cl = &DCInfo.DefClass[char_class];
	QSqlQuery q;
	int have_chars = 0;
	MainDB.Lock();
	q.exec(Query("SELECT `guid` FROM `characters` WHERE `account` = '%s'", player->account).c_str());
	while(q.next())
	{
		have_chars++;
	}
	MainDB.Unlock();
	if(have_chars >= 5)
	{
		packet.Result = 0;
		player->Send((unsigned char*)&packet, packet.h.size);
		return;
	}
	MainDB.Lock();
	q.exec(Query("SELECT `guid` FROM `characters` WHERE `name` = '%s'", data->Name).c_str());
	bool name_used = false;
	if(q.next())
	{
		name_used = true;
	}
	MainDB.Unlock();
	if(name_used)
	{
		packet.Result = 2;
		player->Send((unsigned char*)&packet, packet.h.size);
		return;
	}
	bool result = q.exec(Query("INSERT INTO `characters` (`guid`, `account`, `name`, `position`, `level`, `strength`, `dexterity`, `vitality`, `energy`, `leadership`, `life`, `mana`, `shield`, `bp`, `money`, `class`) values (%u, '%s', '%s', %u, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)",
		CObjectManager::GetFreePlayerGuid(), player->account, data->Name, 0x82820000, 1, cl->Strength, cl->Dexterity, cl->Vitality, cl->Energy, cl->Leadership, (int)(cl->Life), (int)(cl->Mana), 90, 90, 1000, char_class).c_str());
	if(!result)
	{
		packet.Result = 2;
		player->Send((unsigned char*)&packet, packet.h.size);
		return;
	}
	packet.Result = 0x01;
	memcpy(packet.Equipment, Eq, 24);
	packet.Equipment[0] = ((data->ClassSkin / 0x10) * 0x20) & 0xE0;
	packet.pos = have_chars;
	strcpy_s((char*)packet.Name, 10, data->Name);
	player->Send((unsigned char*)&packet, packet.h.size);
	player->LoadSelectionScreen();
}

void World_Move(PMSG_MOVE* data, CPlayer* player)
{
	if(((GetTickCount() - player->last_move_time) >= 100) && !player->teleporting)
	{
		MovePoint * old_pt;
		if(!player->path.empty())
		{
			old_pt = player->GetCurrentPosition();
			assert(old_pt != NULL);
			if(!player->CheckPacketPosition(data->X, data->Y))
			{
				player->SetPosition(old_pt->x, old_pt->y);
				return;
			}
		}
		//todo: skill checks
		uint8 x = data->X;;
		uint8 y = data->Y;
		player->rest = 0;
		player->dir = (data->Path[0] / 0x10);
		player->path_count = data->Path[0] & 0x0f;
		if(player->path_count > 15)
		{
			player->SetPosition(old_pt->x, old_pt->y);
			return;
		}

		uint8 new_path[16];
		ZeroMemory(new_path, sizeof(new_path));
		uint32 n = 0;
		for(uint32 i = 1; i < 8; ++i)
		{
			new_path[n] = (data->Path[i] & 0xf0) / 0x10;
			new_path[n + 1] = data->Path[i] & 0x0f;
			n += 2;
		}
		MovePoint first;
		first.time = GetTickCount();
		first.x = x;
		first.y = y;
		player->path.clear();
		player->path.push_back(first);
		for(uint32 i = 0; i < player->path_count; ++i)
		{
			x += RoadX[new_path[i]];
			y += RoadY[new_path[i]];
			if(!WorldMap[player->map].FreeToMove(x, y))
			{
				player->SetPosition(old_pt->x, old_pt->y);
				return;
			}
			MovePoint point;
			point.time = first.time + 300 * (i + 1);
			point.x = x;
			point.y = y;
			player->path.push_back(point);
		}
		//Blood castle specific code here
		player->target_x = x;
		player->target_y = y;
		PMSG_RECVMOVE packet;
		packet.h.c = 0xC1;
		packet.h.headcode = 0x1D;
		packet.h.size = sizeof(PMSG_RECVMOVE);
		packet.NumberH = HIBYTE(player->guid);
		packet.NumberL = LOBYTE(player->guid);
		packet.X = x;
		packet.Y = y;
		if(!player->CheckPosition())
		{
			player->SetPosition(old_pt->x, old_pt->y);
			return;
		}
		packet.Path = player->dir * 0x10;
		player->Send((unsigned char*)&packet, packet.h.size);
		player->SendToViewport((unsigned char*)&packet, packet.h.size);
		player->x_old = data->X;
		player->y_old = data->Y;
		player->x = x;
		player->y = y;
		player->viewstate = 0;
		player->last_move_time = GetTickCount();
	}
}

void World_Action(PMSG_ACTION* data, CPlayer* player)
{
	PMSG_ACTIONRESULT packet;
	ZeroMemory(&packet, sizeof(PMSG_ACTIONRESULT));
	packet.h.c = 0xC1;
	packet.h.headcode = 0x18;
	packet.h.size = sizeof(PMSG_ACTIONRESULT);
	player->dir = data->Dir;
	player->action = data->ActionNumber;
	packet.Dir = player->dir;
	packet.ActionNumber = player->action;
	packet.NumberH = HIBYTE(player->guid);
	packet.NumberL = LOBYTE(player->guid);
	packet.TargetNumberH = 0;
	packet.TargetNumberL = 0;
	switch(player->action)
	{
	case 0x80:
		{
			player->rest = 2;
			player->viewstate = player->action;
			break;
		}
	case 0x81:
		{
			player->rest = 3;
			player->viewstate = player->action;
			break;
		}
	case 0x82:
		{
			player->rest = 4;
			player->viewstate = player->action;
			break;
		}
	}
	player->SendToViewport((unsigned char*)&packet, packet.h.size);
}

void Player_Chat(PMSG_CHATDATA* data, CPlayer* player)
{
	//implemented only for debug commands processing
	if(data->chatmsg[0] == '.')
	{
		std::string chat_string = &(data->chatmsg[1]);
		char* next_token = NULL;
		char * teh_string = new char[chat_string.size() + 1];
		ZeroMemory(teh_string, chat_string.size() + 1);
		strcpy_s(teh_string, chat_string.size() + 1, chat_string.c_str());
		std::string cmd = strtok_s(teh_string, " ", &next_token);
		for(uint32 i = 0; i < MAX_COMMANDS; ++i)
		{
			std::string temp = commands[i].cmd;
			if(temp == cmd)
			{
				commands[i].command(player, chat_string);
				delete[] teh_string;
				return;
			}
		}
		delete[] teh_string;
	}
	else
	{
		Log.String("Chat NYI.");
	}
}

void Client_Time(PMSG_CLIENTTIME* data, CPlayer* player)
{
	if(player->state == PLAYER_PLAYING && ((data->Time - player->tick_count) < (19 * SECOND)))
	{
		Log.String("Client Time: %s time is smaller than 20 seconds.", player->socket->GetRemoteAddress());
		player->Close();
	}
	player->tick_count = data->Time;
}