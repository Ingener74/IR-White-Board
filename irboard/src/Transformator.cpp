/*
 * Transformator.cpp
 *
 *  Created on: Sep 5, 2014
 *      Author: pavel
 */

#include <stdexcept>

#include <Transformator.h>

using namespace std;

Transformator::Transformator(MouseOutput mo) :
        _mouseOutput(mo ? mo : throw invalid_argument("mouse output is empty"))
{
}

Transformator::~Transformator()
{
}

void Transformator::putCoordinates(int x, int y)
{
}
