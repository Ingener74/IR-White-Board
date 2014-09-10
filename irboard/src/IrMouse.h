/*
 * IrMouse.h
 *
 *  Created on: Sep 10, 2014
 *      Author: pavel
 */

#ifndef IRMOUSE_H_
#define IRMOUSE_H_

#include <IrCameraProcessor.h>
#include <thread>

class IrMouse
{
public:
    IrMouse(ImageOutput);
    virtual ~IrMouse();

private:
    std::thread _thread;
};

#endif /* IRMOUSE_H_ */
