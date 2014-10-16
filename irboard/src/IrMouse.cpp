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

using namespace std;
using namespace cv;

IrMouse::IrMouse
(
    PlatformCreator      pc,
    ImageOutput          imageOut,
    Thresholder          thresholder,
    OutputImageSelector  outputImageSelector,
    CalibrationEnd       ce
){
    _stopThread = false;
    _thread = thread([pc, imageOut, thresholder, outputImageSelector, ce, this]()
    {
        while(!_stopThread)
        {
            try
            {
                auto platform = pc();

                auto coordConverter = make_shared<CoordinateConverter>(
                    [platform](int x, int y, MouseButton mb, MouseCommand mc){platform->mouseCommand(x, y, mb, mc); },
                    [platform](){ return platform->loadTransformer(); },
                    [platform](const Transformer& t){ platform->saveTransformer(t); },
                    ce
                );

                promise<exception_ptr> errorControl;
                auto controlFuture = errorControl.get_future();

                auto irProcessor = make_shared<IrCameraProcessor>(
                    [platform](){ return platform->createVideoSource(); },
                    [coordConverter](int x, int y){ coordConverter->putCoordinates(x, y); },
                    thresholder,
                    ref(errorControl),
                    outputImageSelector,
                    [this](){ return _stopThread.load(); },
                    imageOut
                );

                controlFuture.wait();

                if(controlFuture.get())rethrow_exception(controlFuture.get());
            }
            catch (exception const & e)
            {
                cerr << "IrMouse error: " << e.what() << endl;
                this_thread::sleep_for(chrono::milliseconds(1000));
            }
        }
        cout << "ir mouse thread stopped" << endl;
    });
}

IrMouse::~IrMouse()
{
    _stopThread = true;
    _thread.join();
    cout << "IrMouse::~IrMouse()" << endl;
}

