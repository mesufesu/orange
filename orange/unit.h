#ifndef _UNIT_H_
#define _UNIT_H_

#include ".\\object.h"
#include ".\\UnitAI.h"

class CUnit : public CObject
{
public:
	uint32 templ;
	uint8 startx;
	uint8 starty;
	uint32 radius;
	uint32 view_range;
	uint32 damage_min;
	uint32 damage_max;
	uint32 defense;
	uint32 magic_defense;
	uint32 attack_rating;
	uint32 block;
	uint32 move_range;
	uint32 attack_type;
	uint32 attribute;
	uint32 item_rate;
	uint32 money_rate;
	uint32 max_item_level;
	uint32 skill;
	uint32 resistance;
	CUnitAI * ai;
	CUnit();
	~CUnit();
	void SetUnit(uint32 _type, uint8 _map, uint8 _x, uint8 _y, uint8 tx, uint8 ty, uint8 ustate);
	bool ApplyTemplate(uint32 Template);
private:
};

#endif