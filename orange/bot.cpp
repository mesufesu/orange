#include "stdafx.h"
#include "bot.h"
#include "WorldMap.h" 
#include "packets.h" 

CBot::CBot()
{
	this->status = PLAYER_EMPTY;
	this->type = OBJECT_BOT;
	this->tick_count = GetTicks();
	this->last_think_time = GetTicks();
	this->viewport.resize(100);
	this->viewport.clear();
	this->pklevel = 0;
	this->rest = 0;

	this->experience = 0;
	this->leveluppoint = 0;
	this->money = 0;
	this->pklevel = 0;
	this->addpoint = 0;
	this->maxaddpoint = 0;
	this->minuspoint = 0;
	this->maxminuspoint = 0;
	this->Class = 0;
	this->changeup = 0;

	ZeroMemory(this->name, sizeof(this->name));
	ZeroMemory(this->charset, sizeof(this->charset));
	this->CookCharset();
}

void CBot::Kick()
{
	this->type = VOID_BOT;
}

/*void CBot::UpdateAI()
{
	if((GetTickDiff(this->last_think_time)) >= 5000)
	{
		init_genrand(GetTicks());
		uint32 count = 0;
		while(count < 1000)
		{
			bool helpx = genrand_int32() % 2;
			bool helpy = genrand_int32() % 2;
			uint8 newx = this->x + (genrand_int32() % 4) * (helpx ? -1 : 1);
			uint8 newy = this->y + (genrand_int32() % 4) * (helpy ? -1 : 1);
			uint8 attr = WorldMap[this->map].GetAttr(newx, newy);
			if((!(attr & 0x04)) && (!(attr & 0x08)))
			{
				this->x_old = this->x;
				this->y_old = this->y;
				this->target_x = newx;
				this->target_y = newy;
				PMSG_RECVMOVE data;
				data.h.c = 0xC1;
				data.h.headcode = 0x1D;
				data.h.size = sizeof(PMSG_RECVMOVE);
				data.NumberH = HIBYTE(this->guid);
				data.NumberL = LOBYTE(this->guid);
				data.X = newx;
				data.Y = newy;
				data.Path = (genrand_int32() % 8) * 0x10;
				this->SendToViewport((uint8*)&data, data.h.size);
				this->x = newx;
				this->y = newy;
				break;
			}
		}
		this->last_think_time = GetTicks();
	}
}*/

void CBot::SetBot(const std::string& _name, uint8 _map, uint8 _x, uint8 _y)
{
	strcpy_s(this->name, sizeof(this->name), _name.c_str());
	this->map = _map;
	this->x = _x;
	this->y = _y;
	this->x_old = _x;
	this->y_old = _y;
	this->target_x = _x;
	this->target_y = _y;
}

void CBot::CookCharset()
{
	ZeroMemory(charset, 18);
	this->charset[0] = (this->Class * 0x20) & 0xE0; //0x100 - 0x20 = 0xE0
	this->charset[0] |= (this->changeup * 0x10) & 0x10;
	if(this->action == 0x80)
	{
		this->charset[0] |= 0x02;
	}
	else if(this->action == 0x81)
	{
		this->charset[0] |= 0x03;
	}
	if(this->inventory[RIGHT_HAND]->type >= 0)
	{
		this->charset[12] |= (this->inventory[RIGHT_HAND]->type & 0x0f00) / 0x10;  //12 char - highest 4 bits
		this->charset[1] = (this->inventory[RIGHT_HAND]->type & 0xff); //1 char both 4-bit fields
	}
	else //or -1;
	{
		this->charset[12] |= 0xf0;
		this->charset[1] = 0xff;
	}
	if(this->inventory[LEFT_HAND]->type >= 0)
	{
		this->charset[13] |= (this->inventory[LEFT_HAND]->type & 0x0f00) / 0x10;
		this->charset[2] = (this->inventory[LEFT_HAND]->type & 0xff);
	}
	else
	{
		this->charset[13] |= 0xf0;
		this->charset[2] = 0xff;
	}
	if(this->inventory[HELMET]->type >= 0)
	{
		this->charset[13] |= (this->inventory[HELMET]->type & 0x01E0) / 0x20;
		this->charset[9] |= (this->inventory[HELMET]->type & 0x10) * 0x08;
		this->charset[3] |= (this->inventory[HELMET]->type & 0x0f) * 0x10;
	}
	else
	{
		this->charset[13] |= 0x0f;
		this->charset[9] |= 0x80;
		this->charset[3] |= 0xf0;
	}
	if(this->inventory[ARMOR]->type >= 0)
	{
		this->charset[14] |= (this->inventory[ARMOR]->type & 0x01E0) / 0x02;
		this->charset[9] |= (this->inventory[ARMOR]->type & 0x10) * 0x04;
		this->charset[3] |= (this->inventory[ARMOR]->type &0x0f);
	}
	else
	{
		this->charset[14] |= 0xf0;
		this->charset[9] |= 0x40;
		this->charset[3] |= 0x0f;
	}
	if(this->inventory[PANTS]->type >= 0)
	{
		this->charset[14] |= (this->inventory[PANTS]->type & 0x01E0) / 0x20;
		this->charset[9] |= (this->inventory[PANTS]->type & 0x10) * 0x02;
		this->charset[4] |= (this->inventory[PANTS]->type & 0x0f) * 0x10;
	}
	else
	{
		this->charset[14] |= 0x0f;
		this->charset[9] |= 0x20;
		this->charset[4] |= 0xf0;
	}
	if(this->inventory[GLOVES]->type >= 0)
	{
		this->charset[15] |= (this->inventory[GLOVES]->type & 0x01E0) / 0x02;
		this->charset[9] |= (this->inventory[GLOVES]->type & 0x10);
		this->charset[4] |= (this->inventory[GLOVES]->type & 0x0f);
	}
	else
	{
		this->charset[15] |= 0xf0;
		this->charset[9] |= 0x10;
		this->charset[4] |= 0x0f;
	}
	if(this->inventory[BOOTS]->type >= 0)
	{
		this->charset[15] |= (this->inventory[BOOTS]->type & 0x01E0) / 0x20;
		this->charset[9] |= (this->inventory[BOOTS]->type & 0x10) / 0x02;
		this->charset[5] |= (this->inventory[BOOTS]->type & 0x0f) * 0x10;
	}
	else
	{
		this->charset[15] |= 0x0f;
		this->charset[9] |= 0x08;
		this->charset[5] |= 0xf0;
	}
	uint8 index = 0;
	if(this->inventory[WINGS]->type >= 0)
	{
		index |= (this->inventory[WINGS]->type & 0x03) * 0x04;
	}
	else
	{
		index |= 0x0c;
	}
	if((this->inventory[GUARDIAN]->type >= 0) && !(this->inventory[GUARDIAN]->type == 6660))
	{
		index |= (this->inventory[GUARDIAN]->type & 0x03);
	}
	else
	{
		index |= 0x03;
	}
	this->charset[5] |= index;
	uint32 levelindex = 0;
	levelindex = LevelConvert(this->inventory[RIGHT_HAND]->level) & 0xff;
	levelindex |= (LevelConvert(this->inventory[LEFT_HAND]->level) & 0xff) * 0x08;
	levelindex |= (LevelConvert(this->inventory[HELMET]->level) & 0xff) * 0x40;
	levelindex |= (LevelConvert(this->inventory[ARMOR]->level) & 0xff) * 0x200;
	levelindex |= (LevelConvert(this->inventory[PANTS]->level) & 0xff) * 0x1000;
	levelindex |= (LevelConvert(this->inventory[GLOVES]->level) & 0xff) * 0x8000;
	levelindex |= (LevelConvert(this->inventory[BOOTS]->level) & 0xff) * 0x40000;
	this->charset[6] = (levelindex / 0x10000) & 0xff;
	this->charset[7] = (levelindex / 0x100) & 0xff;
	this->charset[8] = (levelindex) & 0xff;
	if(((this->inventory[WINGS]->type >= (12 * 512 + 3)) && (this->inventory[WINGS]->type <= (12 * 512 + 6))) || (this->inventory[WINGS]->type == (13 * 512 + 30)))
	{
		this->charset[5] |= 0x0C;
		if(this->inventory[WINGS]->type == (13 * 512 + 30))
		{
			this->charset[5] |= 0x05;
		}
		else
		{
			this->charset[9] |= (this->inventory[WINGS]->type - 2) & 0x07;
		}
	}
	this->charset[10] = 0;
	if(this->inventory[HELMET]->IsExtItem())
	{
		this->charset[10] = 0x80;
	}
	if(this->inventory[ARMOR]->IsExtItem())
	{
		this->charset[10] |= 0x40;
	}
	if(this->inventory[PANTS]->IsExtItem())
	{
		this->charset[10] |= 0x20;
	}
	if(this->inventory[GLOVES]->IsExtItem())
	{
		this->charset[10] |= 0x10;
	}
	if(this->inventory[BOOTS]->IsExtItem())
	{
		this->charset[10] |= 0x8;
	}
	if(this->inventory[RIGHT_HAND]->IsExtItem())
	{
		this->charset[10] |= 0x4;
	}
	if(this->inventory[LEFT_HAND]->IsExtItem())
	{
		this->charset[10] |= 0x2;
	}
	this->charset[11] = 0;
	if(this->inventory[HELMET]->IsSetItem())
	{
		this->charset[11] = 0x80;
	}
	if(this->inventory[ARMOR]->IsSetItem())
	{
		this->charset[11] |= 0x40;
	}
	if(this->inventory[PANTS]->IsSetItem())
	{
		this->charset[11] |= 0x20;
	}
	if(this->inventory[GLOVES]->IsSetItem())
	{
		this->charset[11] |= 0x10;
	}
	if(this->inventory[BOOTS]->IsSetItem())
	{
		this->charset[11] |= 0x8;
	}
	if(this->inventory[RIGHT_HAND]->IsSetItem())
	{
		this->charset[11] |= 0x4;
	}
	if(this->inventory[LEFT_HAND]->IsSetItem())
	{
		this->charset[11] |= 0x2;
	}
	/*if(lpObj->IsFullSetItem)
	{
		lpObj->CharSet[11] |= 0x01;
	}*/
	if((this->inventory[GUARDIAN]->type & 3) && (this->inventory[GUARDIAN]->type >= 0))
	{
		this->charset[10] |= 0x01;
	}
	this->charset[16] = 0;
	this->charset[17] = 0;
	if(this->inventory[GUARDIAN]->type == (13 * 512 + 4)) //1a04
	{
		this->charset[12] |= 0x01;
	}
	else if(this->inventory[GUARDIAN]->type == 0x1A25) //horn of fenrir
	{
		this->charset[10] &= 0xFE;
		this->charset[12] &= 0xFE;
		this->charset[12] |= 0x04;
		//todo: unique fenrir checks
	}
}