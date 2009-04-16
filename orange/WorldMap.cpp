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

#include "stdafx.h"
#include "objectmanager.h"
#include "packets.h"
#include "WorldMap.h"

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
		Log.String("Error: %s notfound.", filename);
	}
}

void CWorldMap::UpdateMap()
{
	for(uint32 i = 0; i < this->guids.size(); ++i)
	{
		CObject* object = ObjManager.FindHigh(this->guids.at(i).hi);
		if(object)
		{
			switch(object->type)
			{
			case OBJECT_UNIT:
				{
					this->UpdateViewport(object);
					((CUnit*)object)->ai->UpdateAI();
					break;
				}
			case OBJECT_PLAYER:
				{
					this->UpdateViewport(object);
					break;
				}
			case OBJECT_BOT:
				{
					this->UpdateViewport(object);
					break;
				}
			}
		}
		/*if((object != NULL) && (object->type == OBJECT_PLAYER))
		{
			this->UpdateViewport(object);
		}
		else if((object != NULL) && (object->type == OBJECT_BOT))
		{
			this->UpdateViewport(object);
			((CBot*)object)->UpdateAI();
		}
		else if((object != NULL) && (object->type == OBJECT_UNIT))
		{
			this->UpdateViewport(object);
			((CUnit*)object)->ai->Think();
		}*/
	}
}

void CWorldMap::UpdateViewport(CObject* pobj)
{
	std::vector<uint16> view_delete;
	std::vector<uint16> view_create;
	view_delete.clear();
	/*for(uint32 i = 0; i < pobj->viewport.size(); ++i)
	{
		CObject * object = ObjManager.FindHigh(pobj->viewport.at(i).hi);
		if((!object) || 
			(object->type < OBJECT_UNIT) || 
			(object->map != pobj->map) || 
			!InViewport(pobj->type, pobj->x, pobj->y, object->x, object->y, pobj->type == OBJECT_UNIT ? ((CUnit*)pobj)->view_range : 0))
		{
			Log.Debug("[VIEWPORT] %d:%d deletes %d:%d from viewport", pobj->guid.hi, pobj->guid.lo, pobj->viewport.at(i).hi, pobj->viewport.at(i).lo);
			view_delete.push_back(pobj->viewport.at(i));
			pobj->viewport.erase(pobj->viewport.begin() + i);
		}
	}
	for(uint32 i = 0; i < this->guids.size(); ++i)
	{
		CObject * object = ObjManager.FindByGuid(this->guids.at(i));
		if((object) && 
			(object->type > OBJECT_EMPTY) && 
			(!pobj->IsInViewportList(object->guid)) && 
			(object->map == pobj->map) && 
			(object != pobj) &&
			InViewport(pobj->type, pobj->x, pobj->y, object->x, object->y, pobj->type == OBJECT_UNIT ? ((CUnit*)pobj)->view_range : 0))
		{
			Log.Debug("[VIEWPORT] %d inserts in his viewport %d", pobj->guid, this->guids.at(i));
			view_create.push_back(this->guids.at(i));
			pobj->viewport.push_back(this->guids.at(i));
		}
	}
	
	if(pobj->type != OBJECT_PLAYER)
	{
		return;
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
		((CPlayer*)pobj)->Send((unsigned char*)destroy_buffer, pcount.h.size);
	}
	if(!view_create.empty())
	{
		uint8 player_buffer[5000];
		uint8 npc_buffer[5000];
		ZeroMemory(player_buffer, sizeof(player_buffer));
		size_t player_count = 0;
		size_t npc_count = 0;

		for(uint32 i = 0; i < view_create.size(); ++i)
		{
			CObject * object = ObjManager.FindByGuid(view_create.at(i));
			if(object)
			{
				switch(object->type)
				{
				case OBJECT_UNIT:
					{
						CUnit* obj_unit = (CUnit*)object;
						PMSG_MONSTER_VIEWPORTCREATE packet;
						packet.NumberH = HIBYTE(obj_unit->guid);
						packet.NumberL = LOBYTE(obj_unit->guid);
						if(obj_unit->state == 1 && !obj_unit->teleporting) /* todo: check, bcz packet dont have flags here*/
						/*{
							packet.NumberH |= 0x80;
							packet.NumberH |= 0x40;
						}
						packet.Type_HI = HIBYTE(obj_unit->model_id);
						packet.Type_LO = LOBYTE(obj_unit->model_id);
						packet.ViewSkillState = obj_unit->viewskillstate;
						packet.X = obj_unit->x;
						packet.Y = obj_unit->y;
						packet.TX = obj_unit->target_x;
						packet.TY = obj_unit->target_y;
						packet.Path = obj_unit->dir * 0x10;
						memcpy(&npc_buffer[sizeof(PWMSG_COUNT) + npc_count * sizeof(PMSG_MONSTER_VIEWPORTCREATE)], &packet, sizeof(PMSG_MONSTER_VIEWPORTCREATE));
						npc_count++;
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
						packet.ViewSkillState = obj_player->viewskillstate;
						packet.DirAndPkLevel = obj_player->dir * 0x10;
						packet.DirAndPkLevel |= obj_player->pklevel & 0xf;
						memcpy(packet.Id, obj_player->name, 10);
						memcpy(packet.CharSet, obj_player->charset, 18);
						memcpy(&player_buffer[sizeof(PWMSG_COUNT) + player_count * sizeof(PMSG_VIEWPORTCREATE)], &packet, sizeof(PMSG_VIEWPORTCREATE));
						player_count++;
						break;
					}
				case OBJECT_BOT:
					{
						CBot* obj_bot = (CBot*)object;
						PMSG_VIEWPORTCREATE packet;
						packet.NumberH = HIBYTE(obj_bot->guid);
						packet.NumberL = LOBYTE(obj_bot->guid);
						if(obj_bot->state && !obj_bot->teleporting)
						{
							packet.NumberH |= 0x80;
						}
						packet.X = obj_bot->x;
						packet.Y = obj_bot->y;
						packet.TX = obj_bot->target_x;
						packet.TY = obj_bot->target_y;
						packet.ViewSkillState = obj_bot->viewskillstate;
						packet.DirAndPkLevel = obj_bot->dir * 0x10;
						packet.DirAndPkLevel |= obj_bot->pklevel & 0xf;
						memcpy(packet.Id, obj_bot->name, 10);
						memcpy(packet.CharSet, obj_bot->charset, 18);
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
			((CPlayer*)pobj)->Send((unsigned char*)player_buffer, size);
		}
		if(npc_count > 0)
		{
			size_t size = sizeof(PWMSG_COUNT) + npc_count * sizeof(PMSG_MONSTER_VIEWPORTCREATE);
			PWMSG_COUNT packet_npc;
			packet_npc.h.c = 0xC2;
			packet_npc.h.headcode = 0x13;
			packet_npc.h.sizeH = HIBYTE(size);
			packet_npc.h.sizeL = LOBYTE(size);
			packet_npc.count = npc_count;
			memcpy(npc_buffer, &packet_npc, sizeof(PWMSG_COUNT));
			((CPlayer*)pobj)->Send((unsigned char*)npc_buffer, size);
		}
	}*/
}

unsigned char CWorldMap::GetAttr(int x, int y)
{
	return *(&map[0][0] + x + y*256);
}

bool CWorldMap::FreeToMove(uint8 x, uint8 y)
{
	uint8 attr = this->GetAttr(x, y);
	if(!(attr & MAP_BLOCKED1) && !(attr & MAP_BLOCKED2))
	{
		return true;
	}
	return false;
}