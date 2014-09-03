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

IrCameraProcessor::IrCameraProcessor(IrSpotReceiver irSpot) :
        _irSpot(irSpot ? irSpot : throw invalid_argument("ir spot receiver empty"))
{
    promise<exception_ptr> start_promise;

    auto start = start_promise.get_future();

    _thread = thread([this](promise<exception_ptr> &start)
    {
        try
        {

            start.set_exception(exception_ptr());

            for(;;)
            {

                this_thread::sleep_for(chrono::milliseconds(30));
                _irSpot(0.5, 0.5);
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
    if (start) rethrow_exception(start.get());
}

IrCameraProcessor::~IrCameraProcessor()
{
    _thread = thread();
}

