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

#ifdef MINGW
#include <WinPlatform.h>
#endif

using namespace std;
using namespace std::placeholders;
using namespace cv;

IrMouse::IrMouse(ImageOutput imageOut, Thresholder thresholder, OutputImageSelector outputImageSelector)
{
    _stopThread = false;
    _thread = thread([imageOut, thresholder, outputImageSelector, this]()
    {
        while(!_stopThread)
        {
            try
            {
#ifdef MINGW
                auto platform = make_shared<WinPlatform>();
#else
                auto platform = make_shared<Platform>();
#endif

                auto coordConverter = make_shared<CoordinateConverter>(
                    bind(&Platform::mouseCommand, platform.get(), _1, _2, _3, _4),
                    bind(&Platform::loadTransformer, platform.get()),
                    bind(&Platform::saveTransformer, platform.get(), _1)
                );

                promise<exception_ptr> errorControl;
                auto controlFuture = errorControl.get_future();

                _irProcessor = make_shared<IrCameraProcessor>(
                    bind(&Platform::createVideoSource, platform.get()),
                    bind(&CoordinateConverter::putCoordinates, coordConverter.get(), _1, _2),
                    thresholder,
                    ref(errorControl),
                    outputImageSelector,
                    bind(&IrMouse::isStopThread, this),
                    // bind(&atomic<bool>::load, &_stopThread, memory_order_seq_cst),
                    imageOut
                );

                controlFuture.wait();

                if(controlFuture.get())rethrow_exception(controlFuture.get());
            }
            catch (exception const & e)
            {
                cerr << "IrMouse error: " << e.what() << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(1000));
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

bool IrMouse::isStopThread()
{
    return _stopThread;
}
