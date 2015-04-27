/*
 * IrBoard.h
 *
 *  Created on: Apr 24, 2015
 *      Author: pavel
 */

#ifndef LIBIRBOARD_IRBOARD_H_
#define LIBIRBOARD_IRBOARD_H_

#ifdef SWIG
#else

#include <string>
#include <thread>
#include <atomic>

#endif

namespace irboard {

class IrBoard {
public:
    IrBoard(class ImageOutput *imageOutput = nullptr);

    virtual ~IrBoard();

    std::string getVersion() const;

private:
    std::thread _thread;
    std::atomic<bool> _stopThread;
};

} /* namespace irboard */

#endif /* LIBIRBOARD_IRBOARD_H_ */
