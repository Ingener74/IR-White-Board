/*
 * CoordinateConverter.cpp
 *
 *  Created on: Sep 9, 2014
 *      Author: pavel
 */

#include <map>
#include <string>
#include <iostream>

#include <CoordinateConverter.h>

using namespace std;
using namespace cv;

ostream& operator<<(ostream& out, const MouseButton& rho)
{
    static map<MouseButton, string> buttons{
        {MouseButton::NO_BUTTON, "No Button"},
        {MouseButton::LEFT,      "Left"},
        {MouseButton::RIGHT,     "Right"},
        {MouseButton::MIDDLE,    "Middle"}
    };
    out << buttons[rho];
    return out;
}

ostream& operator<<(ostream& out, const MouseCommand& rho)
{
    static map<MouseCommand, string> commands{
        {MouseCommand::MOVE, "Move"},
        {MouseCommand::UP,   "Up"},
        {MouseCommand::DOWN, "Down"}
    };
    out << commands[rho];
    return out;
}

CoordinateConverter::CoordinateConverter
(
    MouseOutput                  mo,
    CalibrationEnd               ce,
    RemoteVariable<Transformer>  transformer,
    RemoteVariable<cv::Size>     screenResolution,
    RemoteVariable<cv::Size>     calibrationGridNodes
):
    _mouseOutput(mo ? mo : throw invalid_argument("mouse output is invalid")),
    _calibrationEnd(ce ? ce : throw invalid_argument("calibration end is invalid")),
    _remoteTransformer(transformer),
    _transformer(_remoteTransformer),
    _screenResolution(screenResolution),
    _calibrationGridNodes(calibrationGridNodes)
{
}

CoordinateConverter::~CoordinateConverter()
{
    _remoteTransformer = _transformer;
    cout << "CoordinateConverter::~CoordinateConverter()" << endl;
}

double CoordinateConverter::distance(const cv::Point& point_, const cv::Point& point_1)
{
    return sqrt((point_1.y - point_.y)*(point_1.y - point_.y) +
            (point_1.x - point_.x)*(point_1.x - point_.x));
}

bool CoordinateConverter::isValidPoint(const std::vector<cv::Point>& points, const cv::Point& point, double invalidRadius)
{
    for (auto i : points)
        if (distance(i, point) < invalidRadius) return false;
    return true;
}

void CoordinateConverter::putCoordinates(int x, int y)
{
    if (!_calibrationPoints.empty())
    {
        /*
         * calibration process
         */

        auto point = Point{ x, y };
        auto invalidRadius = 0.0;

        Size calibrationGridNodes = _calibrationGridNodes;
        auto validPointsCount = calibrationGridNodes.width * calibrationGridNodes.height;

        if (!isValidPoint(_calibrationPoints, point, invalidRadius)) return;

        _calibrationPoints.push_back(point);

        if (_calibrationPoints.size() != validPointsCount) return;

        /*
         * calculate transformer
         */

        /*
         * calibration end
         */
        _calibrationPoints = vector<Point>{};
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

    Size imageSize = Size{};
}

