#include "stdafx.h"
#include ".\\UnitTemplate.h"
#include ".\\unit.h"

CUnit::CUnit()
{
	this->type = OBJECT_UNIT;
	this->ai = new CSimpleAI((CObject*)this);
	this->startx = 0;
	this->starty = 0;
	this->state = 0;
	this->attack_range = 0;
	this->view_range = 0;
	this->damage_min = 0;
	this->damage_max = 0;
	this->defense = 0;
	this->magic_defense = 0;
	this->attack_rating = 0;
	this->block = 0;
	this->move_range = 0;
	this->attack_type = 0;
	this->attribute = 0;
	this->item_rate = 0;
	this->money_rate = 0;
	this->max_item_level = 0;
	this->skill = 0;
	this->resistance = 0;
	this->radius = 0;
}

CUnit::~CUnit()
{
	delete this->ai;
}

void CUnit::SetUnit(uint32 _type, uint8 _map, uint8 _x, uint8 _y, uint8 tx, uint8 ty, uint8 ustate)
{
	if(this->ApplyTemplate(_type))
	{
		this->startx = _x;
		this->x = _x;
		this->x_old = _x;
		this->target_x = tx;
		this->starty = _y;
		this->y = _y;
		this->y_old = _y;
		this->target_y = ty;
		this->map = _map;
		this->state = ustate;
		this->radius = 10;
	}
}

bool CUnit::ApplyTemplate(uint32 Template)
{
	const UNIT_TEMPLATE * ut = UnitTemplate.Get(Template);
	if(!ut)
	{
		Log.String("Template %u for unit %u can't be found. Deleting.", Template, this->guid);
		this->type = VOID_UNIT;
		return false;
	}
	this->templ = Template;
	this->model_id = ut->model_id;
	this->level = ut->level;
	this->life = ut->health;
	this->maxlife = ut->health;
	this->mana = ut->mana;
	this->maxmana = ut->mana;
	this->damage_min = ut->damage_min;
	this->damage_max = ut->damage_max;
	this->defense = ut->defense;
	this->magic_defense = ut->magic_defense;
	this->attack_rating = ut->attack_rating;
	this->block = ut->block;
	this->move_range = ut->move_range;
	if(this->move_range == 0)
	{
		this->state = 1;
	}
	this->attack_type = ut->attack_type;
	this->attack_range = ut->attack_range;
	this->view_range = ut->view_range;
	this->move_speed = ut->move_speed;
	this->attack_speed = ut->attack_speed;
	this->respawn_time = ut->respawn_time * SECOND;
	this->attribute = ut->attribute;
	this->item_rate = ut->item_rate;
	this->money_rate = ut->money_rate;
	this->max_item_level = ut->max_item_level;
	this->skill = ut->skill;
	this->resistance = ut->resistance;
	return true;
}