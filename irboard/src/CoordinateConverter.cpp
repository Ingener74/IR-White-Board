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
    _calibrationGridNodesCounts(calibrationGridNodes)
{
}

CoordinateConverter::~CoordinateConverter()
{
    _remoteTransformer = _transformer;
    cout << "CoordinateConverter::~CoordinateConverter()" << endl;
}

double CoordinateConverter::distance(const cv::Point& p1, const cv::Point& p2)
{
    return sqrt((p2.y - p1.y) * (p2.y - p1.y) + (p2.x - p1.x) * (p2.x - p1.x));
}

bool CoordinateConverter::isValidPoint(const std::vector<cv::Point>& points, const cv::Point& point, double invalidRadius)
{
    for (auto i : points)
        if (distance(i, point) < invalidRadius) return false;
    return true;
}

void CoordinateConverter::putCoordinates(int x, int y)
{
    if (!_transformer.isReady())
    {
        /*
         * calibration process
         */

        auto point = Point{ x, y };
        auto invalidRadius = 0.0;

        Size calibrationGridNodesCounts = _calibrationGridNodesCounts;
        auto validPointsCount = calibrationGridNodesCounts.width * calibrationGridNodesCounts.height;

        if (!isValidPoint(_sensorCalibrationPointsGrid, point, invalidRadius)) return;

        _sensorCalibrationPointsGrid.push_back(point);

        if (_sensorCalibrationPointsGrid.size() != validPointsCount) return;

        /*
         * calculate transformer
         */

        Size screenResolution = _screenResolution;
        for(int i = 0; i < calibrationGridNodesCounts.height; ++i){
            for(int j = 0; j < calibrationGridNodesCounts.width; ++j){
                auto pointOnScreen = Point{
                    (screenResolution.width  / (calibrationGridNodesCounts.width  - 1)) * j,
                    (screenResolution.height / (calibrationGridNodesCounts.height - 1)) * i};
                _screenCalibrationPointsGrid.push_back(pointOnScreen);
            }
        }

        /*
         * calibration end
         */
        _sensorCalibrationPointsGrid = vector<Point>{};
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

