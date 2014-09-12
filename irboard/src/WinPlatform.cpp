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

WinPlatform::WinPlatform()
{
}

WinPlatform::~WinPlatform()
{
    cout << "WinPlatform::~WinPlatform()" << endl;
}

//void WinPlatform::mouseCommand(int x, int y, MouseButton enumMouseButton, MouseCommand enumMouseCommand)
//{
//}
//
//Transformer WinPlatform::loadTransformer()
//{
//}
//
//void WinPlatform::saveTransformer(const Transformer&)
//{
//}

std::shared_ptr<cv::VideoCapture> WinPlatform::createVideoSource()
{
    return make_shared<VideoCapture>(0);
}
