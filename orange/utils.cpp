#include "stdafx.h"
#include ".\\utils.h"

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
