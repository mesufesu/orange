#ifndef _UNIT_H_
#define _UNIT_H_

#include ".\\object.h"
#include ".\\SimpleAI.h"

class CUnit : public CObject
{
public:
	uint32 templ;
	uint32 view_range;
	CSimpleAI * ai;
	CUnit();
	~CUnit();
	bool SetUnit(uint32 _type, uint8 _map, uint8 _x, uint8 _y, uint8 tx, uint8 ty, uint8 ustate);
private:
};

#endif