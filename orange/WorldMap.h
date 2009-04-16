/*
	Copyright 2008-2009 Ambient.5

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _WORLDMAP_H_
#define _WORLDMAP_H_

#include "player.h"

#define MAX_MAPS 60

enum MAP_ATTR
{
	MAP_NONE = 0,
	MAP_SAFE_ZONE = 0x01,
	MAP_BUSY = 0x02,
	MAP_BLOCKED1 = 0x04,
	MAP_BLOCKED2 = 0x08,
};

class CWorldMap
{
public:
	unsigned char map[256][256];
	int map_number;
	int width;
	int height;

	CWorldMap();
	void LoadMap(const char * filename);
	void UpdateMap();
	void UpdateViewport(CObject* pobj);
	unsigned char GetAttr(int x, int y);
	bool FreeToMove(uint8 x, uint8 y);

	std::vector<Guid> guids;
};

extern CWorldMap WorldMap[MAX_MAPS];

#endif