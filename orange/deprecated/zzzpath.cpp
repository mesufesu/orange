#include "stdafx.h"
#include ".\\zzzpath.h"

PATH::PATH()
{
	int dir[16];
	dir[0] = -1;
	dir[1] = -1;
	dir[2] = 0;
	dir[3] = -1;
	dir[4] = 1;
	dir[5] = -1;
	dir[6] = 1;
	dir[7] = 0;
	dir[8] = 1;
	dir[9] = 1;
	dir[10] = 0;
	dir[11] = 1;
	dir[12] = -1;
	dir[13] = 1;
	dir[14] = -1;
	dir[15] = 0;
	memcpy(&(this->Dir), &(dir), sizeof(int[16]));
}

void PATH::SetMapDimensions(int w, int h, unsigned char * map)
{
	this->Width = w;
	this->Height = h;
	this->Map = map;
	this->HitMap = new unsigned char[(this->Width) * (this->Height)];
}

PATH::~PATH()
{
}