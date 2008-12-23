#include "stdafx.h"
#include ".\\SkillDelay.h"

CSkillDelay::CSkillDelay()
{
	this->Init();
}

void CSkillDelay::Init()
{
	ZeroMemory(this->LastSkillUseTime, sizeof(this->LastSkillUseTime));
}

CSkillDelay::~CSkillDelay()
{
}