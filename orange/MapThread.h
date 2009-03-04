#ifndef _MAP_THREAD_H_
#define _MAP_THREAD_H_

#include "WorldMap.h"
#include <QtCore/QThread>

#define MAP_THREADS 6

class CMapThread : public QThread
{
public:
	CMapThread();
	~CMapThread();
	void Start();
	void AddMap(CWorldMap* map);
	void Quit();
	void run();
private:
	std::vector<CWorldMap*> map_list;
	uint32 sleep_time;
	uint32 last_update;
	bool shutting_down;
};

extern CMapThread MapThreads[MAP_THREADS];

#endif