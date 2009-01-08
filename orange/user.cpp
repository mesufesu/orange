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

/*void Test()
{
	/*
	0 0
	1 WEAPON_01 (third digit) 1 WEAPON_01 (fourth digit)
	2 WEAPON_02 (third digit) 2 WEAPON_02 (fourth digit)
	3 HELMET (fourth digit) 3 ARMOR (fourth digit)
	4 PANTS (fourth digit) 4 GLOVES (fourth digit)
	5 BOOTS (fourth digit) 5 WINGS & GUARDIAN
	6 6 levelindex HIGHWORD
	7 7 levelindex HIBYTE
	8 8 levelindex LOBYTE
	9 HELMET (used on magumsa = 0x80) & ARMOR (=0x40) & PANTS (=0x20) & GLOVES (=0x10) 9 BOOTS (=0x08) & 2nd WINGS
	10 10
	11 11
	12 WEAPON_01 (second digit) 12
	13 WEAPON_02 (second digit) 13 HELMET (third digit / 2)
	14 ARMOR (third digit / 2) 14 PANTS (third digit / 2)
	15 GLOVES (third digit / 2) 15 BOOTS (third digit / 2)
	16 16
	17 17*/
	/*OBJECTSTRUCT* lpObj = &gObj[1];
	lpObj->CharSet[0] = (lpObj->Class * 0x20) & 0xE0; //0x100 - 0x20 = 0xE0
	lpObj->CharSet[0] |= (lpObj->CharSet * 0x10) & 0x10;
	if(lpObj->m_ActionNumber == 0x80)
	{
		lpObj->CharSet[0] |= 0x02;
	}
	else if(lpObj->m_ActionNumber == 0x81)
	{
		lpObj->CharSet[0] |= 0x03;
	}
	if(lpObj->Inventory1[WEAPON_01].m_Type >= 0)
	{
		lpObj->CharSet[12] |= (lpObj->Inventory1[WEAPON_01].m_Type & 0x0f00) / 0x10;  //12 char - highest 4 bits
		lpObj->CharSet[1] = (lpObj->Inventory1[WEAPON_01].m_Type & 0xff); //1 char both 4-bit fields
	}
	else //or -1;
	{
		lpObj->CharSet[12] |= 0xf0;
		lpObj->CharSet[1] = 0xff;
	}
	if(lpObj->Inventory1[WEAPON_02].m_Type >= 0)
	{
		lpObj->CharSet[13] |= (lpObj->Inventory1[WEAPON_2].m_Type & 0x0f00) / 0x10;
		lpObj->CharSet[2] = (lpObj->Inventory1[WEAPON_02].m_Type & 0xff);
	}
	else
	{
		lpObj->CharSet[13] |= 0xf0;
		lpObj->CharSet[2] = 0xff;
	}
	if(lpObj->Inventory1[HELMET].m_Type >= 0)
	{
		lpObj->CharSet[13] |= (lpObj->Inventory1[HELMET].m_Type & 0x01E0) / 0x20;
		lpObj->CharSet[9] |= (lpObj->Inventory1[HELMET].m_Type & 0x10) * 0x08;
		lpObj->CharSet[3] |= (lpObj->Inventory1[HELMET].m_Type & 0x0f) * 0x10;
	}
	else
	{
		lpObj->CharSet[13] |= 0x0f;
		lpObj->CharSet[9] |= 0x80;
		lpObj->CharSet[3] |= 0xf0;
	}
	if(lpObj->Inventory1[ARMOR].m_Type >= 0)
	{
		lpObj->CharSet[14] |= (lpObj->Inventory1[ARMOR].m_Type & 0x01E0) / 0x02;
		lpObj->CharSet[9] |= (lpObj->Inventory1[ARMOR].m_Type & 0x10) * 0x04;
		lpObj->CharSet[3] |= (lpObj->Inventory1[ARMOR].m_Type &0x0f);
	}
	else
	{
		lpObj->CharSet[14] |= 0xf0;
		lpObj->CharSet[9] |= 0x40;
		lpObj->CharSet[3] |= 0x0f;
	}
	if(lpObj->Inventory1[PANTS].m_Type >= 0)
	{
		lpObj->CharSet[14] |= (lpObj->Inventory1[PANTS].m_Type & 0x01E0) / 0x20;
		lpObj->CharSet[9] |= (lpObj->Inventory1[PANTS].m_Type & 0x10) * 0x02;
		lpObj->CharSet[4] |= (lpObj->Inventory1[PANTS].m_Type & 0x0f) * 0x10;
	}
	else
	{
		lpObj->CharSet[14] |= 0x0f;
		lpObj->CharSet[9] |= 0x20;
		lpObj->CharSet[4] |= 0xf0;
	}
	if(lpObj->Inventory1[GLOVES].m_Type >= 0)
	{
		lpObj->CharSet[15] |= (lpObj->Inventory1[GLOVES].m_Type & 0x01E0) / 0x02;
		lpObj->CharSet[9] |= (lpObj->Inventory1[GLOVES].m_Type & 0x10);
		lpObj->CharSet[4] |= (lpObj->Inventory1[GLOVES].m_Type & 0x0f);
	}
	else
	{
		lpObj->CharSet[15] |= 0xf0;
		lpObj->CharSet[9] |= 0x10;
		lpObj->CharSet[4] |= 0x0f;
	}
	if(lpObj->Inventory1[BOOTS].m_Type >= 0)
	{
		lpObj->CharSet[15] |= (lpObj->Inventory1[BOOTS].m_Type & 0x01E0) / 0x20;
		lpObj->CharSet[9] |= (lpObj->Inventory1[BOOTS].m_Type & 0x10) / 0x02;
		lpObj->CharSet[5] |= (lpObj->Inventory1[BOOTS].m_Type & 0x0f) * 0x10;
	}
	else
	{
		lpObj->CharSet[15] |= 0x0f;
		lpObj->CharSet[9] |= 0x08;
		lpObj->CharSet[5] |= 0xf0;
	}
	uint8 index = 0;
	if(lpObj->Inventory1[WINGS].m_Type >= 0)
	{
		index |= (lpObj->Inventory1[WINGS].m_Type & 0x03) * 0x04;
	}
	else
	{
		index |= 0x0c;
	}
	if((lpObj->Inventory1[GUARDIAN].m_Type >= 0) && !(lpObj->Inventory1[GUARDIAN].m_Type == 6660))
	{
		index |= (lpObj->Inventory1[GUARDIAN].m_Type & 0x03);
	}
	else
	{
		index |= 0x03;
	}
	lpObj->CharSet[5] |= index;
	uint32 levelindex = 0;
	levelindex = lsc(0) & 0xff;
	levelindex |= (LevelConvert(1) & 0xff) * 0x08;
	levelindex |= (LevelConvert(2) & 0xff) * 0x40;
	levelindex |= (LevelConvert(3) & 0xff) * 0x200;
	levelindex |= (LevelConvert(4) & 0xff) * 0x1000;
	levelindex |= (LevelConvert(5) & 0xff) * 0x8000;
	levelindex |= (LevelConvert(6) & 0xff) * 0x40000;
	lpObj->CharSet[6] = (levelindex / 0x10000) & 0xff;
	lpObj->CharSet[7] = (levelindex / 0x100) & 0xff;
	lpObj->CharSet[8] = (levelindex) & 0xff;
	if(((lpObj->Inventory1[WINGS].m_Type >= (12 * 512 + 3)) && (lpObj->Inventory1[WINGS].m_Type <= (12 * 512 + 6))) || (lpObj->Inventory1[WINGS].m_Type == (13 * 512 + 30)))
	{
		lpObj->CharSet[5] |= 0x0C;
		if(lpObj->Inventory1[WINGS].m_Type == (13 * 512 + 30))
		{
			lpObj->CharSet[5] |= 0x05;
		}
		else
		{
			lpObj->CharSet[9] |= (lpObj->Inventory1[WINGS].m_Type - 2) & 0x07;
		}
	}
	lpObj->CharSet[10] = 0;
	if(lpObj->pInventory[HELMET].IsExtItem())
	{
		lpObj->CharSet[10] = 0x80;
	}
	if(lpObj->pInventory[ARMOR].IsExtItem())
	{
		lpObj->CharSet[10] |= 0x40;
	}
	if(lpObj->pInventory[PANTS].IsExtItem())
	{
		lpObj->CharSet[10] |= 0x20;
	}
	if(lpObj->pInventory[GLOVES].IsExtItem())
	{
		lpObj->CharSet[10] |= 0x10;
	}
	if(lpObj->pInventory[BOOTS].IsExtItem())
	{
		lpObj->CharSet[10] |= 0x8;
	}
	if(lpObj->pInventory[WEAPON_01].IsExtItem())
	{
		lpObj->CharSet[10] |= 0x4;
	}
	if(lpObj->pInventory[WEAPON_02].IsExtItem())
	{
		lpObj->CharSet[10] |= 0x2;
	}
	lpObj->CharSet[11] = 0;
	if(lpObj->pInventory[HELMET].IsSetItem())
	{
		lpObj->CharSet[11] = 0x80;
	}
	if(lpObj->pInventory[ARMOR].IsSetItem())
	{
		lpObj->CharSet[11] |= 0x40;
	}
	if(lpObj->pInventory[PANTS].IsSetItem())
	{
		lpObj->CharSet[11] |= 0x20;
	}
	if(lpObj->pInventory[GLOVES].IsSetItem())
	{
		lpObj->CharSet[11] |= 0x10;
	}
	if(lpObj->pInventory[BOOTS].IsSetItem())
	{
		lpObj->CharSet[11] |= 0x8;
	}
	if(lpObj->pInventory[WEAPON_01].IsSetItem())
	{
		lpObj->CharSet[11] |= 0x4;
	}
	if(lpObj->pInventory[WEAPON_02].IsSetItem())
	{
		lpObj->CharSet[11] |= 0x2;
	}
	if(lpObj->IsFullSetItem)
	{
		lpObj->CharSet[11] |= 0x01;
	}
	//lpObj->Inventory1[GUARDIAN].m_Type & 0x03;
	//too lazy
}*/