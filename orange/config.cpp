#include "stdafx.h"
#include ".\\config.h"

#include <QtCore\\QSettings>

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
	return true;
}