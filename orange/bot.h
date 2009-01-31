#ifndef _BOT_H_
#define _BOT_H_

#include ".\\ItemManager.h"
#include ".\\inventory.h"
#include ".\\object.h"
#include ".\\player.h"
#include ".\\utils.h"

class CBot : public CObject
{
public:
	PLAYER_STATUS status;
	uint32 tick_count;
	uint32 last_move_time;
	uint32 last_think_time;

	char name[10];
	unsigned char charset[18];
	CInventory inventory;
	std::vector<uint16> viewport;

	unsigned char rest;

	uint64 experience;
	uint16 leveluppoint;
	uint32 money;
	uint8 pklevel;
	uint8 addpoint;
	uint8 maxaddpoint;
	uint8 minuspoint;
	uint8 maxminuspoint;
	uint8 Class;
	uint8 changeup;

	CBot();
	void Kick();
	void UpdateAI();
	void SetBot(const std::string& name, uint8 map, uint8 x, uint8 y); 


	bool InViewport(CObject* obj);
	void AssignItem(DATA_ITEM* item);
	bool CheckPosition();
	void SetPosition(uint8 x, uint8 y);
	bool SavePlayer();
	void CookCharset();
	void LoadItemToInventory(DATA_ITEM * ditem);
};

#endif