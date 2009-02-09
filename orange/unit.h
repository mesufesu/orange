#ifndef _UNIT_H_
#define _UNIT_H_

#include ".\\object.h"

class CUnit : public CObject
{
public:
	uint32 templ;
	CUnit();
	bool SetUnit(uint32 _type, uint8 _map, uint8 _x, uint8 _y);
private:
};

#endif