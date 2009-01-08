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

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include ".\\ServerSocket.h"
#include ".\\ItemManager.h"
#include ".\\mutex.h"
#include ".\\object.h"

enum PLAYER_STATUS
{
	PLAYER_EMPTY = 0,
	PLAYER_CONNECTED = 1,
	PLAYER_LOGGED = 2,
	PLAYER_PLAYING = 3,
};

enum OBJECTS
{
	_OBJECT_EMPTY	= -1,
	_OBJECT_USER	= 1,
	_OBJECT_MONSTER	= 2,
	_OBJECT_NPC		= 3,
	_OBJECT_DUMMY	= 4,
	_OBJECT_ITEM		= 5,
};

enum PLAYER_WARDROBE
{
	WEAPON_01	= 0,	// <--
	WEAPON_02	= 1,	// <--
	HELMET		= 2,	// <--
	ARMOR		= 3,	// <--
	PANTS		= 4,	// <--
	GLOVES		= 5,	// <--
	BOOTS		= 6,	// <--
	WINGS		= 7,	// <--
	GUARDIAN	= 8,	// <--
	PENDANT		= 9,	// <--
	RING_01		= 10,	// <--
	RING_02		= 11,	// <--
};

struct DATA_CHARINFO
{
	char Account[11];
	char Name[11];
	uint8 Class;
	uint8 ChangeUp;
	uint32 Position; //mapx mapy map dir
	uint64 Exp;
	uint8 LevelUpPoint;
	uint16 Level;
	uint16 Str;
	uint16 Dex;
	uint16 Vit;
	uint16 Energy;
	uint16 Leadership;
	uint32 Life;
	uint32 Mana;
	uint32 Shield;
	uint32 BP;
	uint32 Money;
	uint8 PkLevel;
	uint32 GMLevel;
	uint8 AddPoint;
	uint8 MaxAddPoint;
	uint8 MinusPoint;
	uint8 MaxMinusPoint;
	std::vector<uint32> item_guids;
	DATA_ITEM temp_inv[12];
	std::vector<uint8> spell_data;
};

class CPlayer : public CObject
{
public:
	ServerSocket* socket;
	PLAYER_STATUS status;
	uint32 tick_count;
	uint32 last_move_time;
	uint32 last_save_time;
	uint32 check_time;

	size_t path_count;
	unsigned char x_old;
	unsigned char y_old;

	char account[10];
	char name[10];
	unsigned char charset[18];
	unsigned char failed_attempts;
	DATA_CHARINFO charinfo[5];
	CItem * inventory[108];
	CMyMutex view_mtx;
	std::vector<short> viewport;
	size_t send_serial;

	unsigned char rest;

	uint64 experience;
	uint16 leveluppoint;
	uint32 money;
	uint8 pklevel;
	uint32 gmlevel;
	uint8 addpoint;
	uint8 maxaddpoint;
	uint8 minuspoint;
	uint8 maxminuspoint;
	uint8 Class;
	uint8 changeup;

	CPlayer();
	void Send(unsigned char* buffer, size_t len);
	void Close();
	void SetStatus(unsigned char status);
	void SendInventory();
	int LoadCharacters();
	bool InViewport(CObject* obj);
	//void DeleteFromViewport(void* obj);
	void AssignItem(DATA_ITEM* item);
	void SendToViewport(unsigned char* buffer, size_t len);
	bool CheckPosition();
	bool CheckPacketTime();
	void SetPosition(uint8 x, uint8 y);
	bool SavePlayer();
	void CookCharset();
};

extern const CItem dummy;

#endif