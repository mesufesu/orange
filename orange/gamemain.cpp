#include "stdafx.h"
#include <time.h>
#include "utils.h"
#include ".\\CDirPath.h"
#include ".\\CDragonEvent.h"
#include ".\\CAttackEvent.h"
#include ".\\WzUdp.h"
#include ".\\BattleSocketManager.h"
#include ".\\user.h"
#include ".\\CMonsterSetBase.h"
#include ".\\CMonsterItemMng.h"
#include ".\\deprecated\\MapClass.h"
#include ".\\classdef.h"
#include ".\\DServerCli.h"
#include ".\\JoinServer.h"
#include ".\\packets.h"
#include "..\\Deathway\\SimpleModulus\\SimpleModulus.h"
#include ".\\gamemain.h"

int gYear = 0;
int gServerType = 0;
int gPartition = 0;
int gLanguage = 0;
int gLevelExperience[401];
bool gDisconnect = false;

bool GameMainInit()
{
	HWND hWnd = 0;
	srand((unsigned int)time(NULL));
	ReadServerInfo(); //Empty
	//LogInit(); //empty
	gSetDate();
	gDirPath.SetFirstPath(".\\data\\");
	gServerType = GetPrivateProfileInt("GameServerInfo", "ServerType", 0, gDirPath.GetNewPath("commonserver.cfg"));
	gPartition = GetPrivateProfileInt("GameServerInfo", "Partition", 0, gDirPath.GetNewPath("commonserver.cfg"));
	gLanguage = GetPrivateProfileInt("GameServerInfo", "Language", 0, gDirPath.GetNewPath("commonserver.cfg"));
	//no gsa
	pDragonEvent = new CDragonEvent;
	if(pDragonEvent == NULL)
	{
		MsgBox("CDragonEvent lMsg 110");
	}
	pAttackEvent = new CAttackEvent;
	if(pAttackEvent == NULL)
	{
		MsgBox("CAttackEvent lMsg 110");
	}
	ReadCommonServerInfo(); //empty
	/*v11 = j_CDirPath__GetNewPath("MapServerInfo.dat");
    j_CMapServerManager__LoadData(g_MapServerManager, v11);
	if ( gEnableServerDivision )
		MessageBoxA(0, "-?¦", "Warning", 0);*/
	if(!gUdpSoc.CreateSocket())
	{
		MsgBox("gUdpSoc.CreateSocket() error");
	}
	/*if(!gUdpSocCER.CreateSocket())
	{
		MsgBox("gUdpSocCER.CreateSocket() error");
	}
	gUdpSocCER.RecvSet(0x0EA66);
	gUdpSocCER.Run();
	if(!gUdpSocCE.CreateSocket())
	{
		MsgBox("gUdpSocCE.CreateSocket() error");
	}
	gUdpSocCER.SetProtocolCore(&ChaosEventProtocolCore);
	gUdpSocCE.SetProtocolCore(&ChaosEventProtocolCore);*/
	gObjInit();
	InitBattleSoccer();
	gMSetBase.LoadSetBase(".\\monstersetbase.txt");
	g_MonsterItemMng.Init();
	gLevelExperience[0] = 0;
	for(int i = 0; i < 401; ++i)
	{
		gLevelExperience[i] = 10 * i * i * (i + 9);
		if(i > 255)
		{
			gLevelExperience[i] += (i - 255) * (i - 255) * (i - 255 + 9);
		}
	}
	for(int i = 0; i < MAX_MAPS; ++i)
	{
		MapC[i].ItemInit();
		//MapC[i].LoadMapAttr(gDirPath.GetNewPath(MapAttrName[i]), i);
	}
	/*v17 = j_CDirPath__GetNewPath("terrain40_CLOSE.att");
            j_CKanturu__LoadKanturuMapAttr(v17, 0);
            v18 = j_CDirPath__GetNewPath("terrain40_OPEN.att");
            j_CKanturu__LoadKanturuMapAttr(v18, 1);*/
	DCInfo.Init();
	//Shopdata
	//wsGameServer - not used at all.
	JoinServerCli.CreateSocket(hWnd);
	DataCli.CreateSocket(hWnd); //esems useless
	RankingServerCli.CreateSocket(hWnd);
	EventServerCli.CreateSocket(hWnd);
	GameServerInfoSend();
	return 1;
}

bool ReadServerInfo()
{
	if(isFile(".\\data\\ServerInfo.dat"))
	{
		return true;
	}
	else
	{
		MsgBox("ServerInfo.dat not found");
		return false;
	}
}

void gSetDate()
{
	time_t ltime;
	time(&ltime);
	tm today;
	localtime_s(&today, &ltime);
	gYear = today.tm_year + 1900;
}

void ReadCommonServerInfo()
{
	char ip[] = "87.224.153.99";
	gUdpSoc.SendSet(ip, 55557);
	if(g_SimpleModulusCS.LoadDecryptionKey(gDirPath.GetNewPath("Dec1.dat")) == 0)
	{
		MsgBox("Dec1.dat file not found");
	}
	if(g_SimpleModulusSC.LoadEncryptionKey(gDirPath.GetNewPath("Enc2.dat")) == 0)
	{
		MsgBox("Enc2.dat file not found");
	}
}

void GameServerInfoSend()
{
	PMSG_SERVERINFO pMsg;
	if(!gDisconnect)
	{
		pMsg.h.c = 0xC1;
		pMsg.h.headcode = 0x01;
		pMsg.h.size = sizeof(PMSG_SERVERINFO);
		pMsg.Percent = 30;
		pMsg.ServerCode = 0;
		pMsg.UserCount = 12;
		pMsg.AccountCount = 10;
		pMsg.PCbangCount = 10;
		pMsg.MaxUserCount = 11;
		gUdpSoc.SendData((unsigned char*)&pMsg, sizeof(pMsg));
	}
}

void GameMonsterAllAdd()
{
	/*int gCurPaintPlayer = 0;
	for(int i = 0; i < gMSetBase.m_Count; i++)
	{
		if((gMSetBase.m_Mp[i].m_MapNumber != MAP_INDEX_DEVILSQUARE) && (gMSetBase.m_Mp[i].m_MapNumber != MAP_INDEX_DEVILSQUARE2) 
			&& (!((gMSetBase.m_Mp[i].m_MapNumber >= MAP_INDEX_BLOODCASTLE1) && (gMSetBase.m_Mp[i].m_MapNumber <= MAP_INDEX_BLOODCASTLE7)) || gMSetBase.m_Mp[i].m_Type == 232)
			&& !((gMSetBase.m_Mp[i].m_MapNumber >= MAP_INDEX_CHAOSCASTLE1) && (gMSetBase.m_Mp[i].m_MapNumber <= MAP_INDEX_CHAOSCASTLE6)))
		{
			int index;
		}
	}*/
}

void WINAPI CSThreadProc()
{
	while(TRUE)
	{
		Sleep(1000);
		GameServerInfoSend();
	}
}