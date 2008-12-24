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