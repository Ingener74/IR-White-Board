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

#include <IrCameraProcessor.h>
#include <MainWindow.h>

using namespace std;
using namespace std::placeholders;
using namespace cv;

int main(int argc, char* argv[])
{
    try
    {
        auto app = make_shared<QApplication>(argc, argv);

        auto mainWindow = make_shared<MainWindow>(app);
        mainWindow->setWindowFlags(mainWindow->windowFlags() & ~(Qt::WindowMinimizeButtonHint));
        mainWindow->setWindowFlags(mainWindow->windowFlags() & ~(Qt::WindowMaximizeButtonHint));
        mainWindow->show();

        auto irCameraProcessor = make_shared<IrCameraProcessor>(
        []()
        {
            return make_shared<VideoCapture>(0);
        },
        [](double x, double y)
        {
            cout << "x = " << x << ", y = " << y << endl;
        },
        bind(&MainWindow::putImage, mainWindow.get(), _1));

        return app->exec();
    }
    catch (exception const & e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}
