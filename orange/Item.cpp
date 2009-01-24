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
#include ".\\Item.h"
#include ".\\utils.h"

CItem::CItem()
{
	this->guid = 0;
	this->type = -1;
	this->level = 0;
	this->part = 0;
	this->Class = 0;
	this->two_hand = false;
	this->attack_speed = 0;
	this->damage_min = 0;
	this->damage_max = 0;
	this->block = 0;
	this->defense = 0;
	this->magic_defense = 0;
	this->durability = 0.0f;
	this->m_SpecialNum = 0;
	this->m_Value = 0;
	this->m_Option1 = 0;
	this->m_Option2 = 0;
	this->m_Option3 = 0;
	this->m_NewOption = 0;
	this->m_DurabilitySmall = 0;
	this->m_iPShopValue = -1;
	this->m_bItemExist = true;
	this->m_CurrentDurabilityState = 0xBF800000;
	this->m_SetOption = 0;
	this->m_QuestItem = 0;
	ZeroMemory(&(this->m_Special), sizeof(CItem::m_Special));
	ZeroMemory(&(this->m_SpecialValue), sizeof(CItem::m_SpecialValue));
	ZeroMemory(&(this->m_Resistance), sizeof(CItem::m_Resistance));
	this->m_IsLoadPetItemInfo = 0;
	this->m_PetItem_Level = 1;
	this->m_PetItem_Exp = 0;
	this->m_Leadership = 0;
	this->m_JewelOfHarmonyOption = 0;
	this->m_ItemOptionEx = 0;
	this->status = ITEM_UNCHANGED;
}

bool CItem::IsItem()
{
	if(this->type >= 0)
	{
		return true;
	}
	return false;
}

bool CItem::IsExtItem()
{
	if((this->type >=0) && (this->type != (13 * 512 + 37)) && (this->m_NewOption & 0x7F)) //Horn of fenrir
	{
		return true;
	}
	return false;
}

bool CItem::IsSetItem()
{
	if((this->type >= 0) && (this->m_SetOption & 3))
	{
		return true;
	}
	return false;
}

void ItemByteConvert(unsigned char* buf, int type, unsigned char Option1, unsigned char Option2, unsigned char Option3, unsigned char level, unsigned char dur, unsigned char Noption, unsigned char SetOption, unsigned char JewelOfHarmonyOption, unsigned char ItemEffectEx)
{
	ZeroMemory(buf, 12);
	buf[0] = LOBYTE(type);
	buf[1] = 0;
	buf[1] |= 8 * LOBYTE(level);
	buf[1] |= 128 * LOBYTE(Option1);
	buf[1] |= 4 * LOBYTE(Option2);
	buf[1] |= (LOBYTE(Option3) & 3);
	buf[2] = LOBYTE(dur);
	buf[3] = 0;
	buf[3] |= LOBYTE((type & 0x100) / 2); //incorrect
	if(LOBYTE(Option3) > 3)
	{
		buf[3] |= 0x40;
	}
	buf[3] |= Noption;
	buf[4] = SetOption;
	buf[5] |= (type & 0x1e00) / 32; //correct
	buf[5] |= (LOBYTE(ItemEffectEx) & 0x80) / 16;
	buf[6] = JewelOfHarmonyOption;

	buf[7] = 0xff;
	buf[8] = 0xff;
	buf[9] = 0xff;
	buf[10] = 0xff;

	buf[11] = 0xff;

		/*[0x7]	0x0c ''	unsigned char
		[0x8]	0x14 ''	unsigned char
		[0x9]	0x08 ''	unsigned char
		[0xa]	0x1e ''	unsigned char

		[0xb]	0x00	unsigned char
		[0xc]	0x00	unsigned char
		[0xd]	0xd0 'Ð'	unsigned char
		[0xe]	0x00	unsigned char

		[0xf]	0xff 'ÿ'	unsigned char
		[0x10]	0xff 'ÿ'	unsigned char
		[0x11]	0xff 'ÿ'	unsigned char
		[0x12]	0xff 'ÿ'	unsigned char

		[0x13]	0xff 'ÿ'	unsigned char*/

}

void CItem::Assign(const DATA_ITEM *item_data)
{
	this->guid = item_data->guid;
	this->type = item_data->type;
	this->level = item_data->level;
	this->durability = (float)item_data->durability;
	this->m_Option1 = item_data->option1;
	this->m_Option2 = item_data->option2;
	this->m_Option3 = item_data->option3;
	this->m_NewOption = item_data->newoption;
	this->m_SetOption = item_data->setoption;
	this->m_JewelOfHarmonyOption = item_data->joh_option;
	this->m_ItemOptionEx = item_data->optionex;
	this->m_PetItem_Exp = item_data->petitem_exp;
	this->m_PetItem_Level = item_data->petitem_level;
}

bool CItem::ApplyTemplate(const ITEM_TEMPLATE *it)
{
	if(!it)
	{
		return false;
	}
	this->type = it->type;
	this->reqclass = it->CLASS_ATTR;
	this->reqstrength = it->strength;
	this->reqdexterity = it->dexterity;
	this->reqenergy = it->energy;
	this->reqvitality = it->vitality;
	this->reqleadership = it->leadership;
	this->reqlevel = it->reqlevel;
	this->durability = it->durability;
	this->base_durability = it->durability;

	switch(GetCategory(it->type))
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			{
				this->speed = (it->SPECIAL & 0xffffffLL) / 0x10000LL;
				this->damage_max = (it->SPECIAL & 0xffffffffLL) / 0x1000000LL;
				this->damage_min = (it->SPECIAL & 0xffffffffffLL) / 0x100000000LL;
				break;
			}
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
			{
				break;
			}
		}
	return true;
}