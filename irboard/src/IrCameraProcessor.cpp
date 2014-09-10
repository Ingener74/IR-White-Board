/*
 * IrCameraProcessor.cpp
 *
 *  Created on: Sep 3, 2014
 *      Author: pavel
 */

#include <stdexcept>
#include <future>
#include <iostream>

#include <IrCameraProcessor.h>

using namespace std;
using namespace cv;

IrCameraProcessor::IrCameraProcessor(SensorCreator sensorCreator, IrSpotReceiver irSpot, Thresholder thresholder, ImageOutput imageOutput) :
        _irSpot(irSpot ? irSpot : throw invalid_argument("invalid ir spot receiver"))
{
    auto sc = sensorCreator ? sensorCreator : throw invalid_argument("sensor creator is empty");
    auto threshold = thresholder ? thresholder : throw invalid_argument("invalid thresholder");

    promise<exception_ptr> start_promise;
    auto start = start_promise.get_future();

    _thread = thread([this, sc, threshold, imageOutput](promise<exception_ptr> &start)
    {
        try
        {
            auto sensor = sc();

            if(!sensor->isOpened()) throw std::runtime_error("blabla");

            start.set_exception(exception_ptr());

            for(;;)
            {
                Mat image;

                *sensor >> image;

                auto th = threshold();

                if(imageOutput)imageOutput(image);

                this_thread::sleep_for(chrono::milliseconds(30));
                _irSpot(320, 240);
            }
        }
        catch (exception const & e)
        {
            cerr << "ir camera processor error: " << e.what() << endl;
            start.set_exception(current_exception());
        }

    }, ref(start_promise));
    _thread.detach();

    start.wait();
    if (start.get()) rethrow_exception(start.get());
}

IrCameraProcessor::~IrCameraProcessor()
{
    _thread = thread();
}

