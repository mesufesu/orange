#ifndef _OBJECT_THREAD_H_
#define _OBJECT_THREAD_H_

#include <QtCore/QThread>
#include <QtCore/QReadWriteLock>
#include "objectmanager.h"
#include "WorldMap.h"

class CObjectThread : public QThread
{
	Q_OBJECT
public:
	void run();
	CObjectThread(pObjectManager manager, CWorldMap * maps);
	void Shutdown();
private:
	QReadWriteLock * rwl;
	pObjectManager mang;
	CWorldMap * map[MAX_MAPS];
	bool shutting_down;
};

extern CObjectThread ObjThread;

#endif