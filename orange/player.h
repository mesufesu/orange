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
	int Class;
	int ChangeUp;
	int Position; //mapx mapy map dir
	int Exp;
	int LevelUpPoint;
	int Level;
	int Str;
	int Dex;
	int Vit;
	int Energy;
	int Leadership;
	int Life;
	int Mana;
	int Shield;
	int BP;
	int Money;
	int PkLevel;
	int GMLevel;
	int AddPoint;
	int MaxAddPoint;
	int MinusPoint;
	int MaxMinusPoint;
	std::vector<int> item_guids;
	std::vector<DATA_ITEM> items;
	unsigned char Spell_data[10];
	unsigned char Guild_data[10];
};

class CPlayer : public CObject
{
public:
	ServerSocket* socket;
	PLAYER_STATUS status;
	uint32 tick_count;
	uint32 last_move_time;
	uint32 check_time;
	bool teleporting;

	int path_current;
	int path_count;
	short path_original[15];
	short path_x[15];
	short path_y[15];
	unsigned char x_old;
	unsigned char y_old;

	char account[10];
	unsigned char failed_attempts;
	DATA_CHARINFO charinfo[5];
	CItem inventory[108];
	CMyMutex view_mtx;
	std::vector<short> viewport;
	size_t send_serial;

	unsigned char rest;

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
};

#endif