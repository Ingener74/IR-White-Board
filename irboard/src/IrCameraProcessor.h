/*
 * IrCameraProcessor.h
 *
 *  Created on: Sep 3, 2014
 *      Author: pavel
 */

#ifndef IRCAMERAPROCESSOR_H_
#define IRCAMERAPROCESSOR_H_

#include <functional>
#include <memory>
#include <thread>

namespace cv
{
class VideoCapture;
class Mat;
} /* namespace cv */

using SensorCreator = std::function<std::shared_ptr<cv::VideoCapture>()>;
using IrSpotReceiver = std::function<void (int, int)>;
using ImageOutput = std::function<void(cv::Mat)>;
using Thresholder = std::function<unsigned char()>;

class IrCameraProcessor
{
public:
    IrCameraProcessor(SensorCreator, IrSpotReceiver, Thresholder, ImageOutput = ImageOutput());
    virtual ~IrCameraProcessor();

private:
    IrSpotReceiver _irSpot;

    std::thread _thread;
};

#endif /* IRCAMERAPROCESSOR_H_ */
