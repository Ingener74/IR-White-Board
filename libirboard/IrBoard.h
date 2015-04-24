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
#endif

namespace irboard {

class IrBoard {
public:
    IrBoard();
    virtual ~IrBoard();

    std::string getVersion() const;
};

} /* namespace irboard */

#endif /* LIBIRBOARD_IRBOARD_H_ */
