#include "stdafx.h"
#include ".\\MagicInf.h"

CMagicInf::CMagicInf()
{
	this->Clear();
}

CMagicInf::~CMagicInf()
{
	this->m_DamageMin = 0;
	this->m_DamageMax = 0;
}

void CMagicInf::Clear()
{
	this->m_Skill = -1;
	this->m_Level = 0;
}