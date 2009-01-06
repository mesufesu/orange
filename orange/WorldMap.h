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

#include <vector>
#include ".\\player.h"
#include ".\\mutex.h"

#define MAX_MAPS 60

class CWorldMap
{
public:
	HANDLE map_handle;
	CMyMutex obj_mutex;
	unsigned char map[256][256];
	std::vector<short> guids;
	int map_number;
	int width;
	int height;
	int last_update;

	CWorldMap();
	void LoadMap(const char * filename);
	void UpdateMap();
	void UpdateViewport(CPlayer* player);
	static void WINAPI UpdateProc(CWorldMap* map);
	unsigned char GetAttr(int x, int y);
};

extern CWorldMap WorldMap[MAX_MAPS];

#endif