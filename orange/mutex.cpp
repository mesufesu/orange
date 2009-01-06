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
#include "mutex.h"

CMyMutex::CMyMutex()
{
	this->hMutex = CreateMutex(NULL, FALSE, NULL);
}

bool CMyMutex::Lock()
{
	//DWORD dwWaitResult; 
	while(TRUE)
	{
		/*dwWaitResult = WaitForSingleObject(this->hMutex, INFINITE);
		switch(dwWaitResult)*/
		switch(WaitForSingleObject(this->hMutex, INFINITE))
		{
		case WAIT_OBJECT_0:
			{
				//printf_s("Taken control of mutex.\n");
				return true;
			}
		case WAIT_ABANDONED:
			{
				//printf_s("Abandoned mutex.\n");
				return false; 
			}
		case WAIT_TIMEOUT:
			{
				//printf_s("Mutex timed out.\n");
				return false;
			}
		}
	}
	return true; 
}

bool CMyMutex::Unlock()
{
	if(!ReleaseMutex(this->hMutex)) 
	{
		return false;
	}
	//printf_s("Mutex released.\n");
	return true;
}

CMyMutex::~CMyMutex()
{
	CloseHandle(this->hMutex);
}