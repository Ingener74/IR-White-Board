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
#include <SettingsWindow.h>
#include <CalibrationWindow.h>

using namespace std;
using namespace std::placeholders;
using namespace cv;

int main(int argc, char* argv[])
{
    try
    {
        // mac os
        auto app = make_shared<QApplication>(argc, argv);

        auto calibrationWindow = make_shared<CalibrationWindow>([]()
        {
            return Point(200, 200);
        });

        auto settingsWindow = make_shared<SettingsWindow>([]()
        {
            return 255 - 3;
        });
        settingsWindow->setWindowFlags(settingsWindow->windowFlags() & ~(Qt::WindowMinimizeButtonHint));
        settingsWindow->setWindowFlags(settingsWindow->windowFlags() & ~(Qt::WindowMaximizeButtonHint));

        auto mainWindow = make_shared<MainWindow>(app, settingsWindow, calibrationWindow);
        mainWindow->setWindowFlags(mainWindow->windowFlags() & ~(Qt::WindowMinimizeButtonHint));
        mainWindow->setWindowFlags(mainWindow->windowFlags() & ~(Qt::WindowMaximizeButtonHint));
        mainWindow->show();

        auto irMouse = make_shared<IrMouse>(
            bind(&SettingsWindow::slotDrawSensorImage, settingsWindow.get(), _1),
            bind(&SettingsWindow::getThreshold, settingsWindow.get()),
            bind(&SettingsWindow::getImageSelector, settingsWindow.get())
        );

        return app->exec();
    }
    catch (exception const & e)
    {
        cerr << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }
}
