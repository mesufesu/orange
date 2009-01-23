#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#define MAX_COMMANDS 2

#include <string>
#include ".\\player.h"

struct _COMMANDS
{
	char* cmd;
	void (*command)(CPlayer* player, std::string cmd);
	uint32 gmlevel;
};

void HelpHandler(CPlayer* player, std::string cmd);
void CreateItemHandler(CPlayer * player, std::string cmd);

extern const _COMMANDS commands[MAX_COMMANDS];

#endif