//============================================================================
// Name        : SmartPen.cpp
// Author      : Shnayder Pavel aka Ingener74
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <memory>
#include <iostream>

#include <QtWidgets/QApplication>

#include <MainWindow.h>

using namespace std;

int main(int argc, char* argv[])
{
    try
    {
        auto app = make_shared<QApplication>(argc, argv);

        auto mainWindow = make_shared<MainWindow>(app);
        mainWindow->setWindowFlags(mainWindow->windowFlags() & ~(Qt::WindowMinimizeButtonHint));
        mainWindow->setWindowFlags(mainWindow->windowFlags() & ~(Qt::WindowMaximizeButtonHint));
        mainWindow->show();

        return app->exec();
    }
    catch (exception const & e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}
