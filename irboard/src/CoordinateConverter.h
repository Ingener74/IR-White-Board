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

using MouseOutput = std::function<void(int, int, MouseButton, MouseCommand)>;
using CoilsLoader = std::function<Transformer()>;
using CoilsSaver  = std::function<void(const Transformer&)>;

class CoordinateConverter
{
public:
    CoordinateConverter(MouseOutput, CoilsLoader, CoilsSaver);
    virtual ~CoordinateConverter();


    void putCoordinates(int x, int y);

private:
    MouseOutput _mouseOutput;
    CoilsSaver _coilsSaver;
    Transformer _transformer;
};

#endif /* COORDINATECONVERTER_H_ */
