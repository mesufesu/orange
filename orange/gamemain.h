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