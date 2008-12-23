#ifdef _WIN32
#pragma warning(disable:4786)
#endif
/*
 **	Query.h
 **
 **	Published / author: 2001-02-15 / grymse@alhem.net
 **/

/*
Copyright (C) 2001  Anders Hedstrom

This program is made available under the terms of the GNU GPL.

If you would like to use this program in a closed-source application,
a separate license agreement is available. For information about 
the closed-source license agreement for this program, please
visit http://www.alhem.net/sqlwrapped/license.html and/or
email license@alhem.net.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef _QUERY_H
#define _QUERY_H

#include <string>
#include <map>
#ifdef WIN32
typedef unsigned __int64 uint64_t;
typedef __int64 int64_t;
#else
#include <stdint.h>
#endif


#ifdef MYSQLW_NAMESPACE
namespace MYSQLW_NAMESPACE {
#endif


/** SQL Statement execute / result set helper class. */
class Query 
{
public:
	/** Constructor accepting reference to database object. */
	Query(Database& dbin);
	/** Constructor accepting reference to database object
		and query to execute. */
	Query(Database& dbin,const std::string& sql);
	~Query();

	/** Check to see if database object is connectable. */
	bool Connected();
	/** Return reference to database object. */
	Database& GetDatabase() const;
	/** Return string of last query executed. */
	const std::string& GetLastQuery();

	/** execute() returns true if query is successful,
		does not store result */
	bool execute(const std::string& sql);
	/** execute query and store result. */
	MYSQL_RES *get_result(const std::string& sql);

	/** free stored result, must be called after get_result() */
	void free_result();
	/** Fetch next result row.
		\return false if there was no row to fetch (end of rows) */
	MYSQL_ROW fetch_row();
	/** Get id of last insert. */
	my_ulonglong insert_id();
	/** Returns number of rows returned by last select call. */
	long num_rows();
	/** Number of columns in current result. */
	int num_cols();
	/** Last error string. */
	std::string GetError();
	/** Last error code. */
	int GetErrno();

	/** Check if column x in current row is null. */
	bool is_null(const std::string& x);
	bool is_null(int x);
	bool is_null();

	/** Execute query and return first result as a string. */
	const char *get_string(const std::string& sql);
	/** Execute query and return first result as a long integer. */
	long get_count(const std::string& sql);
	/** Execute query and return first result as a double. */
	double get_num(const std::string& sql);

	const char *getstr(const std::string& x);
	const char *getstr(int x);
	const char *getstr();
	long getval(const std::string& x);
	long getval(int x);
	long getval();
	unsigned long getuval(const std::string& x);
	unsigned long getuval(int x);
	unsigned long getuval();
	int64_t getbigint(const std::string& x);
	int64_t getbigint(int x);
	int64_t getbigint();
	uint64_t getubigint(const std::string& x);
	uint64_t getubigint(int x);
	uint64_t getubigint();
	double getnum(const std::string& x);
	double getnum(int x);
	double getnum();

	std::string safestr(const std::string& x);

protected:
	Query(Database *dbin);
	Query(Database *dbin,const std::string& sql);
private:
	Query(const Query& q) : m_db(q.GetDatabase()) {}
	Query& operator=(const Query& ) { return *this; }
	void error(const std::string& );
	Database& m_db;
	Database::OPENDB *odb;
	MYSQL_RES *res;
	MYSQL_ROW row;
	short rowcount;
	std::string m_tmpstr;
	std::string m_last_query;
	std::map<std::string,int> m_nmap;
	int m_num_cols;
};


#ifdef MYSQLW_NAMESPACE
} // namespace MYSQLW_NAMESPACE {
#endif

#endif // _QUERY_H
