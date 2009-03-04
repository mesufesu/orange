#include "stdafx.h"
#include "MapThread.h"

CMapThread MapThreads[MAP_THREADS];

CMapThread::CMapThread()
{
	this->map_list.clear();
	this->sleep_time = 0;
	this->last_update = GetTicks();
	this->shutting_down = false;
}

CMapThread::~CMapThread()
{
	this->map_list.clear();
}

void CMapThread::run()
{
	this->sleep_time = SECOND / config.world_tick_rate;
	while(TRUE && !this->shutting_down)
	{
		if(GetTickDiff(this->last_update) >= this->sleep_time)
		{
			for(uint32 i = 0; i < this->map_list.size(); ++i)
			{
				this->map_list.at(i)->UpdateMap();
			}
			this->last_update = GetTicks();
		}
		this->msleep(3);
	}
}

void CMapThread::Start()
{
	this->start();
}

void CMapThread::Quit()
{
	this->shutting_down = true;
}

void CMapThread::AddMap(CWorldMap *map)
{
	if(!map)
	{
		Log.String("Passed NULL map.");
		return;
	}
	this->map_list.push_back(map);
}