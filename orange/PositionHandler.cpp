#include "stdafx.h"
#include ".\\WorldMap.h"
#include ".\\PositionHandler.h"

CPositionHandler::CPositionHandler()
{
	this->path.clear();
	this->path.reserve(16);
	this->cache.clear();
	this->cache.reserve(16);
}

CPositionHandler::~CPositionHandler()
{
	this->path.clear();
	this->cache.clear();
}

bool CPositionHandler::HandleMovement(uint8 x, uint8 y, uint8 *pPath, uint32 map)
{
	std::vector<uint8> nodes;
	uint32 count = pPath[0] & 0x0f;
	for(int32 i = 1; i < 8; ++i) /* calculating roadpath nodes */
	{
		if(nodes.size() < count)
		{
			nodes.push_back((pPath[i] & 0xf0) / 0x10);
		}
		if(nodes.size() < count)
		{
			nodes.push_back(pPath[i] & 0x0f);
		}
	}
	assert(nodes.size() == count);
	std::vector<CPositionHandler::MovePoint> new_path;
	new_path.reserve(count + 1); /* reserve space immediately, it must be faster i think */
	MovePoint origin;
	origin.x = x;
	origin.y = y;
	origin.time = GetTicks();
	new_path.push_back(origin);
	uint8 tx = x;
	uint8 ty = y;
	for(uint32 i = 0; i < nodes.size(); ++i) /* building path from client data and checking it for walkability */
	{
		tx += RoadX[nodes.at(i)];
		ty += RoadY[nodes.at(i)];
		if(!WorldMap[map].FreeToMove(tx, ty))
		{
			return false;
		}
		MovePoint pt;
		pt.time = origin.time + 300 * (i + 1); /* time is constant (reversed speed), need calculate it later */
		pt.x = tx;
		pt.y = ty;
		new_path.push_back(pt);
	}
	this->mtx.lock(); /* applying new path, also storing backup of previous */
	this->cache = this->path;
	this->path = new_path;
	this->mtx.unlock();
	return true;
}

const CPositionHandler::MovePoint CPositionHandler::GetPosition()
{
	uint32 current_time = GetTicks();
	CPositionHandler::MovePoint pt;
	this->mtx.lock();
	for(uint32 i = 0; i < this->path.size(); ++i)
	{
		if(this->path.at(i).time > current_time)
		{
			pt = this->path.at(i - 1);
			this->mtx.unlock();
			return pt;
		}
	}
	pt = this->path.at(this->path.size() - 1);
	this->mtx.unlock();
	return pt;
}

const CPositionHandler::MovePoint CPositionHandler::GetDestination()
{
	CPositionHandler::MovePoint pt;
	this->mtx.lock();
	pt = this->path.at(this->path.size() - 1);
	this->mtx.unlock();
	return pt;
}

void CPositionHandler::SetPosition(uint8 x, uint8 y)
{
	this->mtx.lock();
	this->path.clear();
	this->cache.clear();
	CPositionHandler::MovePoint pt;
	pt.time = GetTicks();
	pt.x = x;
	pt.y = y;
	this->path.push_back(pt);
	this->cache.push_back(pt);
	this->mtx.unlock();
}

bool CPositionHandler::CheckPacketPosition(uint8 x, uint8 y)
{
	CPositionHandler::MovePoint pt = this->GetPosition();
	if((abs(x - pt.x) <= 2) && (abs(y - pt.y) <= 2))
	{
		return true;
	}
	return false;
}