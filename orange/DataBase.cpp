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