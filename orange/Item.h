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

#ifndef _ITEM_H_
#define _ITEM_H_

#include ".\\ItemTemplate.h"

enum CLASS_ATTR
{
	CLASS_NONE = 0x00L,

	DW_0 = 0x00000001L,
	DW_1 = 0x00000002L,
	DW_2 = 0x00000004L,

	DK_0 = 0x00000008L,
	DK_1 = 0x00000010L,
	DK_2 = 0x00000020L,

	FE_0 = 0x00000040L,
	FE_1 = 0x00000080L,
	FE_2 = 0x00000100L,

	MG_0 = 0x00000200L,
	MG_1 = 0x00000400L,
	MG_2 = 0x00000800L,

	DL_0 = 0x00001000L,
	DL_1 = 0x00002000L,
	DL_2 = 0x00004000L,

	SU_0 = 0x00008000L,
	SU_1 = 0x00010000L,
	SU_2 = 0x00020000L,
};

enum _ITEM_TYPE
{
	ITEM_SWORD = 0,
	ITEM_AXE = 1,
	ITEM_MACE = 2,
	ITEM_SPEAR = 3,
	ITEM_BOW = 4,
	ITEM_STAFF = 5,
	ITEM_SHIELD = 6,
	ITEM_HELM = 7,
	ITEM_CHEST = 8,
	ITEM_PANTS = 9,
	ITEM_GLOVES = 10,
	ITEM_BOOTS = 11,
	ITEM_12 = 12,
	ITEM_13 = 13,
	ITEM_14 = 14,
	ITEM_SCROLL = 15,
};

enum _ITEM_STATUS
{
	ITEM_UNCHANGED = 0, //item was not changed during session, can skip saving
	ITEM_CHANGED = 1, //item was changed, must be saved
	ITEM_NEW = 2, //must be inserted in db
	ITEM_DELETED = 3, //item was dropped and then vanished/sold, such item deleted by ItemProc, must be deleted from db
	ITEM_NOTEXIST = 4, //item just disappeared, it may be already saved or just never existed in database
};

struct DATA_ITEM
{
  int guid;
  int slot;
  int type;
  int level;
  double durability;
  int option1;
  int option2;
  int option3;
  int newoption;
  int setoption;
  int petitem_level;
  int petitem_exp;
  int joh_option;
  int optionex;
  DATA_ITEM()
  {
	  this->type = -1;
  }
};

struct _Special
{
	uint32 type;
	uint32 value;
	_Special(uint32 v1, uint32 v2)
	{
		this->type = v1;
		this->value = v2;
	};
	_Special(uint32 v)
	{
		this->type = v;
	};
};

typedef std::vector<uint32> OptionsList;

typedef class CItem
{
public:
	uint64 guid;
	int16 type;
	uint8 level;
	uint8 part;
	bool two_hand;
	uint8 attack_speed;
	uint8 walk_speed;
	uint16 damage_min;
	uint16 damage_max;
	uint16 damage_min_original;
	uint16 damage_max_original;
	uint16 defense_original;
	uint16 spell_power_original;
	uint16 spell_power;
	uint8 option1;
	uint8 option2;
	uint8 option3;
	uint8 option_new;
	float durability_state[4];
	float state;
	uint8 block;
	uint16 defense;
	uint16 magic_defense;
	uint8 speed;
	OptionsList opt;
	float durability;
	float base_durability;
	uint16 reqstrength;
	uint16 reqdexterity;
	uint16 reqenergy;
	uint16 reqlevel;
	uint16 reqvitality;
	uint16 reqcharisma;
	unsigned short m_Leadership;
	CLASS_ATTR reqclass;
	uint8 resistance[7];
	uint8 m_SkillChange;
  /*<thisrel this+0x5c>*/ /*|0x4|*/ int m_Value;
  /*<thisrel this+0x60>*/ /*|0x4|*/ unsigned long m_SellMoney;
  /*<thisrel this+0x64>*/ /*|0x4|*/ unsigned long m_BuyMoney;
  /*<thisrel this+0x68>*/ /*|0x4|*/ int m_iPShopValue;
  /*<thisrel this+0x70>*/ /*|0x4|*/ int m_OldSellMoney;
  /*<thisrel this+0x74>*/ /*|0x4|*/ int m_OldBuyMoney;
  /*<thisrel this+0x91>*/ /*|0x1|*/ unsigned char m_QuestItem;
  /*<thisrel this+0x92>*/ /*|0x1|*/ unsigned char m_SetOption;
  /*<thisrel this+0x93>*/ /*|0x1|*/ unsigned char m_SetAddStat;
  /*<thisrel this+0x94>*/ /*|0x1|*/ unsigned char m_IsValidItem;
  /*<thisrel this+0x95>*/ /*|0x7|*/ unsigned char m_SkillResistance[7];
  /*<thisrel this+0x9c>*/ /*|0x4|*/ int m_IsLoadPetItemInfo;
  /*<thisrel this+0xa0>*/ /*|0x4|*/ int m_PetItem_Level;
  /*<thisrel this+0xa4>*/ /*|0x4|*/ int m_PetItem_Exp;
  /*<thisrel this+0xa8>*/ /*|0x1|*/ unsigned char m_JewelOfHarmonyOption;
  /*<thisrel this+0xaa>*/ /*|0x2|*/ unsigned short m_HJOpStrength;
  /*<thisrel this+0xac>*/ /*|0x2|*/ unsigned short m_HJOpDexterity;
  /*<thisrel this+0xae>*/ /*|0x1|*/ unsigned char m_ItemOptionEx;
  _ITEM_STATUS status;
  CItem();
  bool IsItem();
  bool IsExtItem();
  bool IsSetItem();
  //void Assign(const DATA_ITEM *item_data);
  //bool ApplyTemplate(const ITEM_TEMPLATE* it);
  void PlusSpecial(uint32 * value, uint32 special); 
  void Convert(uint32 _type, uint8 option1, uint8 option2, uint8 option3, uint8 option_new, uint8 set_option, uint8 effect_ex);
  _ITEM_TYPE GetItemType();
  void Value();
} *pItem;

void ItemByteConvert(unsigned char* buf, int type, unsigned char Option1, unsigned char Option2, unsigned char Option3, unsigned char level, unsigned char dur, unsigned char Noption, unsigned char SetOption, unsigned char JewelOfHarmonyOption, unsigned char ItemEffectEx);

#endif