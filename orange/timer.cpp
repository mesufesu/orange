#include "stdafx.h"
#include "timer.h"

CTimer::CTimer()
{
	this->interval = 0;
	this->time = GetTicks();
}

CTimer::CTimer(uint32 msec)
{
	this->interval = msec;
	this->time = GetTicks();
}

bool CTimer::Passed()
{
	bool res = false;
	if(GetTickDiff(this->time) >= this->interval)
	{
		res = true;
		this->time = GetTicks();
	}
	return res;
}