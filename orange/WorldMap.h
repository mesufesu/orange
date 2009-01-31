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
#include <QtCore\\QThread>
#include <QtCore\\QMutex>

#define MAX_MAPS 60

class CMapThread : public QThread
{
public:
	void run();
	void * lpmap;
};

class CWorldMap
{
public:
	friend void CMapThread::run();
	unsigned char map[256][256];
	int map_number;
	int width;
	int height;
	int32 last_update;
	CMapThread MapThread;

	CWorldMap();
	void LoadMap(const char * filename);
	void UpdateMap();
	void UpdateViewport(CObject* pobj);
	void Run();
	void Quit();
	unsigned char GetAttr(int x, int y);

private:
	std::vector<uint16> guids;
	QMutex guids_mutex;
};

extern CWorldMap WorldMap[MAX_MAPS];

#endif