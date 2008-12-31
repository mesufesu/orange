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

const std::string AssembleQuery(const char *format, ...)
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