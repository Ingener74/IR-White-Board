/*
 * CoordinateConverter.h
 *
 *  Created on: Sep 9, 2014
 *      Author: pavel
 */

#ifndef COORDINATECONVERTER_H_
#define COORDINATECONVERTER_H_

#include <functional>
#include <iostream>

#include <Transformer.h>
#include <RemoteVariable.h>

enum class MouseButton
{
    NO_BUTTON,
    LEFT,
    RIGHT,
    MIDDLE,
};
std::ostream& operator<<(std::ostream&, const MouseButton&);
enum class MouseCommand
{
    MOVE,
    UP,
    DOWN,
};
std::ostream& operator<<(std::ostream&, const MouseCommand&);

using MouseOutput      = std::function<void(int, int, MouseButton, MouseCommand)>;
using CalibrationEnd   = std::function<void()>;

class CoordinateConverter
{
public:
    CoordinateConverter(
            MouseOutput,
            CalibrationEnd,
            RemoteVariable<Transformer>  transformer,
            RemoteVariable<cv::Size>     screenResolution,
            RemoteVariable<cv::Size>     calibrationGridNodes);
    virtual ~CoordinateConverter();

    void putCoordinates(int x, int y);
    void calibrate();

private:
    MouseOutput _mouseOutput;
    CalibrationEnd _calibrationEnd;
    RemoteVariable<Transformer> _remoteTransformer;
    Transformer _transformer;
    std::vector<cv::Point> _calibrationPoints;
    RemoteVariable<cv::Size> _screenResolution;
    RemoteVariable<cv::Size> _calibrationGridNodes;

    static double distance(const cv::Point&, const cv::Point&);
    static bool isValidPoint(const std::vector<cv::Point>& points, const cv::Point& point, double invalidRadius);
};

#endif /* COORDINATECONVERTER_H_ */
