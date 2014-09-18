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

namespace cv
{
class VideoCapture;
class Mat;
} /* namespace cv */

using SensorCreator = std::function<std::shared_ptr<cv::VideoCapture>()>;
using IrSpotReceiver = std::function<void (int, int)>;
using ImageOutput = std::function<void(cv::Mat)>;
using Thresholder = std::function<uint8_t()>;
using OutputImageSelector = std::function<int()>;

class IrCameraProcessor
{
public:
    IrCameraProcessor(
            SensorCreator,
            IrSpotReceiver,
            Thresholder,
            std::promise<std::exception_ptr>& errorControl,
            OutputImageSelector,
            ImageOutput = ImageOutput());
    virtual ~IrCameraProcessor();

private:
    std::thread _thread;
};

#endif /* IRCAMERAPROCESSOR_H_ */
