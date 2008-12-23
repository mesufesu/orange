#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include ".\\mutex.h"
#include "..\\mysql\\mysql.h"
#include "..\\mysqlwrapper\\Database.h"
#include "..\\mysqlwrapper\\Query.h"

class CDatabaseHandler
{
private:
	Database* db;
public:
	CMyMutex db_mutex;
	Query* query;
	CDatabaseHandler();
	~CDatabaseHandler();
	const std::string AssembleQuery(const char * format, ...);
};

extern CDatabaseHandler TestDB;

#endif