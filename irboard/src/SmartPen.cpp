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

#include <IrMouse.h>
#include <MainWindow.h>

using namespace std;
using namespace std::placeholders;
using namespace cv;

/*
 *  *------------------*    *----------------------*
 *  |                  |    |                      |
 *  |                  |    |                      |
 *  |                  |    |                      |
 * -|  VideoCapture    |--->|  IR Video Processor  |--->
 *  |                  |    |                      |
 *  |                  |    |                      |
 *  |                  |    |                      |
 *  *------------------*    *----------------------*
 *
 */

int main(int argc, char* argv[])
{
    try
    {
        auto app = make_shared<QApplication>(argc, argv);

        auto settingsWindow = make_shared<SettingsWindow>();
        settingsWindow->setWindowFlags(settingsWindow->windowFlags() & ~(Qt::WindowMinimizeButtonHint));
        settingsWindow->setWindowFlags(settingsWindow->windowFlags() & ~(Qt::WindowMaximizeButtonHint));

        auto mainWindow = make_shared<MainWindow>(app, settingsWindow);
        mainWindow->setWindowFlags(mainWindow->windowFlags() & ~(Qt::WindowMinimizeButtonHint));
        mainWindow->setWindowFlags(mainWindow->windowFlags() & ~(Qt::WindowMaximizeButtonHint));
        mainWindow->show();

        auto irMouse = make_shared<IrMouse>(bind(&MainWindow::putImage, mainWindow.get(), _1));

        return app->exec();
    }
    catch (exception const & e)
    {
        cerr << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }
}
