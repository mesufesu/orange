#include "stdafx.h"
#include <string.h>
#include ".\\CDirPath.h"

CDirPath gDirPath;

CDirPath::CDirPath()
{
	ZeroMemory(this->m_path, sizeof(this->m_path));
	ZeroMemory(this->m_newpath, sizeof(this->m_newpath));
}

void CDirPath::SetFirstPath(char *dir_path)
{
	strcpy_s(this->m_path, sizeof(this->m_path), dir_path);
}

char* CDirPath::GetNewPath(char *npath)
{
	strcpy_s(this->m_newpath, sizeof(this->m_newpath), this->m_path);
	strcat_s(this->m_newpath, sizeof(this->m_newpath), npath);
	return this->m_newpath;
}

CDirPath::~CDirPath()
{
}