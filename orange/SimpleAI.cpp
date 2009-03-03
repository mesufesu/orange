#include "stdafx.h"
#include "objectmanager.h"
#include "SimpleAI.h"

CSimpleAI::CSimpleAI(CObject* obj)
{
	this->last_think_time = GetTicks();
	this->threat_list.clear();
	this->owner = obj;
	this->target = NULL;
}

CSimpleAI::~CSimpleAI()
{
}

void CSimpleAI::Think()
{
	this->last_think_time = GetTicks();
	if(this->owner->attack_range && !this->owner->viewport.empty()) /* don't make threat selection if we can't attack anyone, all npc's with attack_range == 0 are non-hostile to players */
	{
		for(uint32 i = 0; i < this->owner->viewport.size(); ++i)
		{
			CObject * obj = ObjManager.FindByGuid(this->owner->viewport.at(i));
			if(obj && (obj->type > OBJECT_EMPTY) &&
			this->IsHostile(obj) &&
			this->IsInAggroDistance(obj))
			{
				this->AddThreat(this->owner->viewport.at(i), 0);
			}
		}
	}
	this->ProcessThreatList();

	if((GetTickDiff(this->owner->last_move_time) >= (GetDistance(this->owner->x, this->owner->y, this->owner->x_old, this->owner->y_old) * (DEFAULT_MOVE_SPEED - owner->move_speed))) &&
	(GetTickDiff(this->owner->last_attack_time) >= this->owner->attack_speed)) /* if time passed only then we can try to perform any action */
	{
		if(!this->threat_list.empty() && !this->target) /* valid target was not found, wait for next tick */
		{
			return;
		}
		else
		{
			this->DecideAction();
		}
	}
}

void CSimpleAI::ProcessThreatList()
{
	/* if we can't select a valid target with highest aggro we just skip one ai tick and will try next time (invalid target removed from threat list) */
	this->target = NULL;
	if(this->threat_list.empty())
	{
		return;
	}
	uint32 highest = 0;
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
		this->target = NULL;
		this->threat_list.erase(this->threat_list.begin() + highest);
		return;
	}
}

void CSimpleAI::DecideAction()
{
	/* ai is free to perform some action */
	Log.String("DBG DecideAction from CSimpleAI called.");
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

bool CSimpleAI::IsHostile(CObject * obj)
{
	if(!obj)
	{
		return false;
	}
	switch(this->owner->type) /* a lot of special conditions can be set for, like pk etc. i like it :) */
	{
	case OBJECT_UNIT:
		{
			if(obj->type == OBJECT_UNIT || obj->type == OBJECT_BOT)
			{
				return true;
			}
			break;
		}
	case OBJECT_BOT:
		{
			if(obj->type == OBJECT_BOT)
			{
				return true;
			}
			break;
		}
	default:
		{
			Log.String("AI thinks for incompatible object.");
			return false;
		}
	}
	return false;
}

bool CSimpleAI::IsInAggroDistance(CObject *obj)
{
	if(!obj)
	{
		return false;
	}
	switch(this->owner->type)
	{
	case OBJECT_UNIT:
		{
			CUnit* unit = (CUnit*)this->owner;
			if(GetDistance(unit->x, unit->y, obj->x, obj->y) <= unit->view_range)
			{
				return true;
			}
			break;
		}
	case OBJECT_BOT:
		{
			CBot * bot = (CBot*)this->owner;
			if(GetDistance(bot->x, bot->y, obj->x, obj->y) <= 10)
			{
				return true;
			}
			break;
		}
	}
	return false;
}