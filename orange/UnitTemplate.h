#ifndef _UNIT_TEMPLATE_H_
#define _UNIT_TEMPLATE_H_

struct UNIT_TEMPLATE
{
	uint32 type; //1
	uint32 model_id; //2
	uint32 rate; //3
	std::string name; //4 
	uint32 level; //5 
	uint32 health; //6 
	uint32 mana; //7 
	uint32 damage_min; //8 
	uint32 damage_max; //9 
	uint32 defense; //10 
	uint32 magic_defense; //11 
	uint32 attack_rating; //12
	uint32 block; //13 
	uint32 move_range; //14
	uint32 attack_type; //15 
	uint32 attack_range; //16
	uint32 view_range; //17
	uint32 move_speed; //18
	uint32 attack_speed; //19
	uint32 respawn_time; //20
	uint32 attribute; //21
	uint32 item_rate; //22
	uint32 money_rate; //23
	uint32 max_item_level; //24
	uint32 skill; //25
	uint32 resistance; //26 27 28 29
};

class CUnitTemplate
{
public:
	typedef std::tr1::unordered_map<uint32, UNIT_TEMPLATE> MapType;
	CUnitTemplate();
	bool Load();
	const UNIT_TEMPLATE * Get(uint32 type);
private:
	MapType container;
	QMutex mtx;
};

extern CUnitTemplate UnitTemplate;

#endif