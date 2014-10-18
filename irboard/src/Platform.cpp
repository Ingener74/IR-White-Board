/*
 * Platform.cpp
 *
 *  Created on: Sep 9, 2014
 *      Author: pavel
 */

#include <chrono>
#include <thread>
#include <iostream>

#include <opencv2/highgui/highgui.hpp>

#include <Platform.h>
#include <Transformer.h>

using namespace std;
using namespace cv;

class VideoCaptureMock: public VideoCapture
{
public:
    VideoCaptureMock(int i)
    {
        if (0 != i) throw invalid_argument("invalid sensor");
    }
    virtual ~VideoCaptureMock()
    {
    }

    virtual bool open(const string& filename)
    {
        return true;
    }
    virtual bool open(int device)
    {
        return true;
    }
    virtual bool isOpened() const
    {
        return true;
    }
    virtual void release()
    {
    }

    virtual bool grab()
    {
        return true;
    }
    virtual bool retrieve(Mat& image, int channel = 0)
    {
        return read(image);
    }
    virtual VideoCapture& operator >>(Mat& image)
    {
        read(image);
        return *this;
    }
    virtual bool read(Mat& image)
    {
        this_thread::sleep_for(chrono::milliseconds(1000 / 60));

        image = cv::Mat(640, 480, CV_8UC3, Scalar(0, 0, 0));

        circle(image, Point(320, 240), 2, Scalar(255, 255, 255), -1);

        return true;
    }

    virtual bool set(int propId, double value)
    {
        return true;
    }
    virtual double get(int propId)
    {
        return 0.0;
    }
};

Platform::Platform(RemoteVariable<int> sensor): _sensor(sensor)
{
}

Platform::~Platform()
{
    cout << "Platform::~Platform()" << endl;
}

void Platform::mouseCommand(int x, int y, MouseButton mouseButton, MouseCommand mouseCommand)
{
    cout << "mouse " << x << " x " << y << ", " << mouseButton << ", " << mouseCommand << endl;
}

Transformer Platform::loadTransformer()
{
    return Transformer(640, 640 * 480, [](int index)
    {
        return Point(0, 0);
    });
}

void Platform::saveTransformer(const Transformer&)
{
}

shared_ptr<VideoCapture> Platform::createVideoSource()
{
    return make_shared<VideoCaptureMock>(_sensor);
}
