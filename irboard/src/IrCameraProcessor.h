/*
 * IrCameraProcessor.h
 *
 *  Created on: Sep 3, 2014
 *      Author: pavel
 */

#ifndef IRCAMERAPROCESSOR_H_
#define IRCAMERAPROCESSOR_H_

#include <cstdint>
#include <exception>
#include <functional>
#include <future>
#include <memory>
#include <thread>

#include <RemoteVariable.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace cv
{
class VideoCapture;
class Mat;
} /* namespace cv */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using SensorCreator = std::function<std::shared_ptr<cv::VideoCapture>()>;
using IrSpotReceiver = std::function<void (int, int)>;
using ImageOutput = std::function<void(cv::Mat)>;
using OutputImageSelector = std::function<int()>;
using IrProcessorControl = std::function<bool()>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IrCameraProcessor
{
public:
    IrCameraProcessor(
            SensorCreator,
            IrSpotReceiver,
            RemoteVariable<int> threshold,
            std::promise<std::exception_ptr>& errorControl,
            OutputImageSelector,
            IrProcessorControl,
            RemoteVariable<int> sensorSelector,
            ImageOutput = ImageOutput());
    virtual ~IrCameraProcessor();

private:
    std::thread _thread;
};

#endif /* IRCAMERAPROCESSOR_H_ */
