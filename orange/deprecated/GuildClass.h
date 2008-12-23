#ifndef __GUILDCLASS_H_
#define __GUILDCLASS_H_

typedef struct _GUILD_INFO_STRUCT
{
  /*<thisrel this+0x0>*/ /*|0x4|*/ int Number;
  /*<thisrel this+0x4>*/ /*|0x9|*/ char Name[9];
  /*<thisrel this+0xd>*/ /*|0x20|*/ unsigned char Mark[32];
  /*<thisrel this+0x2d>*/ /*|0x1|*/ unsigned char Count;
  /*<thisrel this+0x2e>*/ /*|0x1|*/ unsigned char TotalCount;
  /*<thisrel this+0x2f>*/ /*|0x370|*/ char Names[80][11];
  /*<thisrel this+0x3a0>*/ /*|0xa0|*/ short Index[80];
  /*<thisrel this+0x440>*/ /*|0x50|*/ unsigned char Use[80];
  /*<thisrel this+0x490>*/ /*|0x50|*/ char pServer[80];
  /*<thisrel this+0x4e0>*/ /*|0x9|*/ char TargetGuildName[9];
  /*<thisrel this+0x4ea>*/ /*|0xa0|*/ short TargetIndex[80];
  /*<thisrel this+0x58c>*/ /*|0x4|*/ _GUILD_INFO_STRUCT* lpTargetGuildNode;
  /*<thisrel this+0x590>*/ /*|0x1|*/ unsigned char WarDeclareState;
  /*<thisrel this+0x591>*/ /*|0x1|*/ unsigned char WarState;
  /*<thisrel this+0x592>*/ /*|0x1|*/ unsigned char WarType;
  /*<thisrel this+0x593>*/ /*|0x1|*/ unsigned char BattleGroundIndex;
  /*<thisrel this+0x594>*/ /*|0x1|*/ unsigned char BattleTeamCode;
  /*<thisrel this+0x595>*/ /*|0x1|*/ unsigned char PlayScore;
  /*<thisrel this+0x598>*/ /*|0x4|*/ int TotalScore;
  /*<thisrel this+0x59c>*/ /*|0x3c|*/ char Notice[60];
  /*<thisrel this+0x5d8>*/ /*|0x140|*/ int GuildStatus[80];
  /*<thisrel this+0x718>*/ /*|0x1|*/ unsigned char btGuildType;
  /*<thisrel this+0x71c>*/ /*|0x4|*/ int iGuildUnion;
  /*<thisrel this+0x720>*/ /*|0x4|*/ int iGuildRival;
  /*<thisrel this+0x724>*/ /*|0x4|*/ int iTimeStamp;
  /*<thisrel this+0x728>*/ /*|0x9|*/ char szGuildRivalName[9];
  /*<thisrel this+0x734>*/ /*|0x4|*/ _GUILD_INFO_STRUCT* back;
  /*<thisrel this+0x738>*/ /*|0x4|*/ _GUILD_INFO_STRUCT* next;

  _GUILD_INFO_STRUCT();
  void SetGuildUnion(int iGuildNumber);
  void SetGuildRival(int iGuildNumber);
  int GetGuildUnion();
  int GetGuildRival();
  void SetTimeStamp();
  int GetTimeStamp();
  int CheckTimeStamp(int iTime);

} GUILD_INFO_STRUCT, *LPGUILD_INFO_STRUCT;
// <size 0x73c>

#endif