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
#include <math.h>
#include ".\\utils.h"
#include ".\\mathlib.h"

uint64 levelexp[401];

int8 RoadX[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
int8 RoadY[8] = {-1, -1, -1, 0, 1, 1, 1, 0};

int32 FrustumX[4];
int32 FrustumY[4];

float rad1;
float rad2;
float t1;
float t2;

short RoadPathTable[16] = {-1, -1, 0, -1, 1, -1, 1, 0, 1, 1, 0, 1, -1, 1, -1, 0};

/*		[0]	-1	shortx
		[1]	-1	short
		[2]	0	shortx
		[3]	-1	short
		[4]	1	shortx
		[5]	-1	short
		[6]	1	shortx
		[7]	0	short
		[8]	1	shortx
		[9]	1	short
		[10]	0	shortx
		[11]	1	short
		[12]	-1	shortx
		[13]	1	short
		[14]	-1	shortx
		[15]	0	short*/

bool isFile(const char* filename)
{
	FILE* file;
	fopen_s(&file, filename, "rb");
	if(file)
	{
		fclose(file);
		return true;
	}
	else
	{
		return false;
	}
}

void MsgBox(const char* str)
{
	MessageBox(NULL, str, "Error", MB_OK | MB_ICONSTOP);
}

const static unsigned char xor_table_3byte[3] = {0xFC, 0xCF, 0xAB};

void xor3(unsigned char* ptr, unsigned int len)
{
	for(unsigned int i = 0; i < len; ++i)
	{
		ptr[i] ^= xor_table_3byte[i%3];
	}
}

const std::string Query(const char *format, ...)
{
	va_list pArgs;
	va_start(pArgs, format); 
	int ret =_vscprintf( format, pArgs ) + 1;
	char * buf = new char[ret];
	ZeroMemory(buf, ret);
	vsprintf_s(buf, ret, format, pArgs);
	va_end(pArgs);
	std::string result = buf;
	delete [] buf;
	return result;
}

unsigned char LevelConvert(unsigned char level)
{
	if(level > 13)
	{
		level = 13;
	}
	switch(level)
	{
	case 13:
		return 7;
	case 12:
		return 6;
	case 11:
		return 5;
	case 10:
	case 9:
		return 4;
	case 8:
	case 7:
		return 3;
	case 6:
	case 5:
		return 2;
	case 4:
	case 3:
		return 1;
	default:
		return 0;
	}
}

uint8 GetCategory(uint16 type)
{
	return (type / 512);
}

void GenerateExp()
{
	for(uint64 i = 0; i < 401; ++i)
	{
		levelexp[i] = 10 * i * i * (i + 9);
		if(i > 255)
		{
			levelexp[i] += (i - 255) * (i - 255) * (i - 255 + 9);
		}
	}
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

void MakeFrustum()
{
	rad1 = 1.0f + sqrt(34.0f * 34.0f + 18.0f * 18.0f);
	rad2 = -1.0f + sqrt(17.0f * 17.0f + 9.0f * 9.0f);
	t1 = 3.0f + (atan((-1.0f) * (9.0f / 17.0f)) * 180.0f) / (float)Q_PI;
	t2 = -3.0f + (atan((-1.0f) * (17.0f / 9.0f)) * 180.0f) / (float)Q_PI;
}

bool InViewport(uint8 type, int32 ox, int32 oy, int32 tx, int32 ty, uint32 view_range)
{
	switch(type)
	{
	case 2:
		{
			float ntx = (float)(tx - ox);
			float nty = (float)(ty - oy);
			float rx = 18.0f + abs(ntx);
			float ry = 18.0f + abs(nty);
			float radius = sqrt(rx*rx + ry*ry);
			if((radius > rad1) || (radius < rad2))
			{
				return false;
			}
			float val = ((-18.0f - nty) / (18.0f - ntx));
			float deg = (atan(val) * 180.0f) / (float)Q_PI;
			if((deg > t1) || (deg < t2))
			{
				return false;
			}
			return true;
			break;
		}
	case 1:
		{
			float nx = (float)(tx - ox);
			float ny = (float)(ty - oy);
			float radius = sqrt(nx*nx + ny*ny);
			if(radius > (float)view_range)
			{
				return false;
			}
			return true;
			break;
		}
	case 3:
		{
			float nx = (float)(tx - ox);
			float ny = (float)(ty - oy);
			float radius = sqrt(nx*nx + ny*ny);
			if(radius > 15.0f)
			{
				return false;
			}
			return true;
			break;
		}
	default:
		{
			return false;
			break;
		}
	}
}

uint32 GetDistance(uint32 ox, uint32 oy, uint32 tx, uint32 ty)
{
	uint32 nx = abs((int)(ox - tx));
	uint32 ny = abs((int)(oy - ty));
	return (uint32)sqrt((float)(nx*nx) + (float)(ny*ny));
}