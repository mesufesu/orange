#include "stdafx.h"
#include ".\\DataBase.h"
#include ".\\utils.h"
#include ".\\classdef.h"
#include ".\\WorldMap.h"
#include ".\\protocol.h"

void ProtocolCore(CPlayer* player, unsigned char opcode, unsigned char* buffer, size_t size, bool Encrypt, int serial)
{
	switch(buffer[0])
	{
	case 0xC1:
		{
			if(buffer[1] != size)
			{
				printf_s("Packet size mismatch %d\n", (int)(buffer[1] - size));
			}
			break;
		}
	case 0xC2:
		{
			if((buffer[1] * 256 + buffer[2]) != size)
			{
				printf_s("Packet size mismatch %d\n", (int)((buffer[2] + buffer[2] * 256) - size));
			}
			break;
		}
	}
	printf_s("Got packet %02x size %02x %02x:\n", opcode, size, buffer[1]);
	for(uint32 i = 0; i < size; ++i)
	{
		printf_s("%02x ", buffer[i]);
	}
	printf_s("\n");

	if(size)
	{

		switch(opcode)
		{
		case 0x18:
			{
				if(size != sizeof(PMSG_ACTION))
				{
					printf_s("Size mismatch %d:%d %02X\n", size, sizeof(PMSG_ACTION), opcode);
				}
				World_Action((PMSG_ACTION*)buffer, player);
				break;
			}
		case 0x1D:
			{
				if(size != sizeof(PMSG_MOVE))
				{
					printf_s("Size mismatch %d:%d %02X\n", size, sizeof(PMSG_MOVE), opcode);
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
						printf_s("Unhandled F1 %02x packet.\n", buffer[3]);
						break;
					}
				case 0x03:
					{
						printf_s("Unhandled F1 %02x packet.\n", buffer[3]);
						break;
					}
				default:
					{
						printf_s("Unhandled F1 %02x packet.\n", buffer[3]);
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
						printf_s("Unhandled F3 %02x packet.\n", buffer[3]);
						break;
					}
				}
				break;
			}
		case 0x0E:
			{
				PMSG_CLIENTTIME clitime;
				memcpy(&clitime, buffer, sizeof(PMSG_CLIENTTIME));
				printf_s("%d\n", clitime.Time);
				printf_s("%d\n", clitime.MagicSpeed);
				printf_s("%d\n", clitime.AttackSpeed);
				break;
			}
		default:
			{
				printf_s("Unhandled opcode %02x\n", opcode);
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

	//char temp[2048];
	//ZeroMemory(temp, sizeof(temp));

	Query* q = TestDB.query;
	PMSG_CHARLISTCOUNT data;
	data.h.c = 0xC1;
	data.h.headcode = 0xF3;
	data.subcode = 0;
	data.MaxClass = 5; //need calculation;
	data.MoveCnt = 0;
	PMSG_CHARLIST chars[5];
	ZeroMemory(chars, (sizeof(PMSG_CHARLIST) * 5));

	int count = player->LoadCharacters();
	for(int i =0; i < count; ++i)
	{
		strcpy_s(chars[i].Name, 10, player->charinfo[i].Name);
		chars[i].Level = player->charinfo[i].Level;
		chars[i].Index = i;
		chars[i].CtlCode = player->charinfo[i].GMLevel; //incorrect, but...
		chars[i].CharSet[0] = (32 * (char)(player->charinfo[i].Class)) & 0xE0;
		switch(player->charinfo[i].ChangeUp)
		{
		case 0:
		case 1:
			{
				chars[i].CharSet[0] |= (16 * (char)(player->charinfo[i].ChangeUp)) & 0x10;
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
	for(int i = 0; i < count; ++i)
	{
		memcpy(&buffer[offs], &chars[i], sizeof(PMSG_CHARLIST));
		offs += sizeof(PMSG_CHARLIST);
	}
	player->Send((unsigned char*)buffer, data.h.size);
}

void Join_WorldJoin(PMSG_CHARMAPJOIN* data, CPlayer* player)
{
	player->LoadCharacters();
	int num = -1;
	for(int i = 0; i < 5; ++i)
	{
		if(!strcmp(data->Name, player->charinfo[i].Name))
		{
			num = i;
			break;
		}
	}
	DATA_CHARINFO * ch = &(player->charinfo[num]);
	Query* q = TestDB.query;
	PMSG_CHARMAPJOINRESULT result;
	ZeroMemory(&result, sizeof(result));
	result.h.c = 0xC3;
	result.h.size = sizeof(PMSG_CHARMAPJOINRESULT);
	result.h.headcode = 0xF3;
	result.subcode = 0x03;

	result.MapX = (char)((ch->Position >> 24) & 0x00ffffff);
	result.MapY = (char)((ch->Position >> 16) & 0x0000ffff);
	result.MapNumber = (char)((ch->Position >> 8) & 0x000000ff);
	result.Dir = (char)((ch->Position) & 0x000000ff);
	result.Exp = ch->Exp;
	result.NextExp = ch->Exp * 2; //need calculation
	result.LevelUpPoint = ch->LevelUpPoint;
	result.Str = ch->Str;
	result.Dex = ch->Dex;
	result.Vit = ch->Vit;
	result.Energy = ch->Energy;
	result.Life = ch->Life;
	result.MaxLife = (unsigned short)(DCInfo.DefClass[ch->Class].VitalityToLife * ch->Vit + DCInfo.DefClass[ch->Class].LevelLife * ch->Level);
	result.Mana = ch->Mana;
	result.MaxMana = (unsigned short)(DCInfo.DefClass[ch->Class].EnergyToMana * ch->Energy + DCInfo.DefClass[ch->Class].LevelMana * ch->Level);
	result.wMaxShield = ch->Shield + 10;
	result.BP = ch->BP;
	result.MaxBP = ch->BP + 10;
	result.Money = ch->Money;
	result.PkLevel = ch->PkLevel;
	result.CtlCode = ch->GMLevel; //wrong, but for now...
	result.AddPoint = ch->AddPoint;
	result.MaxAddPoint = ch->MaxAddPoint;
	result.wMinusPoint = ch->MinusPoint;
	result.wMaxMinusPoint = ch->MaxMinusPoint;
	result.unk3 = 0x005c; //1.3.2 sniffed from war 12 lvl
	//a lot of trash must be done here

	player->x = result.MapX;
	player->y = result.MapY;
	player->x_old = player->x;
	player->y_old = player->y;
	player->target_x = player->x;
	player->target_y = player->y;
	memcpy(player->name, data->Name, 10);

	player->map = result.MapNumber;
	for(uint32 i = 0; i < ch->items.size(); ++i)
	{
		player->AssignItem(&ch->items.at(i));
	}
	player->Send((unsigned char*)&result, result.h.size);
	player->SendInventory();
	player->status = PLAYER_PLAYING;
	//and here =)
}

void Join_LoginHandler(PMSG_IDPASS* data, CPlayer* player)
{
	int status = -1;
	Query* q = TestDB.query;
	char pass[11];
	char account[11];
	ZeroMemory(pass, sizeof(pass));
	ZeroMemory(account, sizeof(account));
	memcpy(pass, data->Pass, 10);
	memcpy(account, data->Id, 10);
	xor3((unsigned char*)pass, 10);
	xor3((unsigned char*)account, 10);
	TestDB.db_mutex.Lock();
	status = q->get_count(TestDB.AssembleQuery("SELECT `status` FROM `account_test` WHERE `account` = '%s'", account));
	TestDB.db_mutex.Unlock();
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
	TestDB.db_mutex.Lock();
	std::string result = q->get_string((TestDB.AssembleQuery("SELECT password FROM `test_db`.`account_test` WHERE account = '%s'", account)));
	TestDB.db_mutex.Unlock();
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
	unsigned char Eq[] = {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x74};
	PMSG_CHARCREATERESULT packet;
	ZeroMemory(&packet, sizeof(PMSG_CHARCREATERESULT));
	packet.h.c = 0xC1;
	packet.h.size = sizeof(PMSG_CHARCREATERESULT);
	packet.h.headcode = 0xF3;
	packet.subcode = 0x01;
	packet.Class = 0x00;
	packet.Level = 1;
	uint8 char_class = data->ClassSkin / 16;
	DEFAULTCLASSTYPE * cl = &DCInfo.DefClass[char_class];
	Query * q = TestDB.query;
	q->get_result(TestDB.AssembleQuery("SELECT `id` FROM `characters` WHERE `account` = '%s'", player->account));
	int have_chars = q->num_rows();
	q->free_result();
	if(have_chars >= 5)
	{
		packet.Result = 0;
		player->Send((unsigned char*)&packet, packet.h.size);
		return;
	}
	q->get_result(TestDB.AssembleQuery("SELECT `id` FROM `characters` WHERE `name` = '%s'", data->Name));
	int name_used = q->num_rows();
	q->free_result();
	if(name_used)
	{
		packet.Result = 2;
		player->Send((unsigned char*)&packet, packet.h.size);
		return;
	}
	q->execute(TestDB.AssembleQuery("INSERT INTO `characters` (`account`, `name`, `position`, `level`, `strength`, `dexterity`, `vitality`, `energy`, `leadership`, `life`, `mana`, `shield`, `bp`, `money`, `inventory_guids`, `class`) values ('%s', '%s', %u, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, '0', %d)",
		player->account, data->Name, 0x82820000, 1, cl->Strength, cl->Dexterity, cl->Vitality, cl->Energy, cl->Leadership, (int)(cl->Life), (int)(cl->Mana), 90, 90, 1000, char_class));
	packet.Result = 0x01;
	memcpy(packet.Equipment, Eq, 24);
	packet.Equipment[0] = data->ClassSkin;
	packet.pos = have_chars;
	strcpy_s((char*)packet.Name, 10, data->Name);
	player->Send((unsigned char*)&packet, packet.h.size);
}

void World_Move(PMSG_MOVE* data, CPlayer* player)
{
	if((GetTickCount() - player->last_move_time) && !player->teleporting)
	{
		short x; // = data->X;
		short y; // = data->Y;
		player->rest = 0;
		player->path_current = 0;
		player->dir = (data->Path[0] / 0x10);
		player->path_count = data->Path[0] & 0x0f;
		if(player->path_count > 15)
		{
			return;
		}
		for(uint32 i = 0; i < 15; ++i)
		{
			player->path_original[i] = 0;
			player->path_x[i] = 0;
			player->path_y[i] = 0;
		}
		player->path_x[0] = data->X;
		player->path_y[0] = data->Y;
		x = player->path_x[0];
		y = player->path_y[0];
		player->path_dir[0] = player->dir;
		player->path_start_end = 1;
		if(player->path_count > 0)
		{
			player->path_current = 1;
			player->path_count++; 
		}
		short pathtable = 0;
		unsigned char * pdata = (unsigned char*)data;
		for(uint32 i = 1; i < player->path_count; ++i)
		{
			if(i % 2 == 1)
			{
				pathtable = *(pdata + (i + 1) / 2 + 5) * 0x10;
			}
			else
			{
				pathtable = *(pdata + (i + 1) / 2 + 5) & 0x0f; //a fucking mess, todo: simplify
			}
			x += RoadPathTable[2* pathtable];
			y += RoadPathTable[1 + 2* pathtable];
			player->path_original[i - 1] = pathtable;
			player->path_dir[i] = pathtable;
			player->path_x[i] = x;
			player->path_y[i] = y;
		}
		uint8 attr = WorldMap[player->map].GetAttr(x, y);
		//Blood castle specific code here
		if(!(attr & 8) && !(attr & 4))
		{
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
				player->path_count = 0;
				player->path_current = 0;
				player->target_x = player->x;
				player->target_y = player->y;
				packet.X = player->x;
				packet.Y = player->y;
			}
			packet.Path = player->dir * 0x10;
			player->Send((unsigned char*)&packet, packet.h.size);
			player->SendToViewport((unsigned char*)&packet, packet.h.size);
			player->x_old = player->target_x;
			player->y_old = player->target_y;
			player->x = x;
			player->y = y;
			player->viewstate = 0;
			player->last_move_time = GetTickCount();
		}
	}
	else
	{
		//nyi
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