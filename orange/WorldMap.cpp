#include "stdafx.h"
#include ".\\objectmanager.h"
#include ".\\packets.h"
#include ".\\WorldMap.h"

CWorldMap WorldMap[MAX_MAPS];

CWorldMap::CWorldMap()
{
	ZeroMemory(this->map, sizeof(this->map));
	//this->objects.resize(300);
	//this->objects.reserve(300);
	this->guids.clear();
	this->map_number = -1;
	this->width = -1;
	this->height = -1;
	this->last_update = GetTickCount();
}

void CWorldMap::LoadMap(const char * filename)
{
	FILE* mapfile;
	unsigned char head;
	fopen_s(&mapfile, filename, "rb");
	if(mapfile)
	{
		fread_s(&head, sizeof(head), 1, 1, mapfile);
		fread_s(&this->width, sizeof(this->width), 1, 1, mapfile);
		fread_s(&this->height, sizeof(this->height), 1, 1, mapfile);
		fread_s(this->map, sizeof(this->map), 0x100, 0x100, mapfile);
		fclose(mapfile);
	}
	else
	{
		printf_s("Error: %s notfound.\n", filename);
	}
}

void CWorldMap::UpdateMap()
{
	this->obj_mutex.Lock();
	this->guids.clear();
	for(std::map<short, CObject*>::iterator it = ObjManager.container.begin(); it != ObjManager.container.end(); ++it)
	{
		CObject* object = it->second;
		if((object->type > OBJECT_EMPTY) && (object->map == this->map_number))
		{
			this->guids.push_back(object->guid);
		}
	}
	this->obj_mutex.Unlock();
	//printf_s("Map %d has %d objects.\n", this->map_number, this->objects.size());
}

void WINAPI CWorldMap::UpdateProc(CWorldMap* map)
{
	while(TRUE)
	{
		if((GetTickCount() - map->last_update) >= 1000)
		{
			map->UpdateMap();
			for(uint32 i = 0; i < map->guids.size(); ++i)
			{
				CObject* object = ObjManager.FindByGuid(map->guids.at(i));
				if((object != NULL) && (object->type == OBJECT_PLAYER))
				{
					map->UpdateViewport((CPlayer*)object);
				}
			}
			map->last_update = GetTickCount();
		}
		Sleep(800);
	}
}

void CWorldMap::UpdateViewport(CPlayer* player)
{
	std::vector<short> view_delete;
	std::vector<short> view_create;
	view_delete.clear();
	for(uint32 i = 0; i < player->viewport.size(); ++i)
	{
		CObject * object = ObjManager.FindByGuid(player->viewport.at(i));
		if((!object) || (object->type < OBJECT_UNIT) || (object->map != player->map) || !((abs(player->x - object->x) <= 8) && (abs(player->y - object->y) <= 8)))
		{
			player->viewport.erase(player->viewport.begin() + i);
			view_delete.push_back(player->viewport.at(i));
		}
	}
	for(uint32 i = 0; i < this->guids.size(); ++i)
	{
		CObject * object = ObjManager.FindByGuid(this->guids.at(i));
		if((object) && (object->type > OBJECT_EMPTY) && (!player->InViewport(object)) && (object->map == player->map) && ((abs(player->x - object->x) <= 8) && (abs(player->y - object->y) <= 8)))
		{
			player->viewport.push_back(this->guids.at(i));
			view_create.push_back(this->guids.at(i));
		}
	}
}

unsigned char CWorldMap::GetAttr(int x, int y)
{
	return *(&map[0][0] + x + y*256);
}