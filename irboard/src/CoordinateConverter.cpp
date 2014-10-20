/*
 * CoordinateConverter.cpp
 *
 *  Created on: Sep 9, 2014
 *      Author: pavel
 */

#include <iostream>

#include <CoordinateConverter.h>

using namespace std;
using namespace cv;

ostream& operator<<(ostream& out, const MouseButton& rho)
{
    static string mb[]
    { "No Button", "Left", "Right", "Middle", };
    out << mb[static_cast<int>(rho)];
    return out;
}

ostream& operator<<(ostream& out, const MouseCommand& rho)
{
    static string mc[]
    { "Move", "Up", "Down", };
    out << mc[static_cast<int>(rho)];
    return out;
}

CoordinateConverter::CoordinateConverter(MouseOutput mo, RemoteVariable<Transformer> transformer, CalibrationEnd ce,
        RemoteVariable<cv::Size> screenResolution) :
        _mouseOutput(mo ? mo : throw invalid_argument("mouse output is invalid")),
        _remoteTransformer(transformer),
        _transformer(_remoteTransformer),
        _calibrationEnd(ce ? ce : throw invalid_argument("calibration end is invalid")),
        _screenResolution(screenResolution)
{
}

CoordinateConverter::~CoordinateConverter()
{
    _remoteTransformer = _transformer;
    cout << "CoordinateConverter::~CoordinateConverter()" << endl;
}

void CoordinateConverter::putCoordinates(int x, int y)
{
    if (!_transformer.isReady()/*in calibration expression: transformer not ready and and calibration point exist*/)
    {
        /*
         * calibration process
         */
    }
    else
    {
        /**
         * in work
         */
        auto point = _transformer.convert(x, y);
        _mouseOutput(point.x, point.y, MouseButton::NO_BUTTON, MouseCommand::MOVE);
    }
}

void CoordinateConverter::calibrate()
{
    /*
     * image size
     * screen size
     */

    Size screenResolution = _screenResolution;
}
