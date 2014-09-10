/*
 * CoordinateConverter.cpp
 *
 *  Created on: Sep 9, 2014
 *      Author: pavel
 */

#include <iostream>

#include <CoordinateConverter.h>

using namespace std;

CoordinateConverter::CoordinateConverter(MouseOutput mo, CoilsLoader cl, CoilsSaver cs) :
        _mouseOutput(mo ? mo : throw invalid_argument("mouse output is empty")),
        _coilsSaver(cs ? cs : throw invalid_argument("coils saver is empty")),
        _transformer((cl ? cl : throw invalid_argument("coils loader is empty"))())
{
}

CoordinateConverter::~CoordinateConverter()
{
    _coilsSaver(_transformer);
}

void CoordinateConverter::putCoordinates(int x, int y)
{
    auto point = _transformer.convert(x, y);
    _mouseOutput(point.x, point.y, MouseButton::NO_BUTTON, MouseCommand::MOVE);
}

ostream& operator<<(std::ostream& out, const MouseButton& rho)
{
    static string mb[]
    { "No Button", "Left", "Right", "Middle", };
    cout << mb[static_cast<int>(rho)];
    return out;
}

ostream& operator<<(std::ostream& out, const MouseCommand& rho)
{
    static string mc[]
    { "Move", "Up", "Down", };
    cout << mc[static_cast<int>(rho)];
    return out;
}

