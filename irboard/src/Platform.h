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

namespace cv
{
class VideoCapture;
} /* namespace cv */

class Transformer;

class Platform
{
public:
    Platform();
    virtual ~Platform();

    void mouseCommand(int x, int y, MouseButton, MouseCommand);

    Transformer loadTransformer();
    void saveTransformer(const Transformer&);

    std::shared_ptr<cv::VideoCapture> createVideoSource();
};

#endif /* PLATFORM_H_ */
