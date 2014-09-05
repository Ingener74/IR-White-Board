//============================================================================
// Name        : SmartPen.cpp
// Author      : Shnayder Pavel aka Ingener74
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <memory>
#include <iostream>

#include <QtWidgets/QApplication>

#include <IrCameraProcessor.h>
#include <MainWindow.h>

using namespace std;
using namespace std::placeholders;
using namespace cv;

class VideoCaptureMock : public VideoCapture
{
public:
    VideoCaptureMock(int i)
    {
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

        image = cv::Mat(640, 480, CV_8UC3, Scalar(0,0,0));

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


/*
 *  *------------------*    *----------------------*
 *  |                  |    |                      |
 *  |                  |    |                      |
 *  |                  |    |                      |
 * -|  VideoCapture    |--->|  IR Video Processor  |--->
 *  |                  |    |                      |
 *  |                  |    |                      |
 *  |                  |    |                      |
 *  *------------------*    *----------------------*
 *
 */


int main(int argc, char* argv[])
{
    try
    {
        auto app = make_shared<QApplication>(argc, argv);

        auto mainWindow = make_shared<MainWindow>(app);
        mainWindow->setWindowFlags(mainWindow->windowFlags() & ~(Qt::WindowMinimizeButtonHint));
        mainWindow->setWindowFlags(mainWindow->windowFlags() & ~(Qt::WindowMaximizeButtonHint));
        mainWindow->show();

        auto irCameraProcessor = make_shared<IrCameraProcessor>([]()
        {
            return make_shared</*VideoCapture*/VideoCaptureMock>(0);
        },
        [](int x, int y)
        {
            cout << "x = " << x << ", y = " << y << endl;
        }, bind(&MainWindow::putImage, mainWindow.get(), _1)
        /*[](Mat image)
        {
            cout << image.rows << " x " << image.cols << endl;
        }*/);

        return app->exec();
    }
    catch (exception const & e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}
