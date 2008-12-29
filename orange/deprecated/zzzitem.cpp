#include "stdafx.h"
#include ".\\zzzitem.h"

ITEM_ATTRIBUTE ItemAttribute[8192];

CItem::CItem()
{
	this->Clear();
}

void CItem::Clear()
{
	this->guid = 0;
	this->m_Type = -1;
	this->m_Level = 0;
	this->m_Part = 0;
	this->m_Class = 0;
	this->m_TwoHand = 0;
	this->m_AttackSpeed = 0;
	this->m_DamageMin = 0;
	this->m_DamageMax = 0;
	this->m_SuccessfulBlocking = 0;
	this->m_MagicDefense = 0;
	this->m_Durability = 0.0f;
	this->m_SpecialNum = 0;
	this->m_Value = 0;
	this->m_Option1 = 0;
	this->m_Option2 = 0;
	this->m_Option3 = 0;
	this->m_NewOption = 0;
	this->m_Number = 0;
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
}

bool CItem::IsItem()
{
	if(this->m_Type >= 0)
	{
		return true;
	}
	return false;
}

int CItem::IsSetItem()
{
	if(this->m_Type >= 0)
	{
		return (this->m_SetOption & 3);
	}
	else
	{
		return 0;
	}
}

int CItem::IsExtItem()
{
	if(this->m_Type != 0x1A25 && (this->m_NewOption & 0x7F))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int CItem::IsFenrirIncLastAttackDamage()
{
	if(this->m_Durability == 1.0f && this->m_NewOption == 1)
	{
		return 10;
	}
	else
	{
		return 0;
	}
}

int CItem::IsFenrirDecLastAttackDamage()
{
	if(this->m_Durability == 1.0f && this->m_NewOption == 2)
	{
		return 10;
	}
	else
	{
		return 0;
	}
}

int CItem::IsFenrirGolden()
{
	if(this->m_Durability == 1.0f && this->m_NewOption == 3)
	{
		return 10;
	}
	else
	{
		return 0;
	}
}

int ItemGetNumberMake(int type, int index)
{
	int make = index + type * 512;
	if((ItemAttribute[make].Width >= 1) && (ItemAttribute[make].Height >= 1))
	{
		return make;
	}
	else
	{
		return -1;
	}
}

/*void ItemByteConvert(unsigned char* buf, int type, unsigned char Option1, unsigned char Option2, unsigned char Option3, unsigned char level, unsigned char dur, unsigned char Noption, unsigned char SetOption, unsigned char JewelOfHarmonyOption, unsigned char ItemEffectEx)
{
	ZeroMemory(buf, 7);
	int n = 0;
	buf[n] = LOBYTE(type); //maybe use LOBYTE?
	n++;
	buf[n] = 0;
	buf[n] |= 8 * LOBYTE(level);
	buf[n] |= 128 * LOBYTE(Option1);
	buf[n] |= 4 * LOBYTE(Option2);
	buf[n] |= (LOBYTE(Option3) & 3);
	n++;
	buf[n] = LOBYTE(dur);
	n++;
	buf[n] = 0;
	buf[n] |= (char)((type & 0x100) / 2);
	if(LOBYTE(Option3) > 3)
	{
		buf[n] |= 0x40;
	}
	buf[n] |= (char)Noption;
	n++;
	buf[n] = (char)SetOption;
	n++;
	buf[n] |= (type & 0x1e00) / 32;
	unsigned char btItemEffectFor380 = 0;
	btItemEffectFor380 = (LOBYTE(ItemEffectEx) & 0x80) / 16;
	buf[n] |= btItemEffectFor380;
	n++;
	buf[n] = JewelOfHarmonyOption;
}*/

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

void CItem::AssignItem(DATA_ITEM *item_data)
{
	this->m_Number = item_data->guid;
	this->m_Type = item_data->type;
	this->m_Level = item_data->level;
	this->m_Durability = (float)item_data->durability;
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