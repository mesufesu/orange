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
void Player_Chat(PMSG_CHATDATA* data, CPlayer* player);

#endif