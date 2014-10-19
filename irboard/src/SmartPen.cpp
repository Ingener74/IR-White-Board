//============================================================================
// Name        : SmartPen.cpp
// Author      : Shnayder Pavel aka Ingener74
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <memory>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <opencv2/core/core.hpp>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

#include <IrMouse.h>
#include <MainWindow.h>
#include <SettingsWindow.h>
#include <CalibrationWindow.h>

#ifdef MINGW
#include <WinPlatform.h>
#else
#include <Platform.h>
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace cv;
using namespace boost;
using namespace boost::property_tree;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    auto app = make_shared<QApplication>(argc, argv);

    try
    {
        auto calibrationWindow = make_shared<CalibrationWindow>([](){ return Point(200, 200); });

        const string configFileName = "config.json";
        ptree pt;

        json_parser::read_json(configFileName, pt);

        /*
         *
         */
        auto threshold = RemoteVariable<int>{
            [&](){ return pt.get<int>("threshold"); },
            [&](int threshold){ pt.put("threshold", threshold); json_parser::write_json(configFileName, pt); }
        };

        /*
         *
         */
        auto sensor = RemoteVariable<int>{
            [&](){ return pt.get<int>("sensor"); },
            [&](int sensor){ pt.put("sensor", sensor); json_parser::write_json(configFileName, pt); }
        };

        /*
         *
         */
        auto transformer = RemoteVariable<Transformer>{
            [&](){
                auto transformer = Transformer{
                    pt.get<int>("transformer.width"),
                    pt.get<int>("transformer.height"),
                    [&](int i){
                        return Point{
                            pt.get<int>("transformer.coil" + to_string(i) + ".x"),
                            pt.get<int>("transformer.coil" + to_string(i) + ".y")};
                    }};
                return transformer;
            },
            [&](const Transformer& trans){
                if(!trans.isReady()) return;

                pt.put("transformer.width", trans.getWidth());
                pt.put("transformer.height", trans.getCoils().size() / trans.getWidth());
                for(int i = 0; i < trans.getCoils().size(); ++i){
                    pt.get<int>("transformer.coil" + to_string(i) + ".x");
                    pt.get<int>("transformer.coil" + to_string(i) + ".y");
                }
                json_parser::write_json(configFileName, pt);
            }
        };

        /*
         *
         */
        auto calibrationPoints = RemoteVariable<cv::Size>{
            [&](){ return Size(pt.get<int>("calibration_x"), pt.get<int>("calibration_y")); },
            [&](const Size& calibrationPoints){
                pt.put("calibration_x", calibrationPoints.width);
                pt.put("calibration_y", calibrationPoints.height);
                json_parser::write_json(configFileName, pt);
            }
        };

        auto settingsWindow = make_shared<SettingsWindow>(threshold, calibrationPoints, sensor);

        settingsWindow->setWindowFlags(settingsWindow->windowFlags() & ~(Qt::WindowMinimizeButtonHint));
        settingsWindow->setWindowFlags(settingsWindow->windowFlags() & ~(Qt::WindowMaximizeButtonHint));

        auto mainWindow = make_shared<MainWindow>(app, settingsWindow, calibrationWindow);
        mainWindow->setWindowFlags(mainWindow->windowFlags() & ~(Qt::WindowMinimizeButtonHint));
        mainWindow->setWindowFlags(mainWindow->windowFlags() & ~(Qt::WindowMaximizeButtonHint));
        mainWindow->show();

        auto irMouse = make_shared<IrMouse>(
            [=]()
            {
#ifdef MINGW
                auto platform = make_shared<WinPlatform>(sensor);
#else
                auto platform = make_shared<Platform>(sensor);
#endif
                return platform;
            },
            [=](Mat image){ settingsWindow->slotDrawSensorImage(image); },
            threshold,
            [=](){ return settingsWindow->getImageSelector(); },
            [=](){ mainWindow->calibrationEnd(); },
            sensor,
            transformer
        );

        return app->exec();
    }
    catch (std::exception const & e)
    {
        QMessageBox::critical(nullptr, "Error", e.what());
        return EXIT_FAILURE;
    }
}
