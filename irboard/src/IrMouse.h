/*
 * IrMouse.h
 *
 *  Created on: Sep 10, 2014
 *      Author: pavel
 */

#ifndef IRMOUSE_H_
#define IRMOUSE_H_

#include <IrCameraProcessor.h>
#include <atomic>
#include <thread>

class IrMouse
{
public:
    IrMouse(ImageOutput, Thresholder, OutputImageSelector);
    virtual ~IrMouse();

private:
    std::thread _thread;

    bool isStopThread();
    std::atomic<bool> _stopThread;

    std::shared_ptr<IrCameraProcessor> _irProcessor;
};

#endif /* IRMOUSE_H_ */
