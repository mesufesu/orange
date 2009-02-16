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

#ifndef _PACKETS_H_
#define _PACKETS_H_

enum GCOPCODES
{
	GC_VIEW_PLAYER = 0x12,
	GC_VIEW_DESTROY = 0x14,
	GC_RECV_POSITION_SET = 0xD6,
};

struct PBMSG_HEAD
{
  /*<thisrel this+0x0>*/ /*|0x1|*/ unsigned char c;
  /*<thisrel this+0x1>*/ /*|0x1|*/ unsigned char size;
  /*<thisrel this+0x2>*/ /*|0x1|*/ unsigned char headcode;

  void set(unsigned char* lpBuf, unsigned char head, unsigned char size);
  void setE(unsigned char* lpBuf, unsigned char head, unsigned char size);
};
// <size 0x3>

struct PBMSG_HEAD2
{
  /*<thisrel this+0x0>*/ /*|0x1|*/ unsigned char c;
  /*<thisrel this+0x1>*/ /*|0x1|*/ unsigned char size;
  /*<thisrel this+0x2>*/ /*|0x1|*/ unsigned char headcode;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char subcode;
  void set(/*<regrel ebp+0x8>*/ /*|0x4|*/ unsigned char* lpBuf, /*<regrel ebp+0xc>*/ /*|0x1|*/ unsigned char head, /*<regrel ebp+0x10>*/ /*|0x1|*/ unsigned char sub, /*<regrel ebp+0x14>*/ /*|0x1|*/ unsigned char size);
};
// <size 0x4>

struct PBMSG_COUNT
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char count;
};
// <size 0x4>

struct PWMSG_HEAD
{
  /*<thisrel this+0x0>*/ /*|0x1|*/ unsigned char c;
  /*<thisrel this+0x1>*/ /*|0x1|*/ unsigned char sizeH;
  /*<thisrel this+0x2>*/ /*|0x1|*/ unsigned char sizeL;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char headcode;

  void set(unsigned char* lpBuf, unsigned char head, int size);
  void setE(unsigned char* lpBuf, unsigned char head, int size);

};
// <size 0x4>

struct PMSG_SERVERINFO
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x4>*/ /*|0x2|*/ short ServerCode;
  /*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char Percent;
  /*<thisrel this+0x8>*/ /*|0x2|*/ short UserCount;
  /*<thisrel this+0xa>*/ /*|0x2|*/ short AccountCount;
  /*<thisrel this+0xc>*/ /*|0x2|*/ short PCbangCount;
  /*<thisrel this+0xe>*/ /*|0x2|*/ short MaxUserCount;
};
// <size 0x10>

struct PMSG_CLIENTTIME
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x4>*/ /*|0x4|*/ unsigned long Time;
  /*<thisrel this+0x8>*/ /*|0x2|*/ unsigned short AttackSpeed;
  /*<thisrel this+0xa>*/ /*|0x2|*/ unsigned short MagicSpeed;
};
// <size 0xc>

struct SDHP_SERVERINFO
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char Type;
  /*<thisrel this+0x4>*/ /*|0x2|*/ unsigned short Port;
  /*<thisrel this+0x6>*/ /*|0x32|*/ char ServerName[50];
  /*<thisrel this+0x38>*/ /*|0x2|*/ unsigned short ServerCode;
};
// <size 0x3a>

struct PMSG_JOINRESULT
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char scode;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char result;
  /*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char NumberH;
  /*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char NumberL;
  /*<thisrel this+0x7>*/ /*|0x5|*/ unsigned char CliVersion[5];
};
// <size 0xc>

struct PMSG_IDPASS
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char subcode;
  /*<thisrel this+0x4>*/ /*|0xa|*/ char Id[10];
  /*<thisrel this+0xe>*/ /*|0xa|*/ char Pass[10];
  /*<thisrel this+0x18>*/ /*|0x4|*/ unsigned long TickCount;
  /*<thisrel this+0x1c>*/ /*|0x5|*/ unsigned char CliVersion[5];
  /*<thisrel this+0x21>*/ /*|0x10|*/ unsigned char CliSerial[16];
};
// <size 0x34>

struct PMSG_RESULT
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char subcode;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char result;
};
// <size 0x5>

struct PMSG_CHARLISTCOUNT
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char subcode;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char MaxClass;
  /*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char MoveCnt;
  /*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char Count;
};
// <size 0x7>

struct PMSG_CHARLIST
{
  /*<thisrel this+0x0>*/ /*|0x1|*/ unsigned char Index;
  /*<thisrel this+0x1>*/ /*|0xa|*/ char Name[10];
  /*<thisrel this+0xc>*/ /*|0x2|*/ unsigned short Level;
  /*<thisrel this+0xe>*/ /*|0x1|*/ unsigned char CtlCode;
  /*<thisrel this+0xf>*/ /*|0x12|*/ unsigned char CharSet[18];
  /*<thisrel this+0x21>*/ /*|0x1|*/ unsigned char btGuildStatus;
};
// <size 0x22>

struct PMSG_CHARMAPJOIN
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char subcode;
  /*<thisrel this+0x4>*/ /*|0xa|*/ char Name[10];
};
// <size 0xe>

struct PMSG_CHARMAPJOINRESULT
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char subcode;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char MapX;
  /*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char MapY;
  /*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char MapNumber;
  /*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char Dir;
  //int unk1; //1.04C+
  /*<thisrel this+0x8>*/ /*|0x8|*/ unsigned __int64 Exp;
  //int unk2;
  /*<thisrel this+0xc>*/ /*|0x8|*/ unsigned __int64 NextExp;
  /*<thisrel this+0x10>*/ /*|0x2|*/ unsigned short LevelUpPoint;
  /*<thisrel this+0x12>*/ /*|0x2|*/ unsigned short Str;
  /*<thisrel this+0x14>*/ /*|0x2|*/ unsigned short Dex;
  /*<thisrel this+0x16>*/ /*|0x2|*/ unsigned short Vit;
  /*<thisrel this+0x18>*/ /*|0x2|*/ unsigned short Energy;
  /*<thisrel this+0x1a>*/ /*|0x2|*/ unsigned short Life;
  /*<thisrel this+0x1c>*/ /*|0x2|*/ unsigned short MaxLife;
  /*<thisrel this+0x1e>*/ /*|0x2|*/ unsigned short Mana;
  /*<thisrel this+0x20>*/ /*|0x2|*/ unsigned short MaxMana;
  /*<thisrel this+0x22>*/ /*|0x2|*/ unsigned short wShield;
  /*<thisrel this+0x24>*/ /*|0x2|*/ unsigned short wMaxShield;
  /*<thisrel this+0x26>*/ /*|0x2|*/ unsigned short BP;
  /*<thisrel this+0x28>*/ /*|0x2|*/ unsigned short MaxBP;
  /*<thisrel this+0x2c>*/ /*|0x4|*/ int Money;
  /*<thisrel this+0x30>*/ /*|0x1|*/ unsigned char PkLevel;
  /*<thisrel this+0x31>*/ /*|0x1|*/ unsigned char CtlCode;
  /*<thisrel this+0x32>*/ /*|0x2|*/ short AddPoint;
  /*<thisrel this+0x34>*/ /*|0x2|*/ short MaxAddPoint;
  /*<thisrel this+0x36>*/ /*|0x2|*/ unsigned short Leadership;
  /*<thisrel this+0x38>*/ /*|0x2|*/ unsigned short wMinusPoint;
  /*<thisrel this+0x3a>*/ /*|0x2|*/ unsigned short wMaxMinusPoint;
  short unk3; //1.3.2
};
// <size 0x3c>

struct PMSG_CHARCREATE
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char subcode;
  /*<thisrel this+0x4>*/ /*|0xa|*/ char Name[10];
  /*<thisrel this+0xe>*/ /*|0x1|*/ unsigned char ClassSkin;
};
// <size 0xf>

struct PMSG_CHARCREATERESULT
{
	/*0000   c1 2c f3 01 01 41 6e 45 6c 66 00 00 00 00 00 02
0010   01 00 40 0f 00 00 00 ff ff ff ff ff ff ff ff ff
0020   ff ff ff ff ff ff ff ff ff ff ff 74*/ //elf
	/*0000   c1 2c f3 01 01 75 77 69 7a 61 00 00 00 00 00 01
0010   01 00 00 ff ff ff ff ff ff ff ff ff ff ff ff ff
0020   ff ff ff ff ff ff ff ff ff ff ff 74*/ //wizard
	/*0000   c1 2c f3 01 01 75 77 61 72 69 6f 72 6f 00 00 02
0010   01 00 20 00 00 ff ff ff ff ff ff ff ff ff ff ff
0020   ff ff ff ff ff ff ff ff ff ff ff 00*/ //warrior
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h; //c1 2c f3
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char subcode; //01
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char Result; //01
  /*<thisrel this+0x5>*/ /*|0xa|*/ unsigned char Name[10];
  /*<thisrel this+0xf>*/ /*|0x1|*/ unsigned char pos; //02
  /*<thisrel this+0x10>*/ /*|0x2|*/ unsigned short Level; //01
  /*<thisrel this+0x12>*/ /*|0x1|*/ //unsigned char Class; //00
  /*<thisrel this+0x13>*/ /*|0x18|*/ unsigned char Equipment[24];
};
// <size 0x2c>

struct PMSG_INVENTORYLIST
{
  /*<thisrel this+0x0>*/ /*|0x1|*/ unsigned char Pos;
  /*<thisrel this+0x1>*/ /*|0x7|*/ unsigned char ItemInfo[12];
};
// <size 0x8>

struct PMSG_INVENTORYLISTCOUNT
{
  /*<thisrel this+0x0>*/ /*|0x4|*/ PWMSG_HEAD h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char subcode;
  /*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char Count;
};
// <size 0x6>

struct PMSG_MOVE
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char X;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char Y;
  /*<thisrel this+0x5>*/ /*|0x8|*/ unsigned char Path[8];
};
// <size 0xd>

struct PMSG_RECVMOVE
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char NumberH;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char NumberL;
  /*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char X;
  /*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char Y;
  /*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char Path;
};
// <size 0x8>

struct PMSG_POSITION_SET
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char X;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char Y;
};

struct PMSG_RECV_POSITION_SET
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char NumberH;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char NumberL;
  /*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char X;
  /*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char Y;
};
// <size 0x7>

struct PWMSG_COUNT
{
  /*<thisrel this+0x0>*/ /*|0x4|*/ PWMSG_HEAD h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char count;
};
// <size 0x5>

struct PMSG_MONSTER_VIEWPORTCREATE
{
  /*<thisrel this+0x0>*/ /*|0x1|*/ unsigned char NumberH; // 04
  /*<thisrel this+0x1>*/ /*|0x1|*/ unsigned char NumberL; // 93
  /*<thisrel this+0x2>*/ /*|0x1|*/ unsigned char Type_HI; // 00
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char Type_LO; // 01
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char X; // 2d
  /*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char Y; // 1d
  /*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char TX; // 2d
  /*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char TY; // 1d
  /*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char Path; // 10
  /*<thisrel this+0x9>*/ /*|0x1|*/ unsigned char ViewSkillState; // 00
};
// <size 0x10>

struct PMSG_VIEWPORTCREATE
{
  /*<thisrel this+0x0>*/ /*|0x1|*/ unsigned char NumberH; //a2
  /*<thisrel this+0x1>*/ /*|0x1|*/ unsigned char NumberL; //6e
  /*<thisrel this+0x2>*/ /*|0x1|*/ unsigned char X; //34
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char Y; //21
  /*<thisrel this+0x4>*/ /*|0x12|*/ unsigned char CharSet[18];
  /*<thisrel this+0x18>*/ /*|0xa|*/ char Id[10];
  /*<thisrel this+0x22>*/ /*|0x1|*/ unsigned char TX; //34
  /*<thisrel this+0x23>*/ /*|0x1|*/ unsigned char TY; //21
  /*<thisrel this+0x24>*/ /*|0x1|*/ unsigned char DirAndPkLevel; //03
  /*<thisrel this+0x25>*/ /*|0x1|*/ unsigned char ViewSkillState; //00
};

struct PMSG_VIEWPORTDESTROY
{
  /*<thisrel this+0x0>*/ /*|0x1|*/ unsigned char NumberH;
  /*<thisrel this+0x1>*/ /*|0x1|*/ unsigned char NumberL;
};
// <size 0x2>

struct PMSG_ACTION
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char Dir;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char ActionNumber;
  /*<thisrel this+0x5>*/ /*|0x1|*/ //unsigned char iTargetIndexH;
  /*<thisrel this+0x6>*/ /*|0x1|*/ //unsigned char iTargetIndexL;
};
// <size 0x7>

struct PMSG_ACTIONRESULT
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char NumberH;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char NumberL;
  /*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char Dir;
  /*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char ActionNumber;
  /*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char TargetNumberH;
  /*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char TargetNumberL;
};
// <size 0x9>

struct PMSG_CHATDATA
{
  /*<thisrel this+0x0>*/ /*|0x3|*/ PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0xa|*/ char chatid[10];
  /*<thisrel this+0xd>*/ /*|0x3c|*/ char chatmsg[60];
};
// <size 0x49>

#endif