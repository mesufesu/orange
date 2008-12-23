#include "stdafx.h"
#include ".\\MapItem.h"

CMapItem::CMapItem()
{
	this->Init();
}

void CMapItem::Init()
{
	this->m_State = 0;
	this->VPCount = 0;
	for(int n = 0; n < 75; ++n)
	{
		memset(&(this->VpPlayer), 0x00, sizeof(VIEWPORT_PLAYER_STRUCT));
	}
}

CMapItem::~CMapItem()
{
}