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
		if(!this->owner->viewport.empty())
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
	CObject * object = ObjManager.FindByGuid(this->threat_list.at(highest).guid);
	if(!object)
	{
		this->threat_list.erase(this->threat_list.begin() + highest);
		return;
	}
	if(!owner->IsInViewportList(object->guid))
	{
		this->threat_list.erase(this->threat_list.begin() + highest);
		return;
	}
	if(!owner->attack_range)
	{
		this->threat_list.erase(this->threat_list.begin() + highest);
		return;
	}
	if(owner->attack_range >= GetDistance(owner->x, owner->y, object->x, object->y))
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
	}
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

void CSimpleAI::Move(uint8 x, uint8 y)
{
	/* need to choose target point before moving to it, in some cases monster ended himself in non walkable place and attacked his target */
	PMSG_RECVMOVE packet;
	packet.h.c = 0xC1;
	packet.h.size = sizeof(PMSG_RECVMOVE);
	packet.h.headcode = 0x1D;
	packet.NumberH = HIBYTE(this->owner->guid);
	packet.NumberL = LOBYTE(this->owner->guid);
	packet.Path = 0x10;
	packet.X = x;
	packet.Y = y;
	this->owner->x_old = this->owner->x;
	this->owner->y_old = this->owner->y;
	this->owner->x = x;
	this->owner->y = y;
	this->owner->target_x = x;
	this->owner->target_y = y;
	this->owner->last_move_time = GetTickCount();
	this->owner->SendToViewport((uint8*)&packet, packet.h.size);
}