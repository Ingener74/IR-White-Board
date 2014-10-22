/*
 * Transformer.cpp
 *
 *  Created on: Sep 9, 2014
 *      Author: pavel
 */

#include <iostream>

#include <Transformer.h>

using namespace std;
using namespace cv;

Transformer::Transformer(int width, int coilsCount, CoilsFiller cf) :
        _coils(coilsCount),
        _width(width)
{
    for (int i = 0; i < coilsCount; ++i)
        _coils[i] = cf(i);
}

Transformer::Transformer(): Transformer(0, 0, [](int i){ return Point{}; })
{
}

Transformer::~Transformer()
{
    cout << "Transformer::~Transformer()" << endl;
}

Point Transformer::convert(int x, int y) const
{
    return _coils[y * _width + x];
}

bool Transformer::isReady() const
{
    return !_coils.empty() && _width;
}

const std::vector<cv::Point>& Transformer::getCoils() const
{
    return _coils;
}

int Transformer::getWidth() const
{
    return _width;
}

