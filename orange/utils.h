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

#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>

bool isFile(const char * file);
void MsgBox(const char * str);
void xor3(unsigned char* ptr, unsigned int len);
const std::string Query(const char * format, ...);
unsigned char LevelConvert(unsigned char level);
void GenerateExp();
uint8 GetCategory(uint16 type);

extern short RoadPathTable[16];
extern int8 RoadX[8];
extern int8 RoadY[8];
extern uint64 levelexp[401];

#endif