#ifndef _POSITION_HANDLER_H_
#define _POSITION_HANDLER_H_

#include <QtCore/QMutex>

struct MovePoint
{
	uint32 time;
	uint8 x;
	uint8 y;
};

class CPositionHandler
{
public:
	struct MovePoint
	{
		uint32 time;
		uint8 x;
		uint8 y;
	};
	CPositionHandler();
	~CPositionHandler();
	void SetPosition(uint8 x, uint8 y);
	bool CheckPacketPosition(uint8 x, uint8 y);
	bool HandleMovement(uint8 x, uint8 y, uint8* pPath, uint32 map);
	const CPositionHandler::MovePoint GetPosition();
	const CPositionHandler::MovePoint GetDestination();
private:
	QMutex mtx;
	std::vector<MovePoint> path;
	std::vector<MovePoint> cache;
};

#endif