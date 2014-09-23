/*
 * IrCameraProcessor.cpp
 *
 *  Created on: Sep 3, 2014
 *      Author: pavel
 */

#include <stdexcept>
#include <future>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <IrCameraProcessor.h>

using namespace std;
using namespace cv;

IrCameraProcessor::IrCameraProcessor(
    SensorCreator sensorCreator,
    IrSpotReceiver irSpot,
    Thresholder thresholder,
    promise<exception_ptr>& errorControl,
    OutputImageSelector outputImageMode,
    IrProcessorControl irControl,
    ImageOutput imageOutput
){
    auto sc        = sensorCreator   ? sensorCreator   : throw invalid_argument("sensor creator is empty");
    auto threshold = thresholder     ? thresholder     : throw invalid_argument("invalid thresholder");
    auto ir        = irSpot          ? irSpot          : throw invalid_argument("invalid ir spot receiver");
    auto oim       = outputImageMode ? outputImageMode : throw invalid_argument("output image mode is invalid");
    auto irc       = irControl       ? irControl       : throw invalid_argument("ir processor control is invalid");

    _thread = thread([this, sc, ir, threshold, imageOutput, oim, irc](promise<exception_ptr> &errorControl)
    {
        try
        {
            auto sensor = sc();

            if(!sensor->isOpened()) throw std::runtime_error("can't open ir sensor device");

            while(!irc())
            {
                Mat image, mono, thresh;

                *sensor >> image;

                auto th = threshold();

                cvtColor(image, mono, CV_BGR2GRAY);
                cv::threshold(mono, thresh, th, (unsigned char)(-1), CV_THRESH_BINARY);

                vector<vector<Point> > contours;
                findContours(thresh, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

                Mat outImage(thresh.size(), CV_8UC3, Scalar(0));
                drawContours(outImage, contours, -1, CV_RGB(0, 255, 0), 1);

                if(imageOutput)imageOutput(oim() ? outImage : image);
                ir(320, 240);
            }
            errorControl.set_value(exception_ptr()); // set_exception(exception_ptr()) now working under mingw
            cout << "ir processor is stopped" << endl;
        }
        catch (exception const & e)
        {
            errorControl.set_exception(current_exception());
        }

    }, ref(errorControl));
}

IrCameraProcessor::~IrCameraProcessor()
{
    _thread.join();
    cout << "IrCameraProcessor::~IrCameraProcessor()" << endl;
}

