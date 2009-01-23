#include "stdafx.h"
#include ".\\commands.h"
#include ".\\ItemManager.h"
#include ".\\ItemTemplate.h"

const _COMMANDS commands[MAX_COMMANDS] = 
{
	{"help", &HelpHandler, 0},
	{"create", &CreateItemHandler, 0},
};

void CreateItemHandler(CPlayer * player, std::string cmd)
{
	char* next_token = NULL;
	char * teh_string = new char[cmd.size() + 1];
	ZeroMemory(teh_string, cmd.size() + 1);
	strcpy_s(teh_string, cmd.size() + 1, cmd.c_str());
	std::string command = strtok_s(teh_string, " ", &next_token);
	std::string stype;
	std::string sslot;
	if(!cmd.empty())
	{
		stype = strtok_s(NULL, " ", &next_token);
		if(!stype.empty())
		{
			sslot = strtok_s(NULL, " ", &next_token);
		}
		else
		{
			delete[] teh_string;
			return;
		}
	}
	else
	{
		delete[] teh_string;
		return;
	}
	delete[] teh_string;
	int32 type = -1;
	int32 slot = -1;
	sscanf_s(stype.c_str(), "%d", &type);
	sscanf_s(sslot.c_str(), "%d", &slot);
	if(type != -1 && slot != -1)
	{
		if(player->inventory[slot]->IsItem())
		{
			return;
		}
		ITEM_TEMPLATE const * it = ItemTemplate.Get(type);
		if(type)
		{
			player->inventory[slot] = (CItem*)ItemManager.CreateItem();
			player->inventory[slot]->ApplyTemplate(it);
			player->SendInventory();
		}
	}
}

void HelpHandler(CPlayer* player, std::string cmd)
{
	printf_s("OMG LOL YOU GOT ME :DDD\n");
}