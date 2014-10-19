/*
 * IrCameraProcessor.cpp
 *
 *  Created on: Sep 3, 2014
 *      Author: pavel
 */

#include <stdexcept>
#include <future>
#include <iostream>
#include <chrono>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <IrCameraProcessor.h>

using namespace std;
using namespace cv;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IrCameraProcessor::IrCameraProcessor
(
    SensorCreator            sensorCreator,
    IrSpotReceiver           irSpot,
    RemoteVariable<int>      threshold,
    promise<exception_ptr>&  errorControl,
    OutputImageSelector      outputImageMode,
    IrProcessorControl       irControl,
    RemoteVariable<int>      sensorSelector,
    ImageOutput              imageOutput
){
    _thread = thread([=](promise<exception_ptr> &errorControl)
    {
        try
        {
            auto sensor = sensorCreator();

            int currentSensor = sensorSelector;

            if(!sensor->isOpened()) throw std::runtime_error("can't open ir sensor device");

            while(!irControl() && sensorSelector == currentSensor)
            {
                Mat image, mono, thresh;

                *sensor >> image;

                int th = threshold;

                auto start = chrono::high_resolution_clock::now();

                cvtColor(image, mono, CV_BGR2GRAY);
                cv::threshold(mono, thresh, th, (unsigned char)(-1), CV_THRESH_BINARY);

                vector<vector<Point> > contours;
                findContours(thresh, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

                Mat outImage(thresh.size(), CV_8UC3, Scalar(0));
                drawContours(outImage, contours, -1, CV_RGB(0, 255, 0), 1);

                // contour processing for search right contour appropriate flash from pen

                // first way is find most of contour and send raw mouse his center mass and area
                // second way is search right contour metod interrelation function

                if(!contours.empty())
                {
//                  // check that the correct camera
//                  if( ProbablyWroneCamera(contours, thresh) ){
//                      lInCorrentCounter++;
//                  }
//                  lFullCounter++;
//                  // end check

                    int maxi = 0, maxlen = 0;
                    for(int i = 0; i < contours.size(); ++i)
                    {
                        if(contours[i].size() > maxlen)
                        {
                            maxlen = contours[i].size();
                            maxi = i;
                        }
                    }

                    float maxarea=contourArea(contours[maxi]);
                    Moments mom = moments(contours[maxi]);
                    float cx = mom.m10 / mom.m00, cy = mom.m01 / mom.m00;

                    if
                    (
                        static_cast<int>(cx) < image.cols &&
                        static_cast<int>(cx) >= 0 &&
                        static_cast<int>(cy) < image.rows &&
                        static_cast<int>(cy) >= 0
                    ){
                        /*
                        lastRawPosition = Point2f(cx, cy);

                        circle(outImage, Point(lastRawPosition.x, lastRawPosition.y), 2, CV_RGB(255, 255, 0), -1);

                        maxarea /= (outImage.cols*outImage.rows);

                        pRawMouse->Process(lastRawPosition, true, maxarea);
                        */
                    }
                }
                else //if(contours.empty())
                {
//                  pRawMouse->Process(lastRawPosition, false, 0);
                }

                auto end = chrono::high_resolution_clock::now();

                auto execTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
                cout << "exec time " << execTime << " ms" << endl;

                if(imageOutput)imageOutput(outputImageMode() ? outImage : image);
                irSpot(320, 240);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IrCameraProcessor::~IrCameraProcessor()
{
    _thread.join();
    cout << "IrCameraProcessor::~IrCameraProcessor()" << endl;
}

