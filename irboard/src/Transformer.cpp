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
        _coils(coilsCount ? coilsCount : throw invalid_argument("coils must have more than zero hanks")),
        _width(width ? width : throw invalid_argument("transformer width can't be zero"))
{
    for (int i = 0; i < coilsCount; ++i)
        _coils[i] = cf(i);
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
    return (_coils.empty() || !_width);
}

const std::vector<cv::Point>& Transformer::getCoils() const
{
    return _coils;
}

int Transformer::getWidth() const
{
    return _width;
}

