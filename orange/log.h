#ifndef _LOG_H_
#define _LOG_H_

#include <QtCore\\QMutex>

class CLog
{
public:
	CLog();
	~CLog();
	void String(const char* format, ...);
	bool Init(const char* file);
private:
	void _print(const std::string& log_string);

	FILE* log_file;
	QMutex mtx;
};

extern CLog Log;

#endif