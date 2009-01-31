#include "stdafx.h"
#include ".\\inventory.h"

const CItem dummy;

CInventory::CInventory()
{
	for(uint32 i = 0; i < 108; ++i)
	{
		this->pinv[i] = (CItem*)&dummy;
	}
}

pItem& CInventory::operator [](uint32 i)
{
	return this->pinv[i];
}