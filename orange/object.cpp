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
#include ".\\object.h"
#include ".\\objectmanager.h"

CObject::CObject()
{
	this->guid = -1;
	type = OBJECT_EMPTY;
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

	this->life = 0.0f;
	this->maxlife = 0.0f;
	this->mana = 0.0f;
	this->maxmana = 0.0f;
	this->shield = 0.0f;
	this->maxshield = 0.0f;
	this->bp = 0.0f;
	this->maxbp = 0.0f;
}

bool CObject::InViewport(CObject *obj)
{
	for(uint32 i = 0; i < this->viewport.size(); ++i)
	{
		if((ObjManager.FindByGuid(this->viewport.at(i)) == obj) && (obj != NULL) && (obj->type > OBJECT_EMPTY))
		{
			return true;
		}
	}
	return false;
}

void CObject::SendToViewport(unsigned char* buffer, size_t len)
{
	for(uint32 i = 0; i < this->viewport.size(); ++i)
	{
		CObject* object = ObjManager.FindByGuid(this->viewport.at(i));
		if((object) && (object->type == OBJECT_PLAYER))
		{
			((CPlayer*)object)->Send(buffer, len);
		}
	}
}