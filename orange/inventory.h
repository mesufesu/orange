#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include ".\\item.h"

class CInventory
{
public:
	CInventory();
	pItem& operator [ ] (uint32 i);
private:
	CItem * pinv[108];
};

extern const CItem dummy;

#endif