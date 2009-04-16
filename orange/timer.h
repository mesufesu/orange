#ifndef _TIMER_H_
#define _TIMER_H_

class CTimer
{
public:
	CTimer();
	CTimer(uint32 msec);

	bool Passed();
	void SetTimer(uint32 msec);
private:
	uint32 interval;
	uint32 time;
};

#endif