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
#include "object.h"
#include "objectmanager.h"

CObject::CObject()
{
	this->guid.hi = 0;
	this->guid.lo = 0;
	this->type = OBJECT_EMPTY;
	this->teleporting = false;
	this->state = 1;
	this->viewstate = 0;
	this->viewskillstate = 0;

	this->level = 0;
	this->strength = 0;
	this->dexterity = 0;
	this->vitality = 0;
	this->energy = 0;
	this->leadership = 0;

	this->x = 0;
	this->target_x = 0;
	this->x_old = 0;
	this->y = 0;
	this->target_y = 0;
	this->y_old = 0;
	this->dir = 0;

	this->life = 0.0f;
	this->maxlife = 0.0f;
	this->mana = 0.0f;
	this->maxmana = 0.0f;
	this->shield = 0.0f;
	this->maxshield = 0.0f;
	this->bp = 0.0f;
	this->maxbp = 0.0f;

	this->model_id = -1;
	this->move_speed = 0; /* null means DEFAULT speed */
	this->last_attack_time = GetTicks();
	this->last_move_time = GetTicks();
	this->attack_range = 0;
	this->attack_speed = DEFAULT_ATTACK_SPEED;
	this->die_time = GetTicks();
	this->respawn_time = 3 * SECOND;
}

/*bool CObject::InViewport(CObject *obj)
{
	for(uint32 i = 0; i < this->viewport.size(); ++i)
	{
		if((ObjManager.FindByGuid(this->viewport.at(i)) == obj) && (obj != NULL) && (obj->type > OBJECT_EMPTY))
		{
			return true;
		}
	}
	return false;
}*/

bool CObject::IsInViewportList(GUID_LOW loguid)
{
	for(uint32 i = 0; i < this->viewport.size(); ++i)
	{
		if(this->viewport.at(i).lo == loguid)
		{
			return true;
		}
	}
	return false;
}

void CObject::SendToViewport(uint8* buffer, size_t len)
{
	for(uint32 i = 0; i < this->viewport.size(); ++i)
	{
		CObject* object = ObjManager.FindHigh(this->viewport.at(i).hi);
		if((object) && (object->type == OBJECT_PLAYER) && (object->IsInViewportList(this->guid.lo)))
		{
			((CPlayer*)object)->Send(buffer, len);
		}
	}
}