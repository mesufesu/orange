#include "stdafx.h"
#include ".\\mathlib.h"
#include ".\\user.h"

OBJECTSTRUCT gObj[OBJ_MAX];

int gObjCount;
int gObjMonCount;
int gObjCallMonCount;
int FrustumX[4];
int FrustumY[4];

//OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJ;

int gObjIsConnected(int aIndex)
{
	if((aIndex >= 0) && (aIndex <= (OBJ_MAX - 1)))
	{
		return (gObj[aIndex].Connected == PLAYER_PLAYING);
	}
	else
	{
		return FALSE;
	}
}

void gObjInit()
{
	gObjCount = OBJ_MONSTER_MAX;
	gObjMonCount = NULL;
	gObjCallMonCount = OBJ_MONSTER_MAX - OBJ_SUMMON_MAX;
	CItem* pTempInventory = new CItem[108]; //sense?
	unsigned char * pTempInventoryMap = new unsigned char[96];
	for(int i = 0; i < OBJ_MAX; ++i)
	{
		ZeroMemory(&gObj[i], sizeof(OBJECTSTRUCT));
		gObj[i].Type = -1;
		gObj[i].m_socket = -1;
		gObj[i].PathTime = GetTickCount();
		gObj[i].m_RecallMon = -1;
		CMagicInf * pMagicBack = new CMagicInf[60];
		gObj[i].m_lpMagicBack = pMagicBack;
		CMagicInf * pMagic = new CMagicInf[60];
		gObj[i].Magic = pMagic;
		if(i < OBJ_MONSTER_MAX)
		{
			gObj[i].Inventory1 = pTempInventory;
			gObj[i].Inventory2 = pTempInventory;
			gObj[i].InventoryMap1 = pTempInventoryMap;
			gObj[i].InventoryMap2 = pTempInventoryMap;
		}
		else
		{
			gObj[i].Inventory1 = new CItem[108];
			gObj[i].Inventory2 = new CItem[108];
			gObj[i].InventoryMap1 = new unsigned char[96];
			gObj[i].InventoryMap2 = new unsigned char[96];
		}
		if(i >= OBJ_MONSTER_MAX)
		{
			gObj[i].Trade = new CItem[32];
			gObj[i].TradeMap = new unsigned char[32];
			gObj[i].pWarehouse = new CItem[120];
			gObj[i].pWarehouseMap = new unsigned char[120];
		}
		gObj[i].WarehouseCount = 0;
		gObj[i].pChaosBox = 0;
		if(i >= OBJ_MONSTER_MAX)
		{
			//allocate per socket context here
		}
		InitializeCriticalSection(&gObj[i].m_critPShopTrade);
	}
	InitFrustum();
}

void InitFrustum()
{
	float Frustum[4][3];
	float CameraViewFar = 2400.0f;
	float CameraViewNear = CameraViewFar * 0.19f;
	float CameraViewTarget = CameraViewFar * 0.53f;
	float WidthFar = 1190.0f;
	float WidthNear = 550.0f;
	float p[4][3];
	p[0][0] = - WidthFar;
	p[0][1] = CameraViewFar - CameraViewTarget;
	p[0][2] = 0.0f;
	p[1][0] = WidthFar;
	p[1][1] = CameraViewFar - CameraViewTarget;
	p[1][2] = 0.0f;
	p[2][0] = WidthNear;
	p[2][1] = CameraViewNear - CameraViewTarget;
	p[2][2] = 0.0f;
	p[3][0] = - WidthNear;
	p[3][1] = CameraViewNear - CameraViewTarget;
	p[3][2] = 0.0f;
	float Angle[3];
	Angle[0] = 0.0f;
	Angle[1] = 0.0f;
	Angle[2] = 45.0f;
	float Matrix[3][4];
	AngleMatrix(&Angle[0], &Matrix[0]);
	for(int i = 0; i < 4; ++i)
	{
		VectorRotateSSE(&p[i][0], &Matrix[0], &Frustum[i][0]);
		FrustumX[i] = (int)(Frustum[i][0] * 0.01f);
		FrustumY[i] = (int)(Frustum[i][1] * 0.01f);
	}
}