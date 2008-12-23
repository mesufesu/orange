#include "stdafx.h"
#include ".\\ComboAttack.h"

void ComboSkillData::Init()
{
	this->dwTime = -1;
	this->Skill[0] = -1;
	this->Skill[1] = -1;
	this->Skill[2] = -1;
	this->ProgressIndex = -1;
}