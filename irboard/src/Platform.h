/*
 * Platform.h
 *
 *  Created on: Sep 9, 2014
 *      Author: pavel
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <CoordinateConverter.h>
#include <memory>
#include <functional>

namespace cv
{
class VideoCapture;
} /* namespace cv */

class Transformer;

using SensorSelector = std::function<int()>;

class Platform
{
public:
    Platform(SensorSelector);
    virtual ~Platform();

    virtual void mouseCommand(int x, int y, MouseButton, MouseCommand);

    virtual Transformer loadTransformer();
    virtual void saveTransformer(const Transformer&);

    virtual std::shared_ptr<cv::VideoCapture> createVideoSource();

protected:
    SensorSelector _ss;
};

#endif /* PLATFORM_H_ */
