/*
 * Platform.h
 *
 *  Created on: Sep 9, 2014
 *      Author: pavel
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <memory>
#include <functional>

#include <CoordinateConverter.h>
#include <RemoteVariable.h>

namespace cv
{
class VideoCapture;
} /* namespace cv */

class Transformer;

using SensorSelector = std::function<int()>;

class Platform
{
public:
    Platform(RemoteVariable<int>);
    virtual ~Platform();

    virtual void mouseCommand(int x, int y, MouseButton, MouseCommand);

    virtual Transformer loadTransformer();
    virtual void saveTransformer(const Transformer&);

    virtual std::shared_ptr<cv::VideoCapture> createVideoSource();

protected:
    RemoteVariable<int> _sensor;
};

#endif /* PLATFORM_H_ */
