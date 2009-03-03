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
#include "Item.h"
#include "utils.h"

CItem::CItem()
{
	this->guid = 0;
	this->type = -1;
	this->level = 0;
	this->part = 0;
	this->reqclass = CLASS_NONE;
	this->two_hand = false;
	this->attack_speed = 0;
	this->damage_min = 0;
	this->damage_max = 0;
	this->block = 0;
	this->defense = 0;
	this->magic_defense = 0;
	this->durability = 0.0f;
	this->m_Value = 0;
	this->option1 = 0;
	this->option2 = 0;
	this->option3 = 0;
	this->option_new = 0;
	this->m_iPShopValue = -1;
	this->state = 0.0f;
	this->m_SetOption = 0;
	this->m_QuestItem = 0;
	ZeroMemory(&(this->resistance), sizeof(this->resistance));
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
	if((this->type >=0) && (this->type != (13 * 512 + 37)) && (this->option_new & 0x7F)) //Horn of fenrir
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

/*void CItem::Assign(const DATA_ITEM *item_data)
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
}*/

/*bool CItem::ApplyTemplate(const ITEM_TEMPLATE *it)
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
}*/

void CItem::PlusSpecial(uint32 *value, uint32 special)
{
	if((this->type < 0) || (this->durability == 0.0f))
	{
		return;
	}
	for(uint32 i = 0; i < this->opt.size(); ++i)
	{
		if(this->opt.at(i) == special)
		{
			switch(special)
			{
			case 80:
			case 81:
			case 83:
				{
					*value += 4 * this->option3 - (4 * this->option3 * this->state);
					break;
				}
			case 82:
				{
					*value += 5 * this->option3 - (5 * this->option3 * this->state);
					break;
				}
			case 84:
				{
					*value += 4;
					break;
				}
			case 100:
			case 101:
				{
					*value += 5 * this->level + 50;
					break;
				}
			case 103:
				{
					*value += 50;
					break;
				}
			case 105:
				{
					*value += 5 * this->level + 10;
					break;
				}
			default:
				{
					*value += 4 * this->option3;
					break;
				}
			}
		}
	}
}

_ITEM_TYPE CItem::GetItemType()
{
	return (_ITEM_TYPE)(this->type / 512);
}

void CItem::Convert(uint32 _type, uint8 _option1, uint8 _option2, uint8 _option3, uint8 _option_new, uint8 _set_option, uint8 _effect_ex)
{
	_ITEM_TYPE cat = this->GetItemType();
	const ITEM_TEMPLATE * it = ItemTemplate.Get(type);
	this->type = _type;
	if(it->option && !(type >= 6147 && type <= 6150 || type == 6686 || type == 6693 || type == 19 || type == 2066 || type == 2570 || type == 1037))
	{
		this->option_new = option_new;
	}
	else
	{
		this->option_new = 0;
	}
	/* set options SKIPPED again =) */
	this->m_SetOption = 0;

	this->m_ItemOptionEx = _effect_ex;
	ZeroMemory(this->resistance, sizeof(this->resistance));

	uint8 chaos_item = 0;
	switch(type)
	{
	case 0x406:
		{
			chaos_item = 15;
			break;
		}
	case 0xa07:
		{
			chaos_item = 25;
			break;
		}
	case 0x806:
		{
			chaos_item = 35;
			break;
		}
	}

	this->base_durability = it->durability;
	this->durability_state[0] = this->base_durability * 0.5f;
	this->durability_state[1] = this->base_durability * 0.3f;
	this->durability_state[2] = this->base_durability * 0.2f;
	this->durability_state[3] = 0.0f;

	this->m_Value = 0; /* getted from template, its in SPECIAL, but i don't made it yet =) */
	this->attack_speed = 0; /* same =) */
	this->two_hand = 0; /* aha... */
	this->damage_min = 0; /* =\ */
	this->damage_max = 0; /* :O */
	this->block = 0; /* ... */
	this->defense = 0;
	this->magic_defense = 0;
	this->walk_speed = 0;
	this->spell_power = 0;
	this->m_QuestItem =0;
	this->reqcharisma = it->reqcharisma;

	if(this->durability == 0.0f)
	{
		this->state = 1.0f;
	}
	else if(this->durability < this->durability_state[2])
	{
		this->state = 0.5f;
	}
	else if(this->durability < this->durability_state[1])
	{
		this->state = 0.3f;
	}
	else if(this->durability < this->durability_state[0])
	{
		this->state = 0.2f;
	}
	else
	{
		this->state = 0.0f;
	}

	this->reqclass = (CLASS_ATTR)it->CLASS_ATTR;
	/* resistance is stored in SPECIAL =) */
	uint32 item_level = it->item_level;
	if(_option_new & 0x3F)
	{
		item_level += 25;
	}
	else
	{
		if(this->m_SetOption)
		{
			item_level += 25;
		}
	}
	if(it->reqstrength)
	{
		this->reqstrength = (3 * (this->level * 3 + item_level) * it->reqstrength / 100) + 20;
	}
	else
	{
		this->reqstrength = 0;
	}
	if(it->reqdexterity)
	{
		this->reqdexterity = (3 * (this->level * 3 + item_level) * it->reqdexterity / 100) + 20;
	}
	else
	{
		this->reqdexterity = 0;
	}
	if(it->reqenergy)
	{
		this->reqenergy = (3 * (this->level * 3 + item_level) * it->reqenergy / 100) + 20;
	}
	else
	{
		this->reqenergy = 0;
	}
	if(type >= 0 && type < 6144)
	{
		if(it->reqvitality)
		{
			this->reqvitality = (3 * (this->level * 3 + item_level) * it->reqvitality / 100) + 20;
		}
		else
		{
			this->reqvitality = 0;
		}
		if(it->reqcharisma)
		{
			this->reqcharisma = (3 * (this->level * 3 + item_level) * it->reqcharisma / 100) + 20;
		}
		else
		{
			this->reqcharisma = 0;
		}
	}
	if(type == 6661)
	{
		this->reqcharisma = 15 * this->m_PetItem_Level + 185;
	}
	/* joh skipped */

	if(it->reqlevel)
	{
		if(type == 6660)
		{
			this->reqlevel = 2 * this->m_PetItem_Level + 218;
		}
		else if(type < 6147 || type > 6150) /* need simplification */
		{
			if(type < 6151 || type > 6168)
			{
				if(type >= 6144)
				{
					this->reqlevel = it->reqlevel + 4 * this->level;
				}
				else if(it->reqlevel)
				{
					this->reqlevel = it->reqlevel;
				}
			}
			else
			{
				this->reqlevel = it->reqlevel;
			}
		}
		else
		{
			this->reqlevel = 5 * this->level + it->reqlevel;
		}
	}
	else
	{
		this->reqlevel = 0;
	}
	if(type == 6666)
	{
		if(item_level > 2)
		{
			this->reqlevel = 50;
		}
		else
		{
			this->reqlevel = 20;
		}
	}
	if(_option_new & 0x3f && this->reqlevel > 0 && type >= 6144)
	{
		this->reqlevel += 20;
	}
	if(this->m_SetOption)
	{
		item_level = it->item_level + 30;
	}
	if(this->damage_max)
	{
		if(this->m_SetOption && item_level)
		{
			this->damage_max += (25 * this->damage_min / it->item_level) + 5;
			this->damage_max += (item_level / 40) + 5;
		}
		else if(_option_new & 0x3f)
		{
			if(chaos_item)
			{
				this->damage_max += chaos_item;
			}
			else if(it->item_level)
			{
				this->damage_max += (25 * this->damage_min / it->item_level) + 5;
			}
		}
		this->damage_max += 3 * this->level;
		if(this->level > 10)
		{
			this->damage_max += (this->level - 8) * (this->level - 9) / 2;
		}
	}
	if(this->damage_min)
	{
		if(this->m_SetOption && item_level)
		{
			this->damage_min += (25 * this->damage_min / it->item_level) + 5;
			this->damage_min += (item_level / 40) + 5;
		}
		else if(_option_new & 0x3f)
		{
			if(chaos_item)
			{
				this->damage_min += chaos_item;
			}
			else if(it->item_level)
			{
				this->damage_min += (25 * this->damage_min / it->item_level) + 5;
			}
		}
		this->damage_min += 3 * this->level;
		if(this->level >= 10)
		{
			this->damage_min += (this->level - 8) * (this->level - 9) / 2;
		}
	}
	if(this->spell_power)
	{
		if(this->m_SetOption && item_level)
		{
			this->spell_power += (25 * this->spell_power / it->item_level) + 5;
			this->spell_power += (item_level / 60) + 2;
		}
		else if(_option_new & 0x3f)
		{
			if(chaos_item)
			{
				this->spell_power += chaos_item;
			}
			else if(it->item_level)
			{
				this->spell_power += (25 * this->spell_power / it->item_level) + 5;
			}
		}
		this->spell_power += 3 * this->level;
		if(this->level >= 10)
		{
			this->spell_power += (this->level - 8) * (this->level - 9) / 2;
		}
	}
	if(this->block) /* strange but webzen checks blocking from item_template, not from item itself */
	{
		if(this->m_SetOption && item_level)
		{
			this->block += (25 * this->block / it->item_level) + 5;
			this->block += (item_level / 40) + 5;
		}
		else if((_option_new & 0x3f) && it->item_level)
		{
			this->block += (25 * this->block / it->item_level) + 5;
		}
		this->block += 3 * this->level;
		if(this->level >= 10)
		{
			this->block += (this->level - 8) * (this->level - 9) / 2;
		}
	}
	if(this->defense) /* same */
	{
		if(this->GetItemType() == ITEM_SHIELD)
		{
			this->defense += this->level;
			if(item_level)
			{
				this->defense += (20 * this->defense / item_level) + 2;
			}
		}
		else
		{
			if(this->m_SetOption && item_level)
			{
				this->defense += (12 * this->defense / it->item_level) + (it->item_level / 5) + 4;
				this->defense += (3 * this->defense / item_level) + (item_level / 30) + 2; 
			}
			else if(_option_new & 0x3f)
			{
				if(it->item_level)
				{
					this->defense += (12 * this->defense / it->item_level) + (it->item_level / 5) + 4;
				}
			}
			if(!(type >= 6147 && type <= 6150) && type != 6686 && type != 6660)
			{
				this->defense += 3 * this->level;
			}
			else
			{
				this->defense += 2 * this->level;
			}
			if(this->level >= 10)
			{
				this->defense += (this->level - 8) * (this->level - 9) / 2;
			}
		}
	}
	if(type == 6686)
	{
		this->defense = 2 * this->level + 15;
		if(this->level >= 10)
		{
			this->defense += (this->level - 8) * (this->level - 9) / 2;
		}
	}
	if(this->magic_defense)
	{
		this->magic_defense += 3 * this->level;
		if(this->level >= 10)
		{
			this->magic_defense += (this->level - 8) * (this->level - 9) / 2;
		}
	}
	this->level &= 0x0f; /* in time ofc, above we calculated almost all item stats with old value, webzen... */
	opt.clear(); /* my innovation - special values list :D */
	this->option1 = 0;
	this->option2 = 0;
	this->option3 = 0;
	this->m_SkillChange = 0;
	if(_option1 && it->skill)
	{
		if(it->skill == 66)
		{
			this->m_SkillChange = 1;
			this->opt.push_back(0);
			this->option1 = 1;
		}
		else
		{
			this->opt.push_back(it->skill);
			this->option1 = 1;
		}
	}
	switch(this->type)
	{
	case 6659:
		{
			this->opt.push_back(49);
			this->option1 = 1;
			break;
		}
	case 6660:
		{
			this->opt.push_back(62);
			this->option1 = 1;
			break;
		}
	case 6693:
		{
			this->opt.push_back(76);
			this->option1 = 1;
			break;
		}
	}
	if(_option2)
	{
		if((this->type >= 0 && this->type <= 6150) || type == 6686)
		{
			this->opt.push_back(84);
			this->option2 = 1;
		}
	}
	if(_option3)
	{
		if(cat >= ITEM_SWORD && cat <= ITEM_BOW)
		{
			this->opt.push_back(80);
			this->option3 = _option3;
			this->reqstrength += 4 * _option3;
		}
		else if(cat == ITEM_STAFF)
		{
			this->opt.push_back(81);
			this->option3 = _option3;
			this->reqstrength += 4 * _option3;
		}
		else if(cat == ITEM_SHIELD)
		{
			this->opt.push_back(82);
			this->option3 = _option3;
			this->reqstrength += 4 * _option3;
		}
		else if(cat >= ITEM_HELM && cat <= ITEM_BOOTS)
		{
			this->opt.push_back(83);
			this->option3 = _option3;
			this->reqstrength += 4 * _option3;
		}
		else if((this->type >= 6664 && this->type < 6670) || (this->type >= 6676 && this->type <= 6684) || this->type == 6686)
		{
			switch(this->type)
			{
			case 6680:
				{
					this->opt.push_back(84);
					this->option3 = _option3;
					break;
				}
			case 6684:
				{
					this->opt.push_back(83);
					this->option3 = _option3;
					break;
				}
			case 6686:
				{
					this->opt.push_back(80);
					this->option3 = _option3;
					this->reqstrength += 4 * _option3;
					break;
				}
			default:
				{
					this->opt.push_back(85);
					this->option3 = _option3;
					break;
				}
			}
		}
		else if((this->type >= 0x1800 && this->type <= 0x1806) || this->type == 0x1a03)
		{
			switch(this->type)
			{
			case 0x1800:
				{
					this->opt.push_back(85);
					this->option3 = _option3;
					break;
				}
			case 0x1801:
				{
					this->opt.push_back(81);
					this->option3 = _option3;
					this->reqstrength += 4 * _option3;
					break;
				}
			case 0x1802:
				{
					this->opt.push_back(80);
					this->option3 = _option3;
					this->reqstrength += 4 * _option3;
					break;
				}
			case 0x1803:
				{
					if(this->option_new & 0x20)
					{
						this->opt.push_back(85);
					}
					else
					{
						this->opt.push_back(80);
					}
					this->option3 = _option3;
					this->reqstrength += 4 * _option3;
					break;
				}
			case 0x1804:
				{
					if(this->option_new & 0x20)
					{
						this->opt.push_back(81);
					}
					else
					{
						this->opt.push_back(85);
					}
					this->option3 = _option3;
					this->reqstrength += 4 * _option3;
					break;
				}
			case 0x1805:
				{
					if(this->option_new & 0x20)
					{
						this->opt.push_back(80);
					}
					else
					{
						this->opt.push_back(85);
					}
					this->option3 = _option3;
					this->reqstrength += 4 * _option3;
					break;
				}
			case 0x1806:
				{
					if(this->option_new & 0x20)
					{
						this->opt.push_back(80);
					}
					else
					{
						this->opt.push_back(81);
					}
					this->option3 = _option3;
					this->reqstrength += 4 * _option3;
					break;
				}
			case 0x1a03:
				{
					this->option3 = _option3;
					if(this->option3 & 0x02)
					{
						this->opt.push_back(103);
					}
					if(this->option3 & 0x04)
					{
						this->opt.push_back(97);
						this->attack_speed += 5;
					}
					if(this->option3 & 0x01)
					{
						this->opt.push_back(104);
					}
					break;
				}
			}
		}
	}
	if((cat >= ITEM_SHIELD && cat <= ITEM_BOOTS) || this->type == 6664 || this->type == 6665 || (this->type >= 6677 && this->type <= 6680))
	{
		if(this->option_new & 0x20)
		{
			this->opt.push_back(86);
		}
		if(this->option_new & 0x10)
		{
			this->opt.push_back(87);
		}
		if(this->option_new & 0x08)
		{
			this->opt.push_back(88);
		}
		if(this->option_new & 0x04)
		{
			this->opt.push_back(89);
		}
		if(this->option_new & 0x02)
		{
			this->opt.push_back(90);
		}
		if(this->option_new & 0x01)
		{
			this->opt.push_back(91);
		}
	}
	else if((cat >= ITEM_SWORD && cat <= ITEM_STAFF) || this->type == 6668 || this->type == 6669 || (this->type >= 6681 && this->type <= 6684))
	{
		if(this->option_new & 0x20)
		{
			this->opt.push_back(92);
		}
		if((cat <= ITEM_BOW || cat >= ITEM_SHIELD) && this->type != 6668 && this->type != 6681 && this->type != 6683)
		{
			if(this->option_new & 0x10)
			{
				this->opt.push_back(93);
			}
			if(this->option_new & 0x08)
			{
				this->opt.push_back(94);
			}
		}
		else
		{
			if(this->option_new & 0x10)
			{
				this->opt.push_back(95);
			}
			if(this->option_new & 0x08)
			{
				this->opt.push_back(96);
			}
		}
		if(this->option_new & 0x04)
		{
			this->opt.push_back(97);
			this->attack_speed += 7;
		}
		if(this->option_new & 0x02)
		{
			this->opt.push_back(98);
		}
		if(this->option_new & 0x01)
		{
			this->opt.push_back(99);
		}
	}
	else if((this->type >= 6147 && this->type <= 6150) || this->type == 6686)
	{
		if(this->option_new & 0x08)
		{
			this->opt.push_back(105);
		}
		if(this->option_new & 0x04)
		{
			this->opt.push_back(102);
		}
		if(this->option_new & 0x02)
		{
			this->opt.push_back(101);
		}
		if(this->option_new & 0x01)
		{
			this->opt.push_back(100);
		}
	}
	else if(this->type == 6693)
	{
		if(this->option_new & 0x02 && this->option_new & 0x01) /* golden is 03 isnt it? */
		{
			this->opt.push_back(108); /* suggested */
		}
		else if(this->option_new & 0x02)
		{
			this->opt.push_back(107);
		}
		else if(this->option_new & 0x01)
		{
			this->opt.push_back(106);
		}
	}
	/* set option skipped */

	this->part = it->slot;
	this->Value();

	if(this->type != 2055 && this->type != 2063)
	{
		this->damage_min_original = this->damage_min;
		this->defense_original = this->defense;
		this->damage_max_original = this->damage_max;
		this->damage_min -= this->damage_min * this->state;
		this->damage_max -= this->damage_max * this->state;
		this->defense -= this->defense * this->state;
		this->block -= this->block * this->state;
		if(this->durability < 1.0f)
		{
			this->attack_speed = 0;
		}
	}
	if(this->durability == 0.0f)
	{
		ZeroMemory(this->resistance, sizeof(this->resistance));
	}
}

void CItem::Value()
{
	this->m_BuyMoney = this->level * 100 + 1000 * this->option1 + 1000* this->option2 + 1000* this->option3 + 1000 * this->option_new;
	this->m_SellMoney = this->m_BuyMoney / 3;
}