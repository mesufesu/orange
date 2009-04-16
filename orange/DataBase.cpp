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

#include "stdafx.h"
#include "DataBase.h"

CDataDB data_db;
CAccountsDB accounts_db;

CDatabaseHandler::CDatabaseHandler()
{
	db = QSqlDatabase::addDatabase("QMYSQL");
}

/*bool CDatabaseHandler::Connect()
{
	this->db.setHostName("localhost");
	this->db.setUserName("root");
	this->db.setPassword("dagal");
	this->db.setDatabaseName("oranged");
	return this->db.open();
}*/

CDatabaseHandler::~CDatabaseHandler()
{
}

void CDatabaseHandler::LockForRead()
{
	this->rwl.lockForRead();
}

void CDatabaseHandler::LockForWrite()
{
	this->rwl.lockForWrite();
}

void CDatabaseHandler::Unlock()
{
	this->rwl.unlock();
}

bool CDataDB::Connect()
{
	this->db.setHostName(config.data_db_hostname.c_str());
	this->db.setUserName(config.data_db_username.c_str());
	this->db.setPassword(config.data_db_password.c_str());
	this->db.setDatabaseName(config.data_db_dbname.c_str());
	return this->db.open();
}

bool CAccountsDB::Connect()
{
	this->db.setHostName(config.accounts_db_hostname.c_str());
	this->db.setUserName(config.accounts_db_username.c_str());
	this->db.setPassword(config.accounts_db_password.c_str());
	this->db.setDatabaseName(config.accounts_db_dbname.c_str());
	return this->db.open();
}