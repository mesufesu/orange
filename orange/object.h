#ifndef _OBJECT_H_
#define _OBJECT_H_

enum OBJECT_TYPE
{
	VOID_EMPTY = -3,
	VOID_UNIT = -2,
	VOID_PLAYER = -1,
	OBJECT_EMPTY = 0,
	OBJECT_UNIT = 1,
	OBJECT_PLAYER = 2,
};

class CObject
{
public:
	short guid;
	unsigned char x;
	unsigned char y;
	unsigned char target_x;
	unsigned char target_y;
	unsigned char map;
	unsigned char dir;
	unsigned char action;
	unsigned char state;
	unsigned char viewstate;
	unsigned char viewskillstate;
	bool teleporting;
	OBJECT_TYPE type;

	uint16 level;
	uint16 strength;
	uint16 dexterity;
	uint16 vitality;
	uint16 energy;
	uint16 leadership;
	float life;
	float maxlife;
	float mana;
	float maxmana;
	float shield;
	float maxshield;
	float bp;
	float maxbp;

	CObject();
};

#endif