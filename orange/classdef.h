#ifndef _CLASSDEF_H_
#define _CLASSDEF_H_

#include ".\\Item.h"

enum ClassNumber
{
  CLASS_WIZARD = 0x0,
  CLASS_KNIGHT = 0x1,
  CLASS_ELF = 0x2,
  CLASS_MAGUMSA = 0x3,
  CLASS_DARKLORD = 0x4,
  CLASS_SUMMONER = 0x5,
};

struct DEFAULTCLASSTYPE
{
  /*<thisrel this+0x0>*/ /*|0x4|*/ int Experience;
  /*<thisrel this+0x4>*/ /*|0x2|*/ unsigned short Strength;
  /*<thisrel this+0x6>*/ /*|0x2|*/ unsigned short Dexterity;
  /*<thisrel this+0x8>*/ /*|0x2|*/ unsigned short Vitality;
  /*<thisrel this+0xa>*/ /*|0x2|*/ unsigned short Energy;
  /*<thisrel this+0xc>*/ /*|0x4|*/ float LevelLife;
  /*<thisrel this+0x10>*/ /*|0x4|*/ float Life;
  /*<thisrel this+0x14>*/ /*|0x4|*/ float MaxLife;
  /*<thisrel this+0x18>*/ /*|0x4|*/ float LevelMana;
  /*<thisrel this+0x1c>*/ /*|0x4|*/ float Mana;
  /*<thisrel this+0x20>*/ /*|0x4|*/ float MaxMana;
  /*<thisrel this+0x24>*/ /*|0x4|*/ float VitalityToLife;
  /*<thisrel this+0x28>*/ /*|0x4|*/ float EnergyToMana;
  /*<thisrel this+0x2c>*/ /*|0x9a0|*/ CItem Equipment[14];
  /*<thisrel this+0x9cc>*/ /*|0x2|*/ unsigned short Leadership;
};
// <size 0x9d0>

class classdef
{
public:
  /*<thisrel this+0x4>*/ /*|0x3110|*/ DEFAULTCLASSTYPE DefClass[6];
  classdef();
  void Init();
  void SetCharacter(int Class, int Str, int Dex, int Vit, int Energy, float Life, float Mana, float LevelLife, float LevelMana, float VitalityToLife, float EnergyToMana, int Leadership);
  void SetEquipment(int Class);
  int GetDefPoint(int char_class);

  virtual /*<vtableoff 0x0>*/ ~classdef();
};
// <size 0x3118>

extern classdef DCInfo;

#endif