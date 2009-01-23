#ifndef _LOG_H_
#define _LOG_H_

#include <QtCore\\QMutex>
#include ".\\MainWindow.h"

class CLog
{
public:
	QTextEdit *texted;
	CLog();
	~CLog();
	void String(const char* format, ...);
	bool Init(const char* file);
private:
	void _print(const std::string& log_string);

	FILE* log_file;
	CMainWindow * cwin;
	QMutex wmtx;
	QMutex fmtx;
};

extern CLog Log;

#endif