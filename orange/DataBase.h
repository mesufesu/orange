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

#include <QtCore/QReadWriteLock>
#include <QtSql/QtSql>

class CDatabaseHandler
{
public:
	QSqlDatabase db;

	void LockForRead();
	void LockForWrite();
	void Unlock();
	CDatabaseHandler();
	~CDatabaseHandler();
	/*bool Connect();*/
protected:
	QReadWriteLock rwl;
};

class CDataDB : public CDatabaseHandler
{
public:
	bool Connect();
};

class CAccountsDB : public CDatabaseHandler
{
public:
	bool Connect();
};

extern CDataDB data_db;
extern CAccountsDB accounts_db;

#endif