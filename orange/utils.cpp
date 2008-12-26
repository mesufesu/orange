#include "stdafx.h"
#include ".\\utils.h"

short RoadPathTable[16] = {-1, -1, 0, -1, 1, -1, 1, 0, 1, 1, 0, 1, -1, 1, -1, 0};

/*		[0]	-1	short
		[1]	-1	short
		[2]	0	short
		[3]	-1	short
		[4]	1	short
		[5]	-1	short
		[6]	1	short
		[7]	0	short
		[8]	1	short
		[9]	1	short
		[10]	0	short
		[11]	1	short
		[12]	-1	short
		[13]	1	short
		[14]	-1	short
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
