/*
 * Transformer.cpp
 *
 *  Created on: Sep 9, 2014
 *      Author: pavel
 */

#include <Transformer.h>

using namespace std;
using namespace cv;

Transformer::Transformer(int width, int coilsCount, CoilsFiller cf) :
        _coils(!coilsCount ? coilsCount : throw invalid_argument("coils count can't be zero")),
        _width(!width ? width : throw invalid_argument("transformer width can't be zero"))
{
    for (int i = 0; i < coilsCount; ++i)
        _coils[i] = cf(i);
}

Point Transformer::convert(int x, int y)
{
    return _coils[y * _width + x];
}
