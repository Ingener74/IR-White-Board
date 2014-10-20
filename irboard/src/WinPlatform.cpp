/*
 * WinPlatform.cpp
 *
 *  Created on: Sep 12, 2014
 *      Author: pavel
 */

#include <opencv2/highgui/highgui.hpp>
#include <WinPlatform.h>

using namespace std;
using namespace cv;

WinPlatform::WinPlatform(RemoteVariable<int> sensor): Platform(sensor)
{
}

WinPlatform::~WinPlatform()
{
    cout << "WinPlatform::~WinPlatform()" << endl;
}

//void WinPlatform::mouseCommand(int x, int y, MouseButton enumMouseButton, MouseCommand enumMouseCommand)
//{
//}

std::shared_ptr<cv::VideoCapture> WinPlatform::createVideoSource()
{
    return make_shared<VideoCapture>(_sensor);
}
