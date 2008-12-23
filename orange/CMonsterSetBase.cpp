#include "stdafx.h"
#include ".\\user.h"
#include ".\\deprecated\\MapClass.h"
#include ".\\CMonsterSetBase.h"

CMonsterSetBase gMSetBase;

CMonsterSetBase::CMonsterSetBase()
{
}

CMonsterSetBase::~CMonsterSetBase()
{
}

void CMonsterSetBase::LoadSetBase(char* filename)
{
}

void CMonsterSetBase::SetBoxPosition(int TableNum, int mapnumber, int ax, int ay, int aw, int ah)
{
	this->m_Mp[TableNum].m_MapNumber = mapnumber;
	this->m_Mp[TableNum].m_W = aw;
	this->m_Mp[TableNum].m_H = ah;
	this->m_Mp[TableNum].m_X = ax;
	this->m_Mp[TableNum].m_Y = ay;
}

bool CMonsterSetBase::GetBoxPosition(int mapnumber, int ax, int ay, int aw, int ah, short &mx, short &my)
{
	int w, h, tx, ty;
	int count = 100;
	while(TRUE)
	{
		count--;
		if(count == 0)
		{
			break;
		}
		w = aw - ax;
		h = ah - ay;
		tx = rand() % w + ax;
		ty = rand() % h + ay;
		unsigned char attr = MapC[mapnumber].GetAttr(tx, ty);
		if(!(attr & 1) && !(attr & 4) && !(attr & 8))
		{
			mx = tx;
			my = ty;
			return true;
		}
	}
	return false;
}

bool CMonsterSetBase::GetPosition(int TableNum, short MapNumber, short &x, short &y)
{
	if(TableNum < 0 || TableNum > (OBJ_MONSTER_MAX - 1))
	{
		/*((int (*)(const char *, ...))LogAdd)(
      "ERROR : %s %d",
      "D:\\Works\\Mu-Studio\\GameServer_Backup\\1.00.18_¦+¬-¦+¦¦L?¬?L?_L+L?L¬-",
      __LINE__Var + 8,
      ST0C_4_0,
      ST10_4_0)*/
		return false;
	}
	switch(this->m_Mp[TableNum].m_ArrangeType)
	{
	case STAND:
		{
			x = this->m_Mp[TableNum].m_X;
			y = this->m_Mp[TableNum].m_Y;
			return true;
		}
	case DEVIL_SQUARE:
		{
			int count = 100;
			while(TRUE)
			{
				count--;
				if(count == 0)
				{
					break;
				}
				int w = this->m_Mp[TableNum].m_W - this->m_Mp[TableNum].m_X;
				int h = this->m_Mp[TableNum].m_H - this->m_Mp[TableNum].m_Y;
				int tx = (w <= 0 ? 1 : w) + this->m_Mp[TableNum].m_X;
				int ty = (h <= 0 ? 1 : h) + this->m_Mp[TableNum].m_Y;
				unsigned char attr = MapC[MapNumber].GetAttr(tx, ty);
				if(!(attr & 1) && !(attr & 4) && !(attr & 8))
				{
					x = tx;
					y = ty;
					return true;
				}
			}
			break;
		}
	case GENERAL:
		{
			int count = 100;
			while(TRUE)
			{
				count--;
				if(count == 0)
				{
					break;
				}
				int tx = this->m_Mp[TableNum].m_X - 3 + rand() % 7;
				int ty = this->m_Mp[TableNum].m_Y - 3 + rand() & 7;
				unsigned char attr = MapC[MapNumber].GetAttr(tx, ty);
				if(!(attr & 1) && !(attr & 4) && !(attr & 8))
				{
					x = tx;
					y = ty;
					return true;
				}
			}
			break;
		}
	case EVENT:
		{
			return true;
		}
	case BLOOD_CASTLE:
		{
			x = this->m_Mp[TableNum].m_X;
			y = this->m_Mp[TableNum].m_Y;
			return true;
		}
	default:
		{
			return false;
		}
	}
	return false;
}

short gObjAddMonster()
{
	/*//TODO: CheckMapCanMove
	int totalcount = 0;
	int count = gObjMonCount;
	while(gObj[count].Connected)
	{
		count++;
		if(count >= OBJ_MONSTER_MAX)
		{
			count = 0;
		}
		totalcount++;
		if(totalcount >= OBJ_MONSTER_MAX)
		{
			printf_s("Monster overflow\n");
			return -1;
		}
		//gObjCharZeroSet(count);
		gObj[count].m_Index = count;
		//gObj[count].
	}*/
	return 0;
}