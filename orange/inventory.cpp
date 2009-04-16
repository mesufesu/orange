#include "stdafx.h"
#include "inventory.h"
#include "ItemTemplate.h"

CItem dummy;

void MAP_CELL::clear()
{
	this->add = 0xff;
	this->item = &dummy;
	this->type = CELL_EMPTY;
}

CInventory::CInventory()
{
	for(uint32 i = 0; i < 12; ++i)
	{
		this->Equipment[i] = (pItem)&dummy;
	}
	for(uint32 i = 0; i < 8; ++i)
	{
		for(uint32 k = 0; k < 8; ++k)
		{
			this->bag_map[i][k].clear();
		}
	}
}

pItem& CInventory::operator [](uint32 i)
{
	if(i >= 0 && i < 12)
	{
		return this->Equipment[i];
	}
	else if(i >= 12 && i < 78)
	{
		return this->bag_map[(i - 12) / 8][(i - 12) - (((i - 12) / 8) * 8)].item;
	}
	assert(false);
	return this->Equipment[0];
}

bool CInventory::InsertItem(pItem item)
{
	if(!item)
	{
		return false;
	}
	const ITEM_TEMPLATE * it = ItemTemplate.Get(item->type);
	uint32 free_x = 0xff;
	uint32 free_y = 0xff;
	uint32 item_square = it->width * it->height;
	bool stop = false;
	for(uint32 i = 0; (i < 8) && (!stop); ++i)
	{
		for(uint32 j = 0; j < 8; ++j)
		{
			if(this->bag_map[i][j].type == CELL_EMPTY)
			{
				uint32 count = 0;
				for(uint32 y = 0; y < it->height; ++y)
				{
					for(uint32 x = 0; x < it->width; ++x)
					{
						if(this->bag_map[i + y][j + x].type == CELL_EMPTY)
						{
							++count;
						}
					}
				}
				if(count == item_square)
				{
					free_x = j;
					free_y = i;
					stop = true;
					break;
				}
			}
		}
	}
	if(free_x != 0xff && free_y != 0xff)
	{
		for(uint32 y = 0; y < it->height; ++y)
		{
			for(uint32 x = 0; x < it->width; ++x)
			{
				this->bag_map[free_y + y][free_x + x].type = CELL_BUSY;
				this->bag_map[free_y + y][free_x + x].item = item;
				this->bag_map[free_y + y][free_x + x].add = free_y * 8 + free_x;
			}
		}
		this->bag_map[free_y][free_x].type = CELL_MAIN;
		return true;
	}
	return false;
}

pItem CInventory::RemoveItem(uint32 i)
{
	if(i < 12)
	{
		pItem temp = this->Equipment[i];
		this->Equipment[i] = &dummy;
		return temp; /* do i have to return null in case of not existed item? */
	}
	else if(i < 78 && i >= 12)
	{
		uint32 ii = i - 12;
		switch(this->bag_map[ii / 8][ii - ((ii / 8) * 8)].type)
		{
		case CELL_MAIN:
		case CELL_BUSY:
			{
				uint32 add = this->bag_map[ii / 8][ii - ((ii / 8) * 8)].add;
				uint32 x = add - (add / 8) * 8;
				uint32 y = add / 8;
				pItem item = this->bag_map[y][x].item;
				this->bag_map[y][x].clear();
				return item;
			}
		}
	}
	return NULL;
}