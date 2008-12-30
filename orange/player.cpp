#include "stdafx.h"
#include ".\\utils.h"
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
	this->last_save_time = GetTickCount();
	this->failed_attempts = NULL;
	for(int i = 0; i < 108; ++i)
	{
		this->inventory[i].type = -1;
	}
	this->send_serial = NULL;
	this->viewport.resize(100);
	this->viewport.clear();
	this->tick_count = GetTickCount();
	this->last_move_time = GetTickCount();
	this->check_time = GetTickCount();
	this->pklevel = 0;
	this->rest = 0;

	this->experience = 0;
	this->leveluppoint = 0;
	this->money = 0;
	this->pklevel = 0;
	this->gmlevel = 0;
	this->addpoint = 0;
	this->maxaddpoint = 0;
	this->minuspoint = 0;
	this->maxminuspoint = 0;
	this->Class = 0;
	this->changeup = 0;

	ZeroMemory(this->account, sizeof(this->account));
	ZeroMemory(this->name, sizeof(this->name));
	ZeroMemory(this->charset, sizeof(this->charset));
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
	q->execute(AssembleQuery("UPDATE `account_test` SET `status` = %d WHERE `account` = '%s'", status, this->account));
	TestDB.db_mutex.Unlock();
}

int CPlayer::LoadCharacters()
{
	char seps[] = " ";
	ZeroMemory(this->charinfo, sizeof(DATA_CHARINFO) * 5);
	Query* q = TestDB.query;
	int count = 0;
	TestDB.db_mutex.Lock();
	q->get_result(AssembleQuery("SELECT `name`, `class`, `changeup`, `position`, `experience`, `leveluppoint`, `level`, `strength`, `dexterity`, `vitality`, `energy`, `leadership`, `life`, `mana`, `shield`, `bp`, `money`, `pklevel`, `gmlevel`, `addpoint`, `maxaddpoint`, `minuspoint`, `maxminuspoint`, `inventory_guids`, `spell_data`, `guild_data` FROM `characters` WHERE `account` = '%s'", this->account));
	while(q->fetch_row() && (count <= 4))
	{
		strcpy_s(this->charinfo[count].Account, 11, this->account);
		strcpy_s(this->charinfo[count].Name, 11, q->getstr());
		this->charinfo[count].Class = q->getuval();
		this->charinfo[count].ChangeUp = q->getuval();
		this->charinfo[count].Position = q->getuval();
		this->charinfo[count].Exp = q->getbigint();
		this->charinfo[count].LevelUpPoint = q->getuval();
		this->charinfo[count].Level = q->getuval();
		this->charinfo[count].Str = q->getuval();
		this->charinfo[count].Dex = q->getuval();
		this->charinfo[count].Vit = q->getuval();
		this->charinfo[count].Energy = q->getuval();
		this->charinfo[count].Leadership = q->getuval();
		this->charinfo[count].Life = q->getuval();
		this->charinfo[count].Mana = q->getuval();
		this->charinfo[count].Shield = q->getuval();
		this->charinfo[count].BP = q->getuval();
		this->charinfo[count].Money = q->getuval();
		this->charinfo[count].PkLevel = q->getuval();
		this->charinfo[count].GMLevel = q->getuval();
		this->charinfo[count].AddPoint = q->getuval();
		this->charinfo[count].MaxAddPoint = q->getuval();
		this->charinfo[count].MinusPoint = q->getuval();
		this->charinfo[count].MaxMinusPoint = q->getuval();
		std::string inventory_guids = q->getstr();
		this->charinfo[count].item_guids.clear();
		char* token = strtok((char*)inventory_guids.c_str(), seps);
		while(token != NULL)
		{
			int guid;
			sscanf_s(token, "%d", &guid);
			this->charinfo[count].item_guids.push_back(guid);
			token = strtok(NULL, seps);
		}
		//memcpy(this->charinfo[count].Spell_data, (q->getstr()), 1);
		//memcpy(this->charinfo[count].Guild_data, (q->getstr()), 1);
		q->getstr();
		q->getstr();
		count++;
	}
	q->free_result();
	TestDB.db_mutex.Unlock();
	for(int i = 0; i < count; ++i) //12 items for viewport
	{
		printf_s("guids %d\n", this->charinfo[i].item_guids.size());
		for(uint32 n = 0; n < this->charinfo[i].item_guids.size(); ++n)
		{
			DATA_ITEM ditem;
			bool result = LoadItem(&ditem, this->charinfo[i].item_guids.at(n));
			if(result && ditem.slot < 12)
			{
				memcpy(&this->charinfo[i].temp_inv[ditem.slot], &ditem, sizeof(DATA_ITEM));
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
			ItemByteConvert(data.ItemInfo, item->type, item->m_Option1, item->m_Option2, item->m_Option3, (unsigned char)item->level, (unsigned char)item->durability, item->m_NewOption, item->m_SetOption, item->m_JewelOfHarmonyOption, item->m_ItemOptionEx);
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
	if(!ItemManager.Instanciate(item))
	{
		item->type = -1;
		return;
	}
	item->guid = data->guid;
	item->type = data->type;
	item->level = data->level;
	item->durability = (float)data->durability;
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
		if((ObjManager.FindByGuid(this->viewport.at(i)) == obj) && (obj != NULL) && (obj->type > OBJECT_EMPTY))
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

void CPlayer::SetPosition(uint8 _x, uint8 _y)
{
	if((this->type != OBJECT_PLAYER) || (!this->CheckPacketTime()) || (this->teleporting))
	{
		return;
	}
	this->x = _x;
	this->y = _y;
	if(!((this->map >= 18) && (this->map <= 23))) //ChaosCastle Specific check here (blow time)
	{
		PMSG_RECV_POSISTION_SET data;
		data.h.c = 0xC1;
		data.h.size = sizeof(PMSG_RECV_POSISTION_SET);
		data.h.headcode = GC_RECV_POSITION_SET;
		data.NumberH = HIBYTE(this->guid);
		data.NumberL = LOBYTE(this->guid);
		data.X = _x;
		data.Y = _y;
		this->target_x = _x;
		this->target_y = _y;
		if(this->CheckPosition())
		{
			this->Send((uint8*)&data, sizeof(PMSG_RECV_POSISTION_SET));
			this->SendToViewport((uint8*)&data, sizeof(PMSG_RECV_POSISTION_SET));
			this->x_old = this->target_x;
			this->y_old = this->target_y;
		}
	}
}

bool CPlayer::SavePlayer()
{
	if(this->type != OBJECT_PLAYER)
	{
		return false;
	}
	this->last_save_time = GetTickCount();
	Query* q = TestDB.query;
	uint32 position = this->dir;
	position |= this->map * 100;
	position |= this->y * 10000;
	position |= this->x * 1000000;
	TestDB.db_mutex.Lock();
	bool result = q->execute(AssembleQuery("UPDATE `characters` SET `class` = %u, `changeup` = %u, `position` = %u, `experience` = %I64u, `leveluppoint` = %u, `level` = %u, `strength` = %u, `dexterity` = %u, `vitality` = %u, `energy` = %u, `leadership` = %u, `life` = %u, `mana` = %u, `shield` = %u, `bp` = %u, `money` = %u, `pklevel` = %u, `gmlevel` = %u, `addpoint` = %u, `maxaddpoint` = %u, `minuspoint` = %u, `maxminuspoint` = %u;", this->Class, this->changeup, position, this->experience, this->leveluppoint, this->level, this->strength, this->dexterity, this->vitality, this->energy, this->leadership, (uint32)this->life, (uint32)this->mana, (uint32)this->shield, (uint32)this->bp, this->money, this->pklevel, this->gmlevel, this->addpoint, this->maxaddpoint, this->minuspoint, this->maxminuspoint));
	TestDB.db_mutex.Unlock();
	if(result)
	{
		std::string inv;
		inv.clear();
		for(uint32 i = 0; i < 108; ++i)
		{
			if(this->inventory[i].IsItem())
			{
				char temp[16];
				ZeroMemory(temp, sizeof(temp));
				sprintf_s(temp, sizeof(temp), "%u ", this->inventory[i].guid);
				if(ItemManager.SaveItem(&(this->inventory[i]), i))
				{
					inv.append(temp);
				}
			}
		}
		TestDB.db_mutex.Lock();
		result = q->execute(AssembleQuery("UPDATE `characters` SET `inventory_guids` = '%s';", inv.c_str()));
		TestDB.db_mutex.Unlock();
		if(!result)
		{
			printf_s("Inventory save failed %s:%s\n", this->account, this->name);
		}
	}
	else
	{
		printf_s("Character save failed %s:%s\n", this->account, this->name);
		return false;
	}
	return true;
}