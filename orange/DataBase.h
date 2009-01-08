/*
	Copyright 2008-2009 Ambient.5

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include ".\\mutex.h"
#include <QtSql\\QtSql>
/*#include "..\\mysql\\mysql.h"
#include "..\\mysqlwrapper\\Database.h"
#include "..\\mysqlwrapper\\Query.h"*/

class CDatabaseHandler
{
public:
	void Lock();
	void Unlock();
	CDatabaseHandler();
	~CDatabaseHandler();
	bool Connect();
private:
	CMyMutex db_mutex;
	QSqlDatabase db;
};

extern CDatabaseHandler MainDB;

#endif