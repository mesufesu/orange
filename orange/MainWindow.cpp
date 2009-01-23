#include "stdafx.h"
#include ".\\MainWindow.h"
#include ".\\ServerSocket.h"
#include ".\\objectmanager.h"
#include ".\\ItemManager.h"
#include ".\\WorldMap.h"

CMainWindow::CMainWindow()
{
	this->textEdit = new QTextEdit;
	this->textEdit->setReadOnly(true);
	this->setCentralWidget(this->textEdit);
	this->setMinimumSize(800, 600);
}

void CMainWindow::closeEvent(QCloseEvent *event)
{
	_SocketThread.quit();
	ObjManager.Quit();
	ItemManager.Quit();
	for(uint32 i = 0; i < MAX_MAPS; ++i)
	{
		WorldMap[i].Quit();
	}
}

void CMainWindow::insertText(const std::string& text)
{
	this->textEdit->insertPlainText("pizdec");
}