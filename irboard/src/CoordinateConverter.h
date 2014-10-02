/*
 * CoordinateConverter.h
 *
 *  Created on: Sep 9, 2014
 *      Author: pavel
 */

#ifndef COORDINATECONVERTER_H_
#define COORDINATECONVERTER_H_

#include <Transformer.h>
#include <functional>
#include <iostream>

enum class MouseButton
{
    NO_BUTTON, LEFT, RIGHT, MIDDLE,
};
std::ostream& operator<<(std::ostream& out, const MouseButton& rho);
enum class MouseCommand
{
    MOVE, UP, DOWN,
};
std::ostream& operator<<(std::ostream& out, const MouseCommand& rho);

using MouseOutput      = std::function<void(int, int, MouseButton, MouseCommand)>;
using CoilsLoader      = std::function<Transformer()>;
using CoilsSaver       = std::function<void(const Transformer&)>;
using CalibrationEnd   = std::function<void()>;

class CoordinateConverter
{
public:
    CoordinateConverter(MouseOutput, CoilsLoader, CoilsSaver, CalibrationEnd);
    virtual ~CoordinateConverter();

    void putCoordinates(int x, int y);
    void calibrate();

private:
    MouseOutput _mouseOutput;
    CoilsSaver _coilsSaver;
    Transformer _transformer;
    CalibrationEnd _calibrationEnd;
    std::vector<cv::Point> _calibrationPoints;
};

#endif /* COORDINATECONVERTER_H_ */
