#include "stdafx.h"
#include ".\\UnitTemplate.h"
#include ".\\unit.h"

CUnit::CUnit()
{
	this->type = OBJECT_UNIT;
	this->ai = new CSimpleAI((CObject*)this);
	this->state = 0;
	this->attack_range = 0;
	this->view_range = 0;
}

CUnit::~CUnit()
{
	delete this->ai;
}

bool CUnit::SetUnit(uint32 _type, uint8 _map, uint8 _x, uint8 _y, uint8 tx, uint8 ty, uint8 ustate)
{
	const UNIT_TEMPLATE * ut = UnitTemplate.Get(_type);
	if(ut)
	{
		this->model_id = ut->model_id;
		this->templ = ut->type;
		this->x = _x;
		this->x_old = _x;
		this->target_x = tx;
		this->y = _y;
		this->y_old = _y;
		this->target_y = ty;
		this->map = _map;
		this->state = ustate;
		this->attack_range = ut->attack_range;
		this->move_speed = ut->move_speed;
		this->view_range = ut->view_range;
		this->attack_speed = ut->attack_speed;
		return true;
	}
	else
	{
		this->type = VOID_UNIT;
		return false;
	}
}