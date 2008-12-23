#include "stdafx.h"
#include ".\\TMonsterAIAgro.h"

TMonsterAIAgro::TMonsterAIAgro()
{
	this->ResetAll();
}

TMonsterAIAgro::~TMonsterAIAgro()
{
}

void TMonsterAIAgro::ResetAll()
{
	for(int i = 0; i < 100; ++i)
	{
		this->m_Agro[i].Reset();
	}
}

//=============================

TMonsterAIAgroInfo::TMonsterAIAgroInfo()
{
	this->Reset();
}

void TMonsterAIAgroInfo::Reset()
{
	this->m_iAgroValue = -1;
	this->m_iUserIndex = -1;
}