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

class Platform;

using CalibrationEnd  = std::function<void()>;
using PlatformCreator = std::function<std::shared_ptr<Platform>()>;

class IrMouse
{
public:
    IrMouse(PlatformCreator, ImageOutput, Thresholder, OutputImageSelector, CalibrationEnd, RemoteVariable<int> sensorSelector);
    virtual ~IrMouse();

private:
    std::thread _thread;
    std::atomic<bool> _stopThread;
};

#endif /* IRMOUSE_H_ */
