#include "stdafx.h"
#include ".\\UnitTemplate.h"
#include ".\\unit.h"

CUnit::CUnit()
{
	this->type = OBJECT_UNIT;
	this->state = 1;
}

bool CUnit::SetUnit(uint32 _type, uint8 _map, uint8 _x, uint8 _y)
{
	const UNIT_TEMPLATE * ut = UnitTemplate.Get(_type);
	if(ut)
	{
		this->model_id = ut->model_id;
		this->templ = ut->type;
		this->x = _x;
		this->x_old = _x;
		this->target_x = _x;
		this->y = _y;
		this->y_old = _y;
		this->target_y = _y;
		this->map = _map;
		return true;
	}
	else
	{
		this->type = VOID_UNIT;
		return false;
	}
}