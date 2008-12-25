#include "stdafx.h"
#include "..\\Deathway\\SimpleModulus\\SimpleModulus.h"
#include ".\\DataBase.h"
#include ".\\packets.h"
#include ".\\ItemManager.h"
#include ".\\objectmanager.h"
#include ".\\player.h"

CPlayer::CPlayer()
{
	this->socket = NULL;
	this->status = PLAYER_EMPTY;
	this->type = OBJECT_PLAYER;
	this->guid = -1;
	this->tick_count = GetTickCount();
	this->failed_attempts = NULL;
	for(int i = 0; i < 108; ++i)
	{
		this->inventory[i].m_Type = -1;
	}
	this->send_serial = NULL;
	this->viewport.resize(100);
	this->viewport.clear();
	this->tick_count = GetTickCount();
	this->last_move_time = GetTickCount();
	this->check_time = GetTickCount();
	this->teleporting = false;
}

void CPlayer::Send(unsigned char* buffer, size_t len)
{
	unsigned char in_buffer[16384];
	unsigned char send_buffer[16384];
	ZeroMemory(in_buffer, sizeof(in_buffer));
	ZeroMemory(send_buffer, sizeof(send_buffer));
	memcpy(in_buffer, buffer, len);

	int ret;
	unsigned char btsize;

	unsigned char code = buffer[0];
	switch(code)
	{
	case 0xC1:
		{
			this->socket->SendBuf((const char*)in_buffer, len);
			break;
		}
	case 0xC2:
		{
			this->socket->SendBuf((const char*)in_buffer, len);
			break;
		}
	case 0xC3:
		{
			btsize = in_buffer[1];
			in_buffer[1] = this->send_serial;
			this->send_serial++;

			ret = g_SimpleModulusSC.Encrypt(&send_buffer[2], &in_buffer[1], len - 1);
			send_buffer[0] = 0xC3;
			send_buffer[1] = ret + 2;
			size_t size = ret + 2;
			in_buffer[1] = btsize;
			this->socket->SendBuf((const char*)send_buffer, size);
			break;
		}
	case 0xC4:
		{
			btsize = in_buffer[2];
			in_buffer[2] = this->send_serial;
			this->send_serial++;
			ret = g_SimpleModulusSC.Encrypt(&send_buffer[3], &in_buffer[2], len - 2);
			send_buffer[0] = 0xC4;
			send_buffer[1] = HIBYTE(ret + 3);
			send_buffer[2] = LOBYTE(ret + 3);
			size_t size = ret + 3;
			in_buffer[2] = btsize;
			this->socket->SendBuf((const char*)send_buffer, size);
			break;
		}
	default:
		{
			break;
		}
	}
	//this->socket->SendBuf((const char*)buffer, len);
}

void CPlayer::Close()
{
	ServerSocket * s = this->socket;
	TcpSocket * tcp = dynamic_cast<TcpSocket *>(s);
	if(tcp)
	{
		tcp->SetCloseAndDelete();
	}
}

void CPlayer::SetStatus(unsigned char status)
{
	Query * q = TestDB.query;
	TestDB.db_mutex.Lock();
	q->execute(TestDB.AssembleQuery("UPDATE `account_test` SET `status` = %d WHERE `account` = '%s'", status, this->account));
	TestDB.db_mutex.Unlock();
}

int CPlayer::LoadCharacters()
{
	char seps[] = " ";
	ZeroMemory(this->charinfo, sizeof(DATA_CHARINFO) * 5);
	Query* q = TestDB.query;
	int count = 0;
	TestDB.db_mutex.Lock();
	q->get_result(TestDB.AssembleQuery("SELECT `name`, `class`, `changeup`, `position`, `experience`, `leveluppoint`, `level`, `strength`, `dexterity`, `vitality`, `energy`, `leadership`, `life`, `mana`, `shield`, `bp`, `money`, `pklevel`, `gmlevel`, `addpoint`, `maxaddpoint`, `minuspoint`, `maxminuspoint`, `inventory_guids`, `spell_data`, `guild_data` FROM `characters` WHERE `account` = '%s'", this->account));
	while(q->fetch_row() && (count <= 4))
	{
		strcpy_s(this->charinfo[count].Account, 11, this->account);
		strcpy_s(this->charinfo[count].Name, 11, q->getstr());
		this->charinfo[count].Class = q->getval();
		this->charinfo[count].ChangeUp = q->getval();
		this->charinfo[count].Position = q->getuval();
		this->charinfo[count].Exp = q->getval();
		this->charinfo[count].LevelUpPoint = q->getval();
		this->charinfo[count].Level = q->getval();
		this->charinfo[count].Str = q->getval();
		this->charinfo[count].Dex = q->getval();
		this->charinfo[count].Vit = q->getval();
		this->charinfo[count].Energy = q->getval();
		this->charinfo[count].Leadership = q->getval();
		this->charinfo[count].Life = q->getval();
		this->charinfo[count].Mana = q->getval();
		this->charinfo[count].Shield = q->getval();
		this->charinfo[count].BP = q->getval();
		this->charinfo[count].Money = q->getval();
		this->charinfo[count].PkLevel = q->getval();
		this->charinfo[count].GMLevel = q->getval();
		this->charinfo[count].AddPoint = q->getval();
		this->charinfo[count].MaxAddPoint = q->getval();
		this->charinfo[count].MinusPoint = q->getval();
		this->charinfo[count].MaxMinusPoint = q->getval();
		std::string inventory_guids = q->getstr();
		//std::vector<int> guid_container;
		this->charinfo[count].item_guids.clear();
		char* token = strtok((char*)inventory_guids.c_str(), seps);
		while(token != NULL)
		{
			int guid;
			sscanf_s(token, "%d", &guid);
			this->charinfo[count].item_guids.push_back(guid);
			token = strtok(NULL, seps);
		}
		/*for(int i = 0; i < this->charinfo[count].item_guids.size(); ++i)
		{
			DATA_ITEM item;
			ZeroMemory(&item, sizeof(item));
			if(LoadItem(&item, this->charinfo[count].item_guids.at(i)))
			{
				this->charinfo[count].items.push_back(item);
			}
		}*/
		memcpy(this->charinfo[count].Spell_data, (q->getstr()), 1);
		memcpy(this->charinfo[count].Guild_data, (q->getstr()), 1);
		count++;
	}
	q->free_result();
	TestDB.db_mutex.Unlock();
	for(int i = 0; i < count; ++i)
	{
		printf_s("guids %d\n", this->charinfo[i].item_guids.size());
		for(uint32 n = 0; n < this->charinfo[i].item_guids.size(); ++n)
		{
			DATA_ITEM item;
			ZeroMemory(&item, sizeof(item));
			if(LoadItem(&item, this->charinfo[i].item_guids.at(n)))
			{
				this->charinfo[i].items.push_back(item);
			}
		}
	}
	return count;
}

void CPlayer::SendInventory()
{
	PMSG_INVENTORYLISTCOUNT phead;
	ZeroMemory(&phead, sizeof(PMSG_INVENTORYLISTCOUNT));
	unsigned char buffer[4096];
	ZeroMemory(buffer, sizeof(buffer));
	size_t offs = sizeof(PMSG_INVENTORYLISTCOUNT);
	int count = 0;
	for(int i = 0; i < 108; ++i)
	{
		CItem * item = &(this->inventory[i]);
		if(item->IsItem())
		{
			count++;
			PMSG_INVENTORYLIST data;
			data.Pos = i;
			ItemByteConvert(data.ItemInfo, item->m_Type, item->m_Option1, item->m_Option2, item->m_Option3, (unsigned char)item->m_Level, (unsigned char)item->m_Durability, item->m_NewOption, item->m_SetOption, item->m_JewelOfHarmonyOption, item->m_ItemOptionEx);
			memcpy(&buffer[offs], &data, sizeof(PMSG_INVENTORYLIST));
			offs += sizeof(PMSG_INVENTORYLIST);
		}
	}
	phead.h.c = 0xC4;
	phead.h.sizeH = HIBYTE(offs);
	phead.h.sizeL = LOBYTE(offs);
	phead.h.headcode = 0xF3;
	phead.subcode = 0x10;
	phead.Count = count;
	memcpy(buffer, &phead, sizeof(PMSG_INVENTORYLISTCOUNT));
	this->Send(buffer, offs);
}

void CPlayer::AssignItem(DATA_ITEM *data)
{
	CItem * item =  &this->inventory[data->slot];
	item->m_Number = data->guid;
	item->m_Type = data->type;
	item->m_Level = data->level;
	item->m_Durability = (float)data->durability;
	item->m_Option1 = data->option1;
	item->m_Option2 = data->option2;
	item->m_Option3 = data->option3;
	item->m_NewOption = data->newoption;
	item->m_SetOption = data->setoption;
	item->m_JewelOfHarmonyOption = data->joh_option;
	item->m_ItemOptionEx = data->optionex;
	item->m_PetItem_Exp = data->petitem_exp;
	item->m_PetItem_Level = data->petitem_level;
}

bool CPlayer::InViewport(CObject *obj)
{
	for(uint32 i = 0; i < this->viewport.size(); ++i)
	{
		if((ObjManager.FindByGuid(this->viewport.at(i)) == obj) && (obj != NULL))
		{
			return true;
		}
	}
	return false;
}

/*void CPlayer::DeleteFromViewport(void* obj)
{
	for(uint32 i = 0; i < this->viewport.size(); ++i)
	{
		if(obj == this->viewport.at(i))
		{
			this->viewport.erase(this->viewport.begin() + i);
			printf_s("deleted %p\n", obj);
			return;
		}
	}
}*/

void CPlayer::SendToViewport(unsigned char* buffer, size_t len)
{
	for(uint32 i = 0; i < this->viewport.size(); ++i)
	{
		CObject* object = ObjManager.FindByGuid(this->viewport.at(i));
		if((object) && (object->type == OBJECT_PLAYER))
		{
			((CPlayer*)object)->Send(buffer, len);
		}
	}
}

bool CPlayer::CheckPosition()
{
	if((abs(this->target_x - this->x_old) < 15) && (abs(this->target_y - this->y_old) < 15))
	{
		return true;
	}
	return false;
}

bool CPlayer::CheckPacketTime()
{
	if((GetTickCount() - this->check_time) >= 300)
	{
		return true;
	}
	return false;
}