//============================================================================
// Name        : SmartPen.cpp
// Author      : Shnayder Pavel aka Ingener74
// Version     :
// Copyright   : 
// Description :
//============================================================================

// #include <qtgui/qwidget.h>
// #include <qtgui/qapplication.h>
// #include <qtcore/qstring.h>
// #include <QtCore/qsharedmemory.h>

#include <MainWindow.h>
#include <memory>
#include <QtWidgets/QApplication>

using namespace std;

int main(int argc, char* argv[])
{
//	QSharedMemory oneInstance("SmartPen_SharedForOneInstance");
//	if(!oneInstance.create(512, QSharedMemory::ReadWrite)){
//		return 0;
//	}

    auto app = make_shared<QApplication>(argc, argv);

    auto mainWindow = make_shared<MainWindow>(app);
    mainWindow->setWindowFlags(mainWindow->windowFlags() & ~(Qt::WindowMinimizeButtonHint));
    mainWindow->setWindowFlags(mainWindow->windowFlags() & ~(Qt::WindowMaximizeButtonHint));
    mainWindow->show();

    return app->exec();
}
