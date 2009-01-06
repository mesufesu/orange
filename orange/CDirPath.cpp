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