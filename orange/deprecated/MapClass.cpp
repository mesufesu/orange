#include "stdafx.h"
#include <stdio.h>
#include ".\\MapClass.h"

MapClass MapC[MAX_MAPS];

extern char MapAttrName[MAX_MAPS][15] = 
{
	"terrain1.att",
	"terrain2.att",
	"terrain3.att",
	"terrain4.att",
	"terrain5.att",
	"terrain6.att",
	"terrain7.att",
	"terrain8.att",
	"terrain9.att",
	"terrain10.att",
	"terrain11.att",
	"terrain12.att",
	"terrain12.att",
	"terrain12.att",
	"terrain12.att",
	"terrain12.att",
	"terrain12.att",
	"terrain12.att",
	"terrain19.att",
	"terrain19.att",
	"terrain19.att",
	"terrain19.att",
	"terrain19.att",
	"terrain19.att",
	"terrain25.att",
	"terrain25.att",
	"terrain25.att",
	"terrain25.att",
	"terrain25.att",
	"terrain25.att",
	"terrain31.att",
	"terrain32.att",
	"terrain33.att",
	"terrain34.att",
	"terrain35.att",
	"terrain36.att",
	"terrain37.att",
	"terrain38.att",
	"terrain39.att",
	"terrain40.att",
	"terrain41.att",
	"terrain42.att",
	"terrain43.att",
	"terrain44.att",
	"terrain45.att",
	"terrain46.att",
	"terrain47.att",
	"terrain48.att",
	"terrain49.att",
	"terrain50.att",
	"terrain51.att",
	"terrain52.att",
	"terrain53.att",
	"terrain54.att",
	"terrain55.att",
	"terrain56.att",
	"terrain57.att",
	"terrain58.att",
	"terrain59.att",
	"terrain60.att",
};

int MapNumberCheck(int map)
{
	if((map <= (MAX_MAPS - 1)) && (map >= 0))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void MapClass::init()
{
	this->m_attrbuf = 0;
	PATH* Path = new PATH;
	this->path = Path;
	this->m_width = 0;
	this->m_height = 0;
}

void MapClass::free()
{
	if(this->m_attrbuf)
	{
		GlobalFree(this->m_attrbuf);
		this->m_attrbuf = 0;
	}
	if(this->path)
	{
		delete this->path;
		this->path = 0;
	}
}

MapClass::MapClass()
{
	this->m_Weather = 0;
	this->m_WeatherTimer = GetTickCount();
	this->m_NextWeatherTimer = rand() % 10000 + 10000;
	this->init();
	SetRect((LPRECT)&(this->gRegenRect[MAP_INDEX_LORENCIA]), 130, 116, 151, 137);
	SetRect((LPRECT)&(this->gRegenRect[MAP_INDEX_DUNGEON]), 106, 236, 112, 243);
	SetRect((LPRECT)&(this->gRegenRect[MAP_INDEX_DEVIAS]), 197, 35, 218, 50);
	SetRect((LPRECT)&(this->gRegenRect[MAP_INDEX_NORIA]), 174, 101, 187, 125);
	SetRect((LPRECT)&(this->gRegenRect[MAP_INDEX_LOSTTOWER]), 201, 70, 213, 81);
	SetRect((LPRECT)&(this->gRegenRect[MAP_INDEX_RESERVED]), 89, 135, 90, 136);
	SetRect((LPRECT)&(this->gRegenRect[MAP_INDEX_BATTLESOCCER]), 89, 135, 90, 136);
	SetRect((LPRECT)&(this->gRegenRect[MAP_INDEX_ATHLANSE]), 14, 11, 27, 23);
	SetRect((LPRECT)&(this->gRegenRect[MAP_INDEX_TARKAN]), 184, 54, 203, 69);
	SetRect((LPRECT)&(this->gRegenRect[MAP_INDEX_AIDA]), 82, 8, 87, 14);
	SetRect((LPRECT)&(this->gRegenRect[MAP_INDEX_CRYWOLF_FIRSTZONE]), 133, 41, 140, 44);
	this->m_ItemCount = 0;
}

void MapClass::ItemInit()
{
}

void MapClass::LoadMapAttr(char* filename, int MapNumber)
{
	if(!this->AttrLoad(filename))
	{
		MessageBox(0, "LoadMapAttr failed", "Fatal error", MB_OK | MB_ICONSTOP);
	}
	this->thisMapNumber = MapNumber;
}

int MapClass::AttrLoad(char* filename)
{
	FILE* fp;
	unsigned char head;
	fopen_s(&fp, filename, "rb");
	if(fp)
	{
		fread(&head, 1, 1, fp);
		fread(&(this->m_width), 1, 1, fp);
		fread(&(this->m_height), 1, 1, fp);
		if(this->m_width <= 255 && this->m_height <= 255)
		{
			if(this->m_attrbuf)
			{
				GlobalFree(this->m_attrbuf);
				this->m_attrbuf = 0;
			}
			this->m_attrbuf = (unsigned char*)GlobalAlloc(GMEM_ZEROINIT, 0x10000);
			fread(this->m_attrbuf, 0x100, 0x100, fp);
			fclose(fp);
			this->path->SetMapDimensions(256, 256, this->m_attrbuf);
			return TRUE;
		}
		else
		{
			MessageBox(0, "AttrLoad failed", "Fatal error", MB_OK | MB_ICONSTOP);
			fclose(fp);
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

unsigned char MapClass::GetAttr(int x, int y)
{
	if((x >= 0) && (y >= 0) && (x < this->m_width) &&(y < this->m_height))
	{
		return (*(this->m_attrbuf + x + (y * 256)));
	}
	else
	{
		return 0x04;
	}
}

MapClass::~MapClass()
{
	this->free();
}