#include "stdafx.h"
#include ".\\CBattleGround.h"

CBattleGround::CBattleGround()
{
	this->m_Used = false;
	this->m_Set = FALSE;
	ZeroMemory(&this->m_szID1, sizeof(this->m_szID1));
	ZeroMemory(&this->m_szID2, sizeof(this->m_szID2));
	ZeroMemory(&this->m_szTeamName1, sizeof(this->m_szTeamName1));
	ZeroMemory(&this->m_szTeamName2, sizeof(this->m_szTeamName2));
}

CBattleGround::~CBattleGround()
{
}

void CBattleGround::SetGroundRect(int map, int x, int y, int xl, int yl)
{
	this->m_MapNumber = map;
	this->m_rect.left = x;
	this->m_rect.top = y;
	this->m_rect.right = xl;
	this->m_rect.bottom = yl;
	this->m_Set = TRUE;
}

void CBattleGround::SetBattleType(int type)
{
	this->m_Type = type;
}

bool CBattleGround::GetUsed()
{
	return (this->m_Used);
}

void CBattleGround::Enable(bool enable)
{
	this->m_Used = enable;
	if(this->m_Used == true)
	{
		this->m_Score1 = 0;
		this->m_Score2 = 0;
	}
}

void CBattleGround::SetTeamMaster(int n, char *szId)
{
	if(n)
	{
		strcpy_s(this->m_szID2, sizeof(this->m_szID2), szId);
	}
	else
	{
		strcpy_s(this->m_szID1, sizeof(this->m_szID1), szId);
	}
}

void CBattleGround::SetTeamName(int n, char *szId)
{
	if(n)
	{
		strcpy_s(this->m_szTeamName2, sizeof(this->m_szTeamName2), szId);
	}
	else
	{
		strcpy_s(this->m_szTeamName1, sizeof(this->m_szTeamName1), szId);
	}
}

char* CBattleGround::GetTeamName(int n)
{
	if(n)
	{
		return this->m_szTeamName2;
	}
	else
	{
		return this->m_szTeamName1;
	}
}

int CBattleGround::GetScore(int team)
{
	if(team)
	{
		return this->m_Score2;
	}
	else
	{
		return this->m_Score1;
	}
}

void CBattleGround::SetScore(int team, int score)
{
	if(team)
	{
		this->m_Score2 = score;
	}
	else
	{
		this->m_Score1 = score;
	}
}

void CBattleGround::SetTimer(int g_time)
{
	this->m_nTimer = g_time;
	this->m_dwCurTimer = GetTickCount();
}

int CBattleGround::GetTimer()
{
	return ((GetTickCount() - this->m_dwCurTimer) / 1000);
}