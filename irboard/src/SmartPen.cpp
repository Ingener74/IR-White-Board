//============================================================================
// Name        : SmartPen.cpp
// Author      : Shnayder Pavel aka Ingener74
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>

// #include <qtgui/qwidget.h>
// #include <qtgui/qapplication.h>
// #include <qtcore/qstring.h>
// #include <QtCore/qsharedmemory.h>
// #include "C_MainWindow.h"
//#include "md5.h"



using namespace std;

		QApplication*					pApplication	= 0;
		C_MainWindow*					pMainWindow		= 0;

int main( int argc, char* argv[]){

//	QSharedMemory oneInstance("SmartPen_SharedForOneInstance");
//	if(!oneInstance.create(512, QSharedMemory::ReadWrite)){
//		return 0;
//	}

	pApplication = new QApplication(argc, argv);

	pMainWindow = new C_MainWindow;
	pMainWindow->setWindowFlags(pMainWindow->windowFlags() & ~(Qt::WindowMinimizeButtonHint));
	pMainWindow->setWindowFlags(pMainWindow->windowFlags() & ~(Qt::WindowMaximizeButtonHint));
	pMainWindow->show();

	return pApplication->exec();
}
