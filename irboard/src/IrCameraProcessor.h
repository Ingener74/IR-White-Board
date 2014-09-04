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

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using SensorCreator = std::function<std::shared_ptr<cv::VideoCapture>()>;
using IrSpotReceiver = std::function<void (double, double)>;
using ImageOutput = std::function<void(cv::Mat)>;

class IrCameraProcessor
{
public:
    IrCameraProcessor(SensorCreator, IrSpotReceiver, ImageOutput = ImageOutput());
    virtual ~IrCameraProcessor();

private:
    IrSpotReceiver _irSpot;

    std::thread _thread;
};

#endif /* IRCAMERAPROCESSOR_H_ */
