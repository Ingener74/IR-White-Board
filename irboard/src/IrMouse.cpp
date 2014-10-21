/*
 * IrMouse.cpp
 *
 *  Created on: Sep 10, 2014
 *      Author: pavel
 */

#include <iostream>

#include <opencv2/highgui/highgui.hpp>

#include <CoordinateConverter.h>
#include <IrCameraProcessor.h>
#include <IrMouse.h>
#include <Platform.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace cv;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IrMouse::IrMouse
(
    PlatformCreator             platformCreator,
    ImageOutput                 imageOutput,
    RemoteVariable<int>         threshold,
    OutputImageSelector         outputImageSelector,
    CalibrationEnd              calibrationEnd,
    RemoteVariable<int>         sensorSelector,
    RemoteVariable<Transformer> transformer,
    RemoteVariable<cv::Size>    screenResolution
){
    _stopThread = false;
    _thread = thread([=]()
    {
        while(!_stopThread)
        {
            try
            {
                auto platform = platformCreator();

                auto coordConverter = make_shared<CoordinateConverter>(
                    [=](int x, int y, MouseButton mb, MouseCommand mc){platform->mouseCommand(x, y, mb, mc); },
                    transformer,
                    calibrationEnd,
                    screenResolution
                );

                promise<exception_ptr> errorControl;
                auto controlFuture = errorControl.get_future();

                auto irProcessor = make_shared<IrCameraProcessor>(
                    [platform](){ return platform->createVideoSource(); },
                    [coordConverter](int x, int y){ coordConverter->putCoordinates(x, y); },
                    threshold,
                    ref(errorControl),
                    outputImageSelector,
                    [this](){ return _stopThread.load(); },
                    sensorSelector,
                    imageOutput
                );

                controlFuture.wait();

                if(controlFuture.get())rethrow_exception(controlFuture.get());
            }
            catch (exception const & e)
            {
                cerr << "IrMouse error: " << e.what() << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
        cout << "ir mouse thread stopped" << endl;
    });
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IrMouse::~IrMouse()
{
    _stopThread = true;
    _thread.join();
    cout << "IrMouse::~IrMouse()" << endl;
}

