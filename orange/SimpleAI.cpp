#include "stdafx.h"
#include ".\\objectmanager.h"
#include ".\\utils.h"
#include ".\\packets.h" 
#include ".\\SimpleAI.h"

CSimpleAI::CSimpleAI(CObject* obj)
{
	this->last_think_time = GetTickCount();
	this->threat_list.clear();
	this->events.clear();
	this->owner = obj;
}

void CSimpleAI::Think()
{
	if((GetTickCount() - this->last_think_time) >= 100)
	{
		this->last_think_time = GetTickCount();
		if(this->owner->attack_range && !this->owner->viewport.empty()) /* don't make threat selection if we can't attack anyone, all npc's with attack_range == 0 are non-hostile to players */
		{
			for(uint32 i = 0; i < this->owner->viewport.size(); ++i)
			{
				CObject * obj = ObjManager.FindByGuid(this->owner->viewport.at(i));
				if(obj && (obj->type > OBJECT_EMPTY) && obj->type != OBJECT_UNIT)/* todo: make an is_enemy check, summoned units are also OBJECT_UNIT :) */
				{
					this->AddThreat(this->owner->viewport.at(i), 0);
				}
			}
		}
		this->ProcessThreatList();
		for(uint32 i = 0; i < this->events.size(); ++i)
		{
			this->ProcessAIEvent(this->events.at(i));
		}
	}
}

void CSimpleAI::ProcessThreatList()
{
	if(this->threat_list.empty())
	{
		/* if we don't hate anyone we must perform random movement */
		return;
	}
	uint highest = 0;
	for(uint32 i = 0; i < this->threat_list.size(); ++i)
	{
		if(this->threat_list.at(i).amount > this->threat_list.at(highest).amount)
		{
			highest = i;
		}
	}
	this->target = ObjManager.FindByGuid(this->threat_list.at(highest).guid);
	if(!this->target)
	{
		this->threat_list.erase(this->threat_list.begin() + highest);
		return;
	}
	if(!owner->IsInViewportList(this->target->guid))
	{
		this->threat_list.erase(this->threat_list.begin() + highest);
		return;
	}
	if(((GetTickCount() - this->owner->last_move_time) >= (GetDistance(this->owner->x, this->owner->y, this->owner->x_old, this->owner->y_old) * (DEFAULT_MOVE_SPEED - owner->move_speed))) &&
		((GetTickCount() - this->owner->last_attack_time) >= (this->owner->attack_speed))) /* if time passed only then we can try to perform any action */
	{
		if(this->owner->attack_range >= GetDistance(this->owner->x, this->owner->y, this->target->x, this->target->y))
		{
			Log.String("%u wants to tore apart %u.", this->owner->guid, this->target->guid);
		}
		else
		{
			this->PerformMovementToTarget();
		}
	}
	/*if(owner->attack_range >= GetDistance(owner->x, owner->y, object->x, object->y))
	{
		if((GetTickCount() - this->owner->last_move_time) >= (GetDistance(owner->x, owner->y, owner->x_old, owner->y_old) * (DEFAULT_MOVE_SPEED - owner->move_speed)))
		{
			Log.String("%u wants to tore apart %u.", owner->guid, object->guid);
		}
		else
		{
			Log.String("%u wants to tore apart %u, but he isn't at the spot really.", owner->guid, object->guid);
		}
	}
	else
	{
		if((GetTickCount() - owner->last_move_time) >= (GetDistance(owner->x, owner->y, owner->x_old, owner->y_old) * (DEFAULT_MOVE_SPEED - owner->move_speed)))
		{
			Log.String("%u ready to move to %u, moving", owner->guid, object->guid);
			this->Move(object->x, object->y);
		}
		else
		{
			Log.String("%u wants to move to %u, but its not time yet.", owner->guid, object->guid);
		}
	}*/
}

void CSimpleAI::AddThreat(uint32 target_guid, uint32 amount)
{
	for(uint32 i = 0; i < this->threat_list.size(); ++i)
	{
		if(this->threat_list.at(i).guid == target_guid)
		{
			this->threat_list.at(i).amount += amount;
			return;
		}
	}
	ThreatElement element;
	element.amount = amount;
	element.guid = target_guid;
	this->threat_list.push_back(element);
}

void CSimpleAI::ProcessAIEvent(AIEvent _event)
{
}

void CSimpleAI::PerformMovementToTarget()
{
	std::vector<std::pair<uint8, uint8>> spots;
	uint8 tx = this->target->x;
	uint8 ty = this->target->y;
	if(tx > 0 && ty < 255)
	{
		uint8 attr = WorldMap[target->map].GetAttr(tx - 1, ty + 1);
		if(!(attr & 0x04) && !(attr & 0x08))
		{
			spots.push_back(std::make_pair(tx - 1, ty + 1));
		}
	}
	if(ty < 255)
	{
		uint8 attr = WorldMap[target->map].GetAttr(tx, ty + 1);
		if(!(attr & 0x04) && !(attr & 0x08))
		{
			spots.push_back(std::make_pair(tx, ty + 1));
		}
	}
	if(tx < 255 && ty < 255)
	{
		uint8 attr = WorldMap[target->map].GetAttr(tx + 1, ty + 1);
		if(!(attr & 0x04) && !(attr & 0x08))
		{
			spots.push_back(std::make_pair(tx + 1, ty + 1));
		}
	}
	if(tx < 255)
	{
		uint8 attr = WorldMap[target->map].GetAttr(tx + 1, ty);
		if(!(attr & 0x04) && !(attr & 0x08))
		{
			spots.push_back(std::make_pair(tx + 1, ty));
		}
	}
	if(tx < 255 && ty > 0)
	{
		uint8 attr = WorldMap[target->map].GetAttr(tx + 1, ty - 1);
		if(!(attr & 0x04) && !(attr & 0x08))
		{
			spots.push_back(std::make_pair(tx + 1, ty - 1));
		}
	}
	if(ty > 0)
	{
		uint8 attr = WorldMap[target->map].GetAttr(tx, ty - 1);
		if(!(attr & 0x04) && !(attr & 0x08))
		{
			spots.push_back(std::make_pair(tx, ty - 1));
		}
	}
	if(tx > 0 && ty > 0)
	{
		uint8 attr = WorldMap[target->map].GetAttr(tx - 1, ty - 1);
		if(!(attr & 0x04) && !(attr & 0x08))
		{
			spots.push_back(std::make_pair(tx - 1, ty - 1));
		}
	}
	if(spots.empty())
	{
		return;
	}
	uint32 least_expensive = 0;
	for(uint32 i = 0; i < spots.size(); ++i)
	{
		if(GetDistance(this->owner->x, this->owner->y, spots.at(i).first, spots.at(i).second) <= GetDistance(this->owner->x, this->owner->y, spots.at(least_expensive).first, spots.at(least_expensive).second))
		{
			least_expensive = i;
		}
	}
	uint8 nx = spots.at(least_expensive).first;
	uint8 ny = spots.at(least_expensive).second;
	uint32 distance = GetDistance(this->owner->x, this->owner->y, nx, ny);
	if(distance > 9)
	{
		float mult = (float)9 / (float)distance;
		nx = this->owner->x - (int32)(((float)(this->owner->x - nx)) * mult);
		ny = this->owner->y - (int32)(((float)(this->owner->y - ny)) * mult);
	}

	/* need to choose target point before moving to it, in some cases monster ended himself in non walkable place and attacked his target */
	PMSG_RECVMOVE packet;
	packet.h.c = 0xC1;
	packet.h.size = sizeof(PMSG_RECVMOVE);
	packet.h.headcode = 0x1D;
	packet.NumberH = HIBYTE(this->owner->guid);
	packet.NumberL = LOBYTE(this->owner->guid);
	packet.Path = 0x10; /* still lazy to calculate direction */
	packet.X = nx;
	packet.Y = nx;
	this->owner->x_old = this->owner->x;
	this->owner->y_old = this->owner->y;
	this->owner->x = nx;
	this->owner->y = nx;
	this->owner->target_x = nx;
	this->owner->target_y = nx;
	this->owner->last_move_time = GetTickCount();
	this->owner->SendToViewport((uint8*)&packet, packet.h.size);
}