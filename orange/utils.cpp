#include "stdafx.h"
#include ".\\utils.h"

int8 RoadX[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
int8 RoadY[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
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
