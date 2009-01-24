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

class CItem
{
public:
  /*<thisrel this+0x0>*/ /*|0x4|*/ uint32 guid;
  /*<thisrel this+0x6>*/ /*|0x2|*/ int16 type;
  /*<thisrel this+0x8>*/ /*|0x2|*/ uint8 level;
  /*<thisrel this+0xa>*/ /*|0x1|*/ uint8 part;
  /*<thisrel this+0xb>*/ /*|0x1|*/ uint8 Class;
  /*<thisrel this+0xc>*/ /*|0x1|*/ bool two_hand;
  /*<thisrel this+0xd>*/ /*|0x1|*/ uint8 attack_speed;
  /*<thisrel this+0xe>*/ /*|0x1|*/ uint8 walk_speed;
  /*<thisrel this+0x10>*/ /*|0x2|*/ uint16 damage_min;
  /*<thisrel this+0x12>*/ /*|0x2|*/ uint16 damage_max;
  /*<thisrel this+0x14>*/ /*|0x1|*/ uint8 block;
  /*<thisrel this+0x16>*/ /*|0x2|*/ uint16 defense;
  /*<thisrel this+0x18>*/ /*|0x2|*/ uint16 magic_defense;
  /*<thisrel this+0x1a>*/ /*|0x1|*/ uint8 speed;
  /*<thisrel this+0x1c>*/ /*|0x2|*/ unsigned short m_DamageMinOrigin;
  /*<thisrel this+0x1e>*/ /*|0x2|*/ unsigned short m_DefenseOrigin;
  /*<thisrel this+0x20>*/ /*|0x2|*/ unsigned short m_Magic;
  /*<thisrel this+0x24>*/ /*|0x4|*/ float durability;
  float base_durability;
  /*<thisrel this+0x28>*/ /*|0x2|*/ unsigned short m_DurabilitySmall;
  /*<thisrel this+0x2c>*/ /*|0x4|*/ float m_BaseDurability;
  /*<thisrel this+0x30>*/ /*|0x1|*/ unsigned char m_SpecialNum;
  /*<thisrel this+0x31>*/ /*|0x8|*/ unsigned char m_Special[8];
  /*<thisrel this+0x39>*/ /*|0x8|*/ unsigned char m_SpecialValue[8];
  /*<thisrel this+0x42>*/ /*|0x2|*/ uint16 reqstrength;
  /*<thisrel this+0x44>*/ /*|0x2|*/ uint16 reqdexterity;
  /*<thisrel this+0x46>*/ /*|0x2|*/ uint16 reqenergy;
  /*<thisrel this+0x48>*/ /*|0x2|*/ uint16 reqlevel;
  /*<thisrel this+0x4a>*/ /*|0x2|*/ uint16 reqvitality;
  /*<thisrel this+0x4c>*/ /*|0x2|*/ uint16 reqleadership;
  /*<thisrel this+0x4e>*/ /*|0x2|*/ unsigned short m_Leadership;
  /*<thisrel this+0x50>*/ /*|0x5|*/ uint32 reqclass;
  /*<thisrel this+0x55>*/ /*|0x7|*/ unsigned char m_Resistance[7];
  /*<thisrel this+0x5c>*/ /*|0x4|*/ int m_Value;
  /*<thisrel this+0x60>*/ /*|0x4|*/ unsigned long m_SellMoney;
  /*<thisrel this+0x64>*/ /*|0x4|*/ unsigned long m_BuyMoney;
  /*<thisrel this+0x68>*/ /*|0x4|*/ int m_iPShopValue;
  /*<thisrel this+0x6c>*/ /*|0x1|*/ unsigned char m_bItemExist;
  /*<thisrel this+0x70>*/ /*|0x4|*/ int m_OldSellMoney;
  /*<thisrel this+0x74>*/ /*|0x4|*/ int m_OldBuyMoney;
  /*<thisrel this+0x78>*/ /*|0x1|*/ unsigned char m_Option1;
  /*<thisrel this+0x79>*/ /*|0x1|*/ unsigned char m_Option2;
  /*<thisrel this+0x7a>*/ /*|0x1|*/ unsigned char m_Option3;
  /*<thisrel this+0x7b>*/ /*|0x1|*/ unsigned char m_NewOption;
  /*<thisrel this+0x7c>*/ /*|0x10|*/ float m_DurabilityState[4];
  /*<thisrel this+0x8c>*/ /*|0x4|*/ float m_CurrentDurabilityState;
  /*<thisrel this+0x90>*/ /*|0x1|*/ unsigned char m_SkillChange;
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
  void Assign(const DATA_ITEM *item_data);
  bool ApplyTemplate(const ITEM_TEMPLATE* it);
};

void ItemByteConvert(unsigned char* buf, int type, unsigned char Option1, unsigned char Option2, unsigned char Option3, unsigned char level, unsigned char dur, unsigned char Noption, unsigned char SetOption, unsigned char JewelOfHarmonyOption, unsigned char ItemEffectEx);

#endif