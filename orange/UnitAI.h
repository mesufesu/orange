#ifndef _UNIT_AI_H_
#define _UNIT_AI_H_

#include "SimpleAI.h" 

class CUnitAI : public CSimpleAI
{
public:
	CUnitAI(CObject * owner);
	~CUnitAI();
private:
	void DecideAction();
	void PerformMovementToTarget();
	void PerformRandomMovement();
	void TryMoveTo(uint8 x, uint8 y);
};

#endif