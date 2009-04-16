#include "stdafx.h"
#include "config.h"

#include <QtCore/QSettings>

CConfigStorage config;

CConfigStorage::CConfigStorage()
{
	ZeroMemory(this, sizeof(CConfigStorage));
}

bool CConfigStorage::Read()
{
	QSettings cfg(".\\orange.ini", QSettings::Format::IniFormat);
	cfg.beginGroup("System");
	this->world_tick_rate = cfg.value("world_tick_rate", 33).toUInt();
	this->log_file_name = cfg.value("log_file_name", ".\\orange.log").toString().toStdString();
	cfg.endGroup();
	cfg.beginGroup("DataDB");
	this->data_db_dbname = cfg.value("dbname", "orange").toString().toStdString();
	this->data_db_hostname = cfg.value("hostname", "localhost").toString().toStdString();
	this->data_db_username = cfg.value("username", "root").toString().toStdString();
	this->data_db_password = cfg.value("password", "orange").toString().toStdString();
	cfg.endGroup();
	cfg.beginGroup("AccountsDB");
	this->accounts_db_dbname = cfg.value("dbname", "daemon").toString().toStdString();
	this->accounts_db_hostname = cfg.value("hostname", "localhost").toString().toStdString();
	this->accounts_db_username = cfg.value("username", "root").toString().toStdString();
	this->accounts_db_password = cfg.value("password", "orange").toString().toStdString();
	cfg.endGroup();
	return true;
}