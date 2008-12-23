#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include ".\\DataBase.h"

CDatabaseHandler TestDB;

CDatabaseHandler::CDatabaseHandler()
{
	this->db = new Database("localhost", "root", "dagal", "test_db");
	this->query = new Query(*db);
}

CDatabaseHandler::~CDatabaseHandler()
{
	delete this->query;
	delete this->db;
}

const std::string CDatabaseHandler::AssembleQuery(const char *format, ...)
{
	va_list pArgs;
	va_start(pArgs, format); 
	int ret =_vscprintf( format, pArgs ) + 1;
	char * buf = new char[ret];
	ZeroMemory(buf, ret);
	vsprintf_s(buf, ret, format, pArgs);
	va_end(pArgs);
	std::string result = buf;
	delete [] buf;
	return result;
}