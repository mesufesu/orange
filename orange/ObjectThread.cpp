#include "stdafx.h"
#include "ObjectThread.h"

CObjectThread ObjThread(&ObjManager, &WorldMap[0]);

CObjectThread::CObjectThread(CObjectManager * manager, CWorldMap * maps)
{
	this->mang = manager;
	this->rwl = &this->mang->rwl;
	for(uint32 i = 0; i < MAX_MAPS; ++i)
	{
		this->map[i] = &maps[i];
	}
	this->shutting_down = false;
}

void CObjectThread::run()
{
	CTimer cleanup(10 * SECOND);
	CTimer maps(100);
	while(!this->shutting_down)
	{
		if(cleanup.Passed())
		{
			this->rwl->lockForRead();
			CObjectManager::MapType::iterator itr;
			for(itr = this->mang->container.begin(); itr != this->mang->container.end(); true)
			{
				CObjectManager::MapType::iterator current = itr;
				++itr;
				CObject * object = current->second;
				if(object && object->type < OBJECT_EMPTY)
				{
					this->rwl->lockForWrite();
					switch(object->type)
					{
					case VOID_PLAYER:
						{
							CPlayer * player = (CPlayer*)object;
							delete player;
							break;
						}
					case VOID_UNIT:
						{
							CUnit * unit = (CUnit*)object;
							delete unit;
							break;
						}
					case VOID_EMPTY:
						{
							break;
						}
					case VOID_BOT:
						{
							CBot * bot = (CBot*)object;
							delete bot;
							break;
						}
					}
					this->mang->container.erase(current);
					this->rwl->unlock();
				}
			}
			this->rwl->unlock();
		}
		if(maps.Passed())
		{
			for(uint32 i = 0; i < MAX_MAPS; ++i)
			{
				this->map[i]->guids.clear();
			}
			this->rwl->lockForRead();
			CObjectManager::MapType::iterator itr;
			for(itr = this->mang->container.begin(); itr != this->mang->container.end(); true)
			{
				CObjectManager::MapType::iterator current = itr;
				++itr;
				CObject * object = current->second;
				if(object && (object->map >= 0 && object->map < MAX_MAPS) && object->type > OBJECT_EMPTY)
				{
					this->map[object->map]->guids.push_back(object->guid);
				}
			}
			this->rwl->unlock();
			init_genrand(GetTicks());
			for(uint32 i = 0; i < MAX_MAPS; ++i)
			{
				CWorldMap * pmap = this->map[i];
				for(uint32 i = 0; i < pmap->guids.size(); ++i)
				{
					if(pmap->guids.at(i).lo == 0)
					{
						uint32 count = 0;
						while(count < RETRIES)
						{
							++count;
							GUID_LOW lo = uint32(genrand_int32()) % MAX_GUID;
							bool found = false;
							for(uint32 k = 0; k < pmap->guids.size(); ++k)
							{
								if(pmap->guids.at(k).lo == lo)
								{
									found = true;
									break;
								}
							}
							if(!found)
							{
								this->mang->FindHigh(pmap->guids.at(i).hi)->guid.lo = lo;
								pmap->guids.at(i).lo = lo;
								break;
							}
						}
						assert(count != RETRIES);
					}
				}
				pmap->UpdateMap();
			}
		}
	}
	this->msleep(DEFSLEEP);
}

void CObjectThread::Shutdown()
{
	this->shutting_down = true;
}