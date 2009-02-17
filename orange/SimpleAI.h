#ifndef _SIMPLE_AI_H_
#define _SIMPLE_AI_H_

#include ".\\object.h"

enum AIEventPriority
{
	LOW = 0,
	NORMAL = 1,
	HIGH = 2,
};

struct ThreatElement
{
	uint32 guid;
	uint32 amount;
};

class CSimpleAI
{
public:
	CSimpleAI(CObject* obj);
	~CSimpleAI();
	void Think();
	void AddThreat(uint32 guid, uint32 amount);
protected:
	CObject* owner;
	CObject* target;
	void ProcessThreatList();
	virtual void DecideAction();
	virtual bool IsHostile(CObject* obj);
	std::vector<ThreatElement> threat_list;
private:
	uint32 last_think_time;
};

#endif