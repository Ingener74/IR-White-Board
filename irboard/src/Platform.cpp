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
    Mat _image;
    Point _fakeIr{-1, -1};
    std::function<void(Point)> _callback = [&](Point p){ _fakeIr = p; };

    static void mouseCallback(int event, int x, int y, int flags, void* userdata)
    {
        auto callback = *static_cast<function<void(Point)>*>(userdata);

        if ( event == EVENT_LBUTTONDOWN || (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)))
            callback(Point(x, y));
    }

public:
    VideoCaptureMock(int i)
    {
        if (0 != i) throw invalid_argument("invalid sensor");

        _image = imread("monitor.png");
        if(_image.empty()) throw runtime_error("monitor image is empty");
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
//        this_thread::sleep_for(chrono::milliseconds(1000 / 60));
//        image = cv::Mat(640, 480, CV_8UC3, Scalar(0, 0, 0));
//        circle(image, Point(240, 320), 5, Scalar(255, 255, 255), -1);

        imshow("ir-tester", _image);
        setMouseCallback("ir-tester", mouseCallback, &_callback);

        if ( waitKey(1000 / 30) == 27 ) return false;

        Mat blackImage{480, 640, CV_8UC3, Scalar{0, 0, 0}};

        circle(blackImage, _fakeIr, 3, Scalar{255,255,255}, -1);

        imshow("fake camera image", blackImage);

        _fakeIr = Point{-1, -1};

        image = blackImage;

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

shared_ptr<VideoCapture> Platform::createVideoSource()
{
    return make_shared<VideoCaptureMock>(_sensor);
}
