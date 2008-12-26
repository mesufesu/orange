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
	ObjManager.con_mutex.Lock();
	for(std::map<short, CObject*>::iterator it = ObjManager.container.begin(); it != ObjManager.container.end(); ++it)
	{
		CObject* object = it->second;
		if((object->type > OBJECT_EMPTY) && (object->map == this->map_number))
		{
			this->guids.push_back(object->guid);
		}
	}
	ObjManager.con_mutex.Unlock();
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
		if((!object) || (object->type < OBJECT_UNIT) || (object->map != player->map) || !((abs(player->x - object->x) <= 9) && (abs(player->y - object->y) <= 8)))
		{
			printf_s("[VIEWPORT] %d deletes %d from viewport\n", player->guid, player->viewport.at(i));
			view_delete.push_back(player->viewport.at(i));
			player->viewport.erase(player->viewport.begin() + i);
		}
	}
	for(uint32 i = 0; i < this->guids.size(); ++i)
	{
		CObject * object = ObjManager.FindByGuid(this->guids.at(i));
		if((object) && (object->type > OBJECT_EMPTY) && (!player->InViewport(object)) && (object->map == player->map) && ((abs(player->x - object->x) <= 9) && (abs(player->y - object->y) <= 8)) && (object != (CObject*)player))
		{
			printf_s("[VIEWPORT] %d inserts in his viewport %d\n", player->guid, this->guids.at(i));
			view_create.push_back(this->guids.at(i));
			player->viewport.push_back(this->guids.at(i));
		}
	}
	
	if(!view_delete.empty())
	{
		uint8 destroy_buffer[5000];
		ZeroMemory(destroy_buffer, sizeof(destroy_buffer));

		for(uint32 i = 0; i < view_delete.size(); ++i)
		{
			PMSG_VIEWPORTDESTROY data_destroy;
			data_destroy.NumberH = HIBYTE(view_delete.at(i));
			data_destroy.NumberL = LOBYTE(view_delete.at(i));
			memcpy(&destroy_buffer[sizeof(PBMSG_COUNT) + i * sizeof(PMSG_VIEWPORTDESTROY)], &data_destroy, sizeof(PMSG_VIEWPORTDESTROY));
		}

		PBMSG_COUNT pcount;
		pcount.h.c = 0xC1;
		pcount.h.headcode = GC_VIEW_DESTROY;
		pcount.h.size = sizeof(PBMSG_COUNT) + view_delete.size() * sizeof(PMSG_VIEWPORTDESTROY);
		pcount.count = view_delete.size();
		memcpy(destroy_buffer, &pcount, sizeof(PBMSG_COUNT));
		player->Send((unsigned char*)destroy_buffer, pcount.h.size);
	}
	if(!view_create.empty())
	{
		uint8 player_buffer[5000];
		ZeroMemory(player_buffer, sizeof(player_buffer));
		size_t player_count = 0;

		for(uint32 i = 0; i < view_create.size(); ++i)
		{
			CObject * object = ObjManager.FindByGuid(view_create.at(i));
			if(object)
			{
				switch(object->type)
				{
				case OBJECT_UNIT:
					{
						break;
					}
				case OBJECT_PLAYER:
					{
						CPlayer* obj_player = (CPlayer*)object;
						PMSG_VIEWPORTCREATE packet;
						packet.NumberH = HIBYTE(obj_player->guid);
						packet.NumberL = LOBYTE(obj_player->guid);
						if(obj_player->state && !obj_player->teleporting)
						{
							packet.NumberH |= 0x80;
						}
						packet.X = obj_player->x;
						packet.Y = obj_player->y;
						packet.TX = obj_player->target_x;
						packet.TY = obj_player->target_y;
						//packet.ViewSkillState = obj_player->viewskillstate;
						packet.ViewSkillState = 0;
						packet.DirAndPkLevel = obj_player->dir * 0x10;
						packet.DirAndPkLevel |= obj_player->pklevel & 0xf;
						memcpy(packet.Id, obj_player->name, 10);
						memcpy(packet.CharSet, obj_player->charset, 18);
						memcpy(&player_buffer[sizeof(PWMSG_COUNT) + player_count * sizeof(PMSG_VIEWPORTCREATE)], &packet, sizeof(PMSG_VIEWPORTCREATE));
						player_count++;
						break;
					}
				}
			}
		}
		if(player_count > 0)
		{
			size_t size = sizeof(PWMSG_COUNT) + player_count * sizeof(PMSG_VIEWPORTCREATE);
			PWMSG_COUNT packet_player;
			packet_player.h.c = 0xC2;
			packet_player.h.headcode = GC_VIEW_PLAYER;
			packet_player.h.sizeH = HIBYTE(size);
			packet_player.h.sizeL = LOBYTE(size);
			packet_player.count = player_count;
			memcpy(player_buffer, &packet_player, sizeof(PWMSG_COUNT));
			player->Send((unsigned char*)player_buffer, size);
		}
	}
}

unsigned char CWorldMap::GetAttr(int x, int y)
{
	return *(&map[0][0] + x + y*256);
}