#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include ".\\packets.h"
#include ".\\objectmanager.h"

void ProtocolCore(CPlayer* player, unsigned char opcode, unsigned char* buffer, size_t size, bool Encrypt, int serial);
void TestJoinSend(CPlayer* player, int result);
void JoinResult(CPlayer* player, unsigned char result);
void Join_LoginHandler(PMSG_IDPASS* data, CPlayer* player);
void Join_GetCharacters(CPlayer* player);
void Join_WorldJoin(PMSG_CHARMAPJOIN* data, CPlayer* player);
void Join_CreateCharacter(PMSG_CHARCREATE * data, CPlayer* player);
void World_Move(PMSG_MOVE* data, CPlayer * player);
void World_Action(PMSG_ACTION* data, CPlayer* player);

#endif