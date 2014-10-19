/*
 * IrMouse.h
 *
 *  Created on: Sep 10, 2014
 *      Author: pavel
 */

#ifndef IRMOUSE_H_
#define IRMOUSE_H_

#include <atomic>
#include <thread>

#include <IrCameraProcessor.h>
#include <Transformer.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Platform;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using CalibrationEnd  = std::function<void()>;
using PlatformCreator = std::function<std::shared_ptr<Platform>()>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IrMouse
{
public:
    IrMouse(PlatformCreator, ImageOutput, RemoteVariable<int> threshold, OutputImageSelector, CalibrationEnd,
            RemoteVariable<int> sensorSelector,
            RemoteVariable<Transformer> transformer);
    virtual ~IrMouse();

private:
    std::thread _thread;
    std::atomic<bool> _stopThread;
};

#endif /* IRMOUSE_H_ */
