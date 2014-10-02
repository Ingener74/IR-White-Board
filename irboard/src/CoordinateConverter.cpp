/*
 * CoordinateConverter.cpp
 *
 *  Created on: Sep 9, 2014
 *      Author: pavel
 */

#include <iostream>

#include <CoordinateConverter.h>

using namespace std;

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

CoordinateConverter::CoordinateConverter(MouseOutput mo, CoilsLoader cl, CoilsSaver cs, CalibrationEnd ce) :
        _mouseOutput(mo ? mo : throw invalid_argument("mouse output is invalid")),
        _coilsSaver(cs ? cs : throw invalid_argument("coils saver is invalid")),
        _transformer((cl ? cl : throw invalid_argument("coils loader is invalid"))()),
        _calibrationEnd(ce ? ce : throw invalid_argument("calibration end is invalid"))
{
}

CoordinateConverter::~CoordinateConverter()
{
    _coilsSaver(_transformer);
    cout << "CoordinateConverter::~CoordinateConverter()" << endl;
}

void CoordinateConverter::putCoordinates(int x, int y)
{
    if (false /*in calibration expression*/)
    {
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
}
