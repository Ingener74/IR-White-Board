/*
 * Transformator.h
 *
 *  Created on: Sep 5, 2014
 *      Author: pavel
 */

#ifndef TRANSFORMATOR_H_
#define TRANSFORMATOR_H_

#include <functional>

struct Transformer
{
    struct Coil
    {
        int x, y;
    };
    std::vector<Coil> _coils;
    int w, h;

    const Coil& getScreenCoordinates(const Coil& spotCoordinate);
};

using MouseOutput = std::function<void(int, int)>;
using CoilsLoader = std::function<Transformer()>;

class Transformator
{
public:
    Transformator(MouseOutput);
    virtual ~Transformator();

    void putCoordinates(int x, int y);

private:
    MouseOutput _mouseOutput;

    Transformer _transformer;
};

#endif /* TRANSFORMATOR_H_ */
