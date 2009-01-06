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

#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

bool GameMainInit();
bool ReadServerInfo();
bool LogInit();
void gSetDate();
void ReadCommonServerInfo();
void GameServerInfoSend();
void WINAPI CSThreadProc();

extern int gYear;
extern int gServerType;
extern int gPartition;
extern int gLanguage;
extern int gLevelExperience[401];
extern bool gDisconnect;

#endif