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
	/*std::vector<void*> new_container;
	new_container.clear();
	std::vector<void*> trash_container;
	trash_container.clear();
	std::vector<int> trash_nums;
	trash_nums.clear();
	player->view_mtx.Lock();
	for(uint32 i = 0; i < player->viewport.size(); ++i)
	{
		if(((CObject*)player->viewport.at(i))->map == player->map)
		{
			if(abs(((CObject*)player->viewport.at(i))->x - player->x) <= 8)
			{
				if(abs(((CObject*)player->viewport.at(i))->y - player->y) > 8)
				{
					trash_container.push_back(player->viewport.at(i));
					trash_nums.push_back(i);
				}
			}
			else
			{
				trash_container.push_back(player->viewport.at(i));
				trash_nums.push_back(i);
			}
		}
		else
		{
			trash_container.push_back(player->viewport.at(i));
			trash_nums.push_back(i);
		}
	}

	for(uint32 i = 0; i < trash_nums.size(); ++i)
	{
		player->DeleteFromViewport(player->viewport.at(trash_nums.at(i)));
	}

	this->obj_mutex.Lock();
	for(uint32 i = 0; i < this->objects.size(); ++i)
	{
		if((((CObject*)this->objects.at(i)) != (CObject*)player) && (abs(((CObject*)this->objects.at(i))->x - player->x) <= 8))
		{
			if(abs(((CObject*)this->objects.at(i))->y - player->y) <= 8)
			{
				if(!player->InViewport(((CObject*)this->objects.at(i))))
				{
					player->viewport.push_back(this->objects.at(i));
					new_container.push_back(this->objects.at(i));
				}
			}
		}
	}
	this->obj_mutex.Unlock();
	player->view_mtx.Unlock();
	//sendpackets here
	if(!new_container.empty())
	{
		uint8 player_buffer[5000];
		ZeroMemory(player_buffer, sizeof(player_buffer));
		size_t player_cnt = 0;
		size_t unit_cnt = 0;
		/*unsigned char buffer[] = {0xc2, 0x00, 0x19, 0x13, 0x02, 0x04, 0x93, 0x00, 0x01, 0x83, 0x85, 0x83, 0x85, 0x80, 0x00, 0x04, 0xd3, 0x00, 0x07, 0x86, 0x85, 0x82, 0x87, 0x70, 0x08};
		player->Send(buffer, 0x19);*/
		/*for(uint32 i = 0; i < new_container.size(); ++i)
		{
			CObject* obj = (CObject*)new_container.at(i);
			switch(obj->type)
			{
			case OBJECT_UNIT:
				{
					break;
				}
			case OBJECT_PLAYER:
				{
					printf_s("Spotted a player\n");
					CPlayer * obj_player = (CPlayer*)obj;
					PMSG_VIEWPORTCREATE pvc_data;
					ZeroMemory(&pvc_data, sizeof(PMSG_VIEWPORTCREATE));
					pvc_data.NumberH = HIBYTE(obj_player->guid);
					pvc_data.NumberH |= 0x80;
					pvc_data.NumberL = LOBYTE(obj_player->guid);
					pvc_data.DirAndPkLevel = 0x10 * obj_player->dir;
					pvc_data.X = obj_player->x;
					pvc_data.Y = obj_player->y;
					pvc_data.TX = obj_player->target_x;
					pvc_data.TY = obj_player->target_y;
					//pvc_data.ViewSkillState = obj_player->viewskillstate;
					pvc_data.ViewSkillState = 0;
					memcpy(pvc_data.Id, obj_player->account, 10); //todo: add a name to player =)
					memcpy(&player_buffer[sizeof(PWMSG_COUNT) + player_cnt * sizeof(PMSG_VIEWPORTCREATE)], &pvc_data, sizeof(PMSG_VIEWPORTCREATE));
					player_cnt++;
					break;
				}
			}
		}
		if(player_cnt > 0)
		{
			unsigned short size = sizeof(PWMSG_COUNT) + player_cnt * sizeof(PMSG_VIEWPORTCREATE);
			PWMSG_COUNT pcnt_data;
			pcnt_data.h.c = 0xC2;
			pcnt_data.h.headcode = 0x12;
			pcnt_data.h.sizeH = HIBYTE(size);
			pcnt_data.h.sizeL = LOBYTE(size);
			pcnt_data.count = player_cnt;
			memcpy(player_buffer, &pcnt_data, sizeof(PWMSG_COUNT));
			player->Send(player_buffer, size);
		}
	}*/
}

unsigned char CWorldMap::GetAttr(int x, int y)
{
	return *(&map[0][0] + x + y*256);
}