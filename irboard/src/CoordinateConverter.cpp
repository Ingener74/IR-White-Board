/*
 * CoordinateConverter.cpp
 *
 *  Created on: Sep 9, 2014
 *      Author: pavel
 */

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
    _mouseOutput(point.x, point.y);
}
