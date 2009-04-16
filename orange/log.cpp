#include "stdafx.h"
#include "log.h"

CLog Log;

CLog::CLog()
{
	this->log_file = NULL;
}

CLog::~CLog()
{
	if(this->log_file)
	{
		fclose(this->log_file);
	}
}

bool CLog::Init(const char* file)
{
	if(!file)
	{
		return false;
	}
	errno_t error = fopen_s(&(this->log_file), file, "a+");
	if(error)
	{
		return false;
	}
	return true;
}

void CLog::String(const char *format, ...)
{
	va_list pArgs;
	va_start(pArgs, format); 
	int ret =_vscprintf(format, pArgs) + 1;
	char * buf = new char[ret];
	ZeroMemory(buf, ret);
	vsprintf_s(buf, ret, format, pArgs);
	va_end(pArgs);
	std::string logstring;
	logstring.append(buf);
	logstring.append("\n");
	delete [] buf;
	this->_print(logstring);
}

void CLog::Debug(const char *format, ...)
{
#ifdef _DEBUG
	va_list pArgs;
	va_start(pArgs, format); 
	int ret =_vscprintf(format, pArgs) + 1;
	char * buf = new char[ret];
	ZeroMemory(buf, ret);
	vsprintf_s(buf, ret, format, pArgs);
	va_end(pArgs);
	std::string logstring;
	logstring.append("[DEBUG] ");
	logstring.append(buf);
	logstring.append("\n");
	delete [] buf;
	this->_print(logstring);
#endif
}

void CLog::_print(const std::string &log_string)
{
	this->mtx.lock();
	printf_s(log_string.c_str());
	fwrite(log_string.c_str(), sizeof(uint8), log_string.size(), this->log_file);
	this->mtx.unlock();
}