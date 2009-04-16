#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "item.h"

enum CELL_TYPE
{
	CELL_EMPTY = 0,
	CELL_MAIN = 1,
	CELL_BUSY = 2,
};

struct MAP_CELL
{
	uint8 add;
	pItem item;
	CELL_TYPE type;
	void clear();
};

class CInventory
{
public:
	CInventory();
	bool InsertItem(pItem item);
	pItem RemoveItem(uint32 i);
	bool PlaceItem(uint32 i, pItem item);
	pItem& operator [ ] (uint32 i);
	void operator = (pItem){};
private:
	pItem Equipment[12];
	MAP_CELL bag_map[8][8];
};

extern CItem dummy;

#endif