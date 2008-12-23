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