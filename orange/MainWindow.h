#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QtGui\\QtGui>

class CMainWindow : public QMainWindow
{
public:
	CMainWindow();
	void insertText(const std::string& text);
protected:
	void closeEvent(QCloseEvent* _event);
private:
	QTextEdit * textEdit;
};

#endif