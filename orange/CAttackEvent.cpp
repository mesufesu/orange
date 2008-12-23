#include "stdafx.h"
#include ".\\CAttackEvent.h"

CAttackEvent * pAttackEvent;

CAttackEvent::CAttackEvent()
{
	this->Init();
}

void CAttackEvent::Init()
{
	this->EventState = 0;
	this->EventStartTime = GetTickCount();
	this->m_MapNumber = 0;
}

CAttackEvent::~CAttackEvent()
{
}