#ifndef MUTEX_H_
#define MUTEX_H_
#include <windows.h>

typedef class CMyMutex
{
public:
	bool Lock();
	bool Unlock();
	CMyMutex();
	~CMyMutex();
private:
	HANDLE hMutex;
} MUTEX, *PMUTEX;

#endif