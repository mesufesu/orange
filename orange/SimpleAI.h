#ifndef _SIMPLE_AI_H_
#define _SIMPLE_AI_H_

#include ".\\object.h"

enum AIEventType
{
	ATTACKED = 0,
};

enum AIEventPriority
{
	LOW = 0,
	NORMAL = 1,
	HIGH = 2,
};

struct AIEvent
{
	AIEventType ev;
	AIEventPriority prio;
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
	void Think();
	void AddAIEvent(AIEvent _event);
	void SetOwner(CObject* owner);
	void AddThreat(uint32 guid, uint32 amount);
private:
	CObject* owner;
	CObject* target;
	void ProcessAIEvent(AIEvent _event);
	void ProcessThreatList();
	void PerformMovementToTarget();
	uint32 last_think_time;
	std::vector<ThreatElement> threat_list;
	std::vector<AIEvent> events;
};

#endif