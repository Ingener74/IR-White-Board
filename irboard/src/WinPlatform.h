/*
 * WinPlatform.h
 *
 *  Created on: Sep 12, 2014
 *      Author: pavel
 */

#ifndef WINPLATFORM_H_
#define WINPLATFORM_H_

#include <Platform.h>

class WinPlatform: public Platform
{
public:
    WinPlatform();
    virtual ~WinPlatform();

//    virtual void mouseCommand(int x, int y, MouseButton, MouseCommand);
//
//    virtual Transformer loadTransformer();
//    virtual void saveTransformer(const Transformer&);

    virtual std::shared_ptr<cv::VideoCapture> createVideoSource();
};

#endif /* WINPLATFORM_H_ */
