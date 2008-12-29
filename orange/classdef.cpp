#include "stdafx.h"
#include ".\\classdef.h"

classdef DCInfo;

classdef::classdef()
{
}

void classdef::Init()
{
	this->SetCharacter(CLASS_WIZARD, 18, 18, 15, 30, 60.0f, 60.0f, 1.0f, 2.0f, 2.0f, 2.0f, 0);
	this->SetCharacter(CLASS_KNIGHT, 28, 20, 25, 10, 110.0f, 20.0f, 2.0f, 0.5f, 3.0f, 1.0f, 0);
	this->SetCharacter(CLASS_ELF, 22, 25, 20, 15, 80.0f, 30.0f, 1.0f, 1.5f, 2.0f, 1.5f, 0);
	this->SetCharacter(CLASS_MAGUMSA, 26, 26, 26, 26, 110.0f, 60.0f, 1.0f, 1.0f, 2.0f, 2.0f, 0);
	this->SetCharacter(CLASS_DARKLORD, 26, 20, 20, 15, 90.0f, 40.0f, 1.5f, 1.0f, 2.0f, 1.5f, 19);
	this->SetCharacter(CLASS_SUMMONER, 22, 19, 18, 23, 90.0f, 60.0f, 1.5f, 2.0f, 2.0f, 2.0f, 0); //heuristical
}

void classdef::SetCharacter(int Class, int Str, int Dex, int Vit, int Energy, float Life, float Mana, float LevelLife, float LevelMana, float VitalityToLife, float EnergyToMana, int Leadership)
{
	this->DefClass[Class].Experience = 0;
	this->DefClass[Class].Strength = Str;
	this->DefClass[Class].Dexterity = Dex;
	this->DefClass[Class].Vitality = Vit;
	this->DefClass[Class].Energy = Energy;
	this->DefClass[Class].Life = Life;
	this->DefClass[Class].Mana = Mana;
	this->DefClass[Class].LevelLife = LevelLife;
	this->DefClass[Class].LevelMana = LevelMana;
	this->DefClass[Class].VitalityToLife = VitalityToLife;
	this->DefClass[Class].EnergyToMana = EnergyToMana;
	this->DefClass[Class].Leadership = Leadership;
	this->DefClass[Class].MaxLife = Life;
	this->DefClass[Class].MaxMana = Mana;
	this->SetEquipment(Class);
}

void classdef::SetEquipment(int Class)
{
	/*int def_type = 0;
	int right_type = 0;
	for(int i = 0; i < 14; ++ i)
	{
		this->DefClass[Class].Equipment[i].Clear();
	}
	if(Class <= 6)
	{
		switch(Class)
		{
		case CLASS_WIZARD:
			{
				break;
			}
		case CLASS_KNIGHT:
			{
				def_type = ItemGetNumberMake(1, 0);
				this->DefClass[Class].Equipment[0].m_Level = 0;
				break;
			}
		case CLASS_ELF:
			{
				def_type = ItemGetNumberMake(4, 0);
				right_type = ItemGetNumberMake(4, 15);
				this->DefClass[Class].Equipment[0].m_Level = 0;
				this->DefClass[Class].Equipment[1].m_Level = 0;
				break;
			}
		case CLASS_MAGUMSA:
			{
				def_type = ItemGetNumberMake(6, 0);
				right_type = ItemGetNumberMake(0, 1);
				this->DefClass[Class].Equipment[0].m_Level = 0;
				this->DefClass[Class].Equipment[1].m_Level = 0;
				break;
			}
		case CLASS_DARKLORD:
			{
				def_type = ItemGetNumberMake(6, 0);
				right_type = ItemGetNumberMake(0, 1);
				this->DefClass[Class].Equipment[0].m_Level = 0;
				this->DefClass[Class].Equipment[1].m_Level = 0;
				break;
			}
		case CLASS_SUMMONER:
			{
				def_type = ItemGetNumberMake(6, 0);
				right_type = ItemGetNumberMake(0, 1);
				this->DefClass[Class].Equipment[0].m_Level = 0;
				this->DefClass[Class].Equipment[1].m_Level = 0;
				break;
			}
		}
	}*/
}

int classdef::GetDefPoint(int char_class)
{
	if(char_class >= 0 && char_class <= 6)
	{
		return (this->DefClass[char_class].Strength + this->DefClass[char_class].Dexterity + this->DefClass[char_class].Energy + this->DefClass[char_class].Vitality + this->DefClass[char_class].Leadership);
	}
	else
	{
		return 0;
	}
}

classdef::~classdef()
{
}