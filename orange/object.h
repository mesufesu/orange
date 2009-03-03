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

#ifndef _OBJECT_H_
#define _OBJECT_H_

enum OBJECT_TYPE
{
	VOID_BOT = -4,
	VOID_EMPTY = -3,
	VOID_UNIT = -2,
	VOID_PLAYER = -1,
	OBJECT_EMPTY = 0,
	OBJECT_UNIT = 1,
	OBJECT_PLAYER = 2,
	OBJECT_BOT = 3,
};

#define DEFAULT_MOVE_SPEED 1000
#define DEFAULT_ATTACK_SPEED 1000

#define MAX_UNIT_GUID 0x3fff //0 - 0x3fff, bcz flags 0x40 & 0x80 can be in higher part
#define MAX_BOT_GUID 0x4fff //0x3fff - 0x4fff
#define MAX_PLAYER_GUID 0x7fff //0x4fff - 0x7fff, bcz flag 0x80 can be in higher part
#define MAX_TEMP_GUID 0x1000000 //temporary guids for a non-game connections (logging in and etc.)
/* all written above is total foolness, players can have up to 0x7FFF, bcz in NumberH can be 0x80 flag, units can have up to 0x3FFF cuz of 0x40 and 0x80 */

class CObject
{
public:
	uint32 guid;
	uint8 x;
	uint8 y;
	uint8 x_old;
	uint8 y_old;
	uint32 last_move_time;
	uint32 last_attack_time;
	uint32 die_time;
	uint32 respawn_time;
	uint32 move_speed;
	uint32 attack_speed;
	uint32 attack_range;
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
	int16 model_id;

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

	std::vector<uint32> viewport;

	CObject();
	/*bool InViewport(CObject* obj);*/
	bool IsInViewportList(uint32 guid);
	void SendToViewport(unsigned char* buffer, size_t len);
};

#endif