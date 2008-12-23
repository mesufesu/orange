#include "stdafx.h"
#include ".\\Shop.h"

CShop::CShop()
{
}

void CShop::Init()
{
	this->SendItemDataLen = 0;
	this->ItemCount = 0;
	ZeroMemory(this->ShopInventoryMap, sizeof(this->ShopInventoryMap));
	ZeroMemory(this->SendItemData, sizeof(this->SendItemData));
}

CShop::~CShop()
{
}