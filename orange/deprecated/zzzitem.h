#ifndef __ZZZITEM_H_
#define __ZZZITEM_H_

struct ITEM_ATTRIBUTE
{
  /*<thisrel this+0x0>*/ /*|0x20|*/ char Name[32];
  /*<thisrel this+0x20>*/ /*|0x1|*/ unsigned char HaveItemInfo;
  /*<thisrel this+0x21>*/ /*|0x1|*/ unsigned char TwoHand;
  /*<thisrel this+0x22>*/ /*|0x1|*/ unsigned char Level;
  /*<thisrel this+0x23>*/ /*|0x1|*/ unsigned char Width;
  /*<thisrel this+0x24>*/ /*|0x1|*/ unsigned char Height;
  /*<thisrel this+0x25>*/ /*|0x1|*/ char Serial;
  /*<thisrel this+0x26>*/ /*|0x1|*/ unsigned char OptionFlag;
  /*<thisrel this+0x27>*/ /*|0x1|*/ unsigned char MondownFlag;
  /*<thisrel this+0x28>*/ /*|0x1|*/ unsigned char AttackSpeed;
  /*<thisrel this+0x29>*/ /*|0x1|*/ unsigned char WalkSpeed;
  /*<thisrel this+0x2a>*/ /*|0x1|*/ unsigned char DamageMin;
  /*<thisrel this+0x2b>*/ /*|0x1|*/ unsigned char DamageMax;
  /*<thisrel this+0x2c>*/ /*|0x1|*/ unsigned char SuccessfulBlocking;
  /*<thisrel this+0x2d>*/ /*|0x1|*/ unsigned char Defense;
  /*<thisrel this+0x2e>*/ /*|0x1|*/ unsigned char MagicDefense;
  /*<thisrel this+0x2f>*/ /*|0x1|*/ unsigned char Speed;
  /*<thisrel this+0x30>*/ /*|0x1|*/ unsigned char Durability;
  /*<thisrel this+0x31>*/ /*|0x1|*/ unsigned char MagicDurability;
  /*<thisrel this+0x32>*/ /*|0x1|*/ unsigned char AttackDur;
  /*<thisrel this+0x33>*/ /*|0x1|*/ unsigned char DefenceDur;
  /*<thisrel this+0x34>*/ /*|0x2|*/ unsigned short RequireStrength;
  /*<thisrel this+0x36>*/ /*|0x2|*/ unsigned short RequireDexterity;
  /*<thisrel this+0x38>*/ /*|0x2|*/ unsigned short RequireEnergy;
  /*<thisrel this+0x3a>*/ /*|0x2|*/ unsigned short RequireLevel;
  /*<thisrel this+0x3c>*/ /*|0x2|*/ unsigned short Value;
  /*<thisrel this+0x3e>*/ /*|0x5|*/ unsigned char RequireClass[5];
  /*<thisrel this+0x43>*/ /*|0x7|*/ unsigned char Resistance[7];
  /*<thisrel this+0x4a>*/ /*|0x2|*/ unsigned short RequireVitality;
  /*<thisrel this+0x4c>*/ /*|0x4|*/ int BuyMoney;
  /*<thisrel this+0x50>*/ /*|0x4|*/ int MagicPW;
  /*<thisrel this+0x54>*/ /*|0x4|*/ float RepaireMoneyRate;
  /*<thisrel this+0x58>*/ /*|0x4|*/ float AllRepaireMoneyRate;
  /*<thisrel this+0x5c>*/ /*|0x1|*/ unsigned char QuestItem;
  /*<thisrel this+0x5d>*/ /*|0x1|*/ unsigned char SetAttr;
  /*<thisrel this+0x5e>*/ /*|0x1|*/ unsigned char ResistanceType;
  /*<thisrel this+0x60>*/ /*|0x4|*/ int ItemSlot;
  /*<thisrel this+0x64>*/ /*|0x4|*/ int SkillType;
  /*<thisrel this+0x68>*/ /*|0x4|*/ int RequireLeadership;
};
// <size 0x6c>

struct JEWELOFHARMONY_ITEM_EFFECT
{
  /*<thisrel this+0x0>*/ /*|0x2|*/ short HJOpAddMinAttackDamage;
  /*<thisrel this+0x2>*/ /*|0x2|*/ short HJOpAddMaxAttackDamage;
  /*<thisrel this+0x4>*/ /*|0x2|*/ short HJOpRequireStr;
  /*<thisrel this+0x6>*/ /*|0x2|*/ short HJOpRequireDex;
  /*<thisrel this+0x8>*/ /*|0x2|*/ short HJOpAddAttackDamage;
  /*<thisrel this+0xa>*/ /*|0x2|*/ short HJOpAddCriticalDamage;
  /*<thisrel this+0xc>*/ /*|0x2|*/ short HJOpAddSkillAttack;
  /*<thisrel this+0xe>*/ /*|0x2|*/ short HJOpAddAttackSuccessRatePVP;
  /*<thisrel this+0x10>*/ /*|0x2|*/ short HJOpDecreaseSDRate;
  /*<thisrel this+0x12>*/ /*|0x2|*/ short HJOpAddIgnoreSDRate;
  /*<thisrel this+0x14>*/ /*|0x2|*/ short HJOpAddMagicPower;
  /*<thisrel this+0x16>*/ /*|0x2|*/ short HJOpAddDefense;
  /*<thisrel this+0x18>*/ /*|0x2|*/ short HJOpAddMaxAG;
  /*<thisrel this+0x1a>*/ /*|0x2|*/ short HJOpAddMaxHP;
  /*<thisrel this+0x1c>*/ /*|0x2|*/ short HJOpAddRefillHP;
  /*<thisrel this+0x1e>*/ /*|0x2|*/ short HJOpAddRefillMP;
  /*<thisrel this+0x20>*/ /*|0x2|*/ short HJOpAddDefenseSuccessRatePvP;
  /*<thisrel this+0x22>*/ /*|0x2|*/ short HJOpAddDamageDecrease;
  /*<thisrel this+0x24>*/ /*|0x2|*/ short HJOpAddSDRate;
};
// <size 0x26>

struct ITEMOPTION_FOR380ITEM_EFFECT
{
  /*<thisrel this+0x0>*/ /*|0x2|*/ short OpAddAttackSuccessRatePVP;
  /*<thisrel this+0x2>*/ /*|0x2|*/ short OpAddDamage;
  /*<thisrel this+0x4>*/ /*|0x2|*/ short OpAddDefenseSuccessRatePvP;
  /*<thisrel this+0x6>*/ /*|0x2|*/ short OpAddDefense;
  /*<thisrel this+0x8>*/ /*|0x2|*/ short OpAddMaxHP;
  /*<thisrel this+0xa>*/ /*|0x2|*/ short OpAddMaxSD;
  /*<thisrel this+0xc>*/ /*|0x2|*/ short OpRefillOn;
  /*<thisrel this+0xe>*/ /*|0x2|*/ short OpAddRefillSD;
};
// <size 0x10>

class CItem
{
public:
  /*<thisrel this+0x0>*/ /*|0x4|*/ unsigned long m_Number;
  /*<thisrel this+0x4>*/ /*|0x1|*/ char m_serial;
  /*<thisrel this+0x6>*/ /*|0x2|*/ short m_Type;
  /*<thisrel this+0x8>*/ /*|0x2|*/ short m_Level;
  /*<thisrel this+0xa>*/ /*|0x1|*/ unsigned char m_Part;
  /*<thisrel this+0xb>*/ /*|0x1|*/ unsigned char m_Class;
  /*<thisrel this+0xc>*/ /*|0x1|*/ unsigned char m_TwoHand;
  /*<thisrel this+0xd>*/ /*|0x1|*/ unsigned char m_AttackSpeed;
  /*<thisrel this+0xe>*/ /*|0x1|*/ unsigned char m_WalkSpeed;
  /*<thisrel this+0x10>*/ /*|0x2|*/ unsigned short m_DamageMin;
  /*<thisrel this+0x12>*/ /*|0x2|*/ unsigned short m_DamageMax;
  /*<thisrel this+0x14>*/ /*|0x1|*/ unsigned char m_SuccessfulBlocking;
  /*<thisrel this+0x16>*/ /*|0x2|*/ unsigned short m_Defense;
  /*<thisrel this+0x18>*/ /*|0x2|*/ unsigned short m_MagicDefense;
  /*<thisrel this+0x1a>*/ /*|0x1|*/ unsigned char m_Speed;
  /*<thisrel this+0x1c>*/ /*|0x2|*/ unsigned short m_DamageMinOrigin;
  /*<thisrel this+0x1e>*/ /*|0x2|*/ unsigned short m_DefenseOrigin;
  /*<thisrel this+0x20>*/ /*|0x2|*/ unsigned short m_Magic;
  /*<thisrel this+0x24>*/ /*|0x4|*/ float m_Durability;
  /*<thisrel this+0x28>*/ /*|0x2|*/ unsigned short m_DurabilitySmall;
  /*<thisrel this+0x2c>*/ /*|0x4|*/ float m_BaseDurability;
  /*<thisrel this+0x30>*/ /*|0x1|*/ unsigned char m_SpecialNum;
  /*<thisrel this+0x31>*/ /*|0x8|*/ unsigned char m_Special[8];
  /*<thisrel this+0x39>*/ /*|0x8|*/ unsigned char m_SpecialValue[8];
  /*<thisrel this+0x42>*/ /*|0x2|*/ unsigned short m_RequireStrength;
  /*<thisrel this+0x44>*/ /*|0x2|*/ unsigned short m_RequireDexterity;
  /*<thisrel this+0x46>*/ /*|0x2|*/ unsigned short m_RequireEnergy;
  /*<thisrel this+0x48>*/ /*|0x2|*/ unsigned short m_RequireLevel;
  /*<thisrel this+0x4a>*/ /*|0x2|*/ unsigned short m_RequireVitality;
  /*<thisrel this+0x4c>*/ /*|0x2|*/ unsigned short m_RequireLeaderShip;
  /*<thisrel this+0x4e>*/ /*|0x2|*/ unsigned short m_Leadership;
  /*<thisrel this+0x50>*/ /*|0x5|*/ unsigned char m_RequireClass[5];
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
  CItem();
  void Convert(int type, unsigned char Option1, unsigned char Option2, unsigned char Option3, unsigned char Attribute2, unsigned char SetOption, unsigned char ItemEffectEx, unsigned char DbVersion);
  void Value();
  void OldValue();
  int GetSize(int& w, int& h);
  void Clear();
  bool IsItem();
  int IsSetItem();
  int GetAddStatType();
  void SetPetItemInfo(int petlevel, int petexp);
  int AddPetItemExp(int petexp);
  int DecPetItemExp(int percent);
  void PetValue();
  int PetItemLevelDown(int exp);
  int ItemDamageMin();
  int ItemDefense();
  int IsClass(char aClass, int ChangeUP);
  char* GetName();
  int GetLevel();
  void PlusSpecial(int* Value, int Special);
  void PlusSpecialPercent(int* Value, int Special, unsigned short Percent);
  void PlusSpecialPercentEx(int* Value, int SourceValue, int Special);
  void SetItemPlusSpecialStat(short* Value, int Special);
  int GetWeaponType();
  void PlusSpecialSetRing(unsigned char* Value);
  unsigned long GetNumber();
  int IsExtItem();
  int IsExtLifeAdd();
  int IsExtManaAdd();
  int IsExtDamageMinus();
  int IsExtDamageReflect();
  int IsExtDefenseSuccessfull();
  int IsExtMonsterMoney();
  int IsExtExcellentDamage();
  int IsExtAttackRate();
  int IsExtAttackRate2();
  int IsExtAttackSpeed();
  int IsExtMonsterDieLife();
  int IsExtMonsterDieMana();
  int IsWingOpGetOnePercentDamage();
  int IsWingOpGetLifeToMonster();
  int IsWingOpGetManaToMoster();
  int IsDinorantReduceAttackDamaege();
  int IsFenrirIncLastAttackDamage();
  int IsFenrirDecLastAttackDamage();
  int IsFenrirGolden();
  int SimpleDurabilityDown(int iDur);
  int DurabilityDown(int dur, int aIndex);
  int DurabilityDown2(int dur, int aIndex);
  int NormalWeaponDurabilityDown(int defence, int aIndex);
  int BowWeaponDurabilityDown(int defence, int aIndex);
  int StaffWeaponDurabilityDown(int defence, int aIndex);
  int ArmorDurabilityDown(int damagemin, int aIndex);
  int CheckDurabilityState();
};
// <size 0xb0>

int ItemGetNumberMake(int type, int index);
void ItemByteConvert(unsigned char* buf, int type, unsigned char Option1, unsigned char Option2, unsigned char Option3, unsigned char level, unsigned char dur, unsigned char Noption, unsigned char SetOption, unsigned char JewelOfHarmonyOption, unsigned char ItemEffectEx);

extern ITEM_ATTRIBUTE ItemAttribute[8192];

#endif