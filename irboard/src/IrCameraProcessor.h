/*
 * IrCameraProcessor.h
 *
 *  Created on: Sep 3, 2014
 *      Author: pavel
 */

#ifndef IRCAMERAPROCESSOR_H_
#define IRCAMERAPROCESSOR_H_

#include <thread>
#include <functional>

using IrSpotReceiver = std::function<void (double, double)>;

class IrCameraProcessor
{
public:
    IrCameraProcessor(IrSpotReceiver);
    virtual ~IrCameraProcessor();

private:
    IrSpotReceiver _irSpot;

    std::thread _thread;
};

#endif /* IRCAMERAPROCESSOR_H_ */
