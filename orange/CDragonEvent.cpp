#include "stdafx.h"
#include ".\\CDragonEvent.h"

CDragonEvent* pDragonEvent;

CDragonEvent::CDragonEvent()
{
	this->Init();
}

void CDragonEvent::Init()
{
	this->EventState = 0;
	this->EventStartTime = 0;
	this->m_MapNumber = 0;
	this->m_bManualStart = false;
}

CDragonEvent::~CDragonEvent()
{
}