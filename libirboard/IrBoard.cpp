/*
 * IrBoard.cpp
 *
 *  Created on: Apr 24, 2015
 *      Author: pavel
 */

#include <vector>
#include <iostream>
#include <chrono>

#include "ImageOutput.h"
#include "IrBoard.h"

namespace irboard {

    using namespace std;

    IrBoard::IrBoard(ImageOutput *imageOutput) {

        struct RGB {
            uint8_t r, g, b;
        };
        size_t width = 400, height = 400;
        vector<RGB> data{width * height};

        RGB *p = data.data();
        for (size_t i = 0; i < data.size(); ++p, ++i) {
            *p = RGB{1, 255, 1};
        }

        imageOutput->updateImage(data.data(), width, height);

        _stopThread = false;
        _thread = thread([](){
            while (true) {
                try {

                    break;

                } catch (exception const &e) {
                    cerr << e.what() << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                }
            }
        });
    }

    IrBoard::~IrBoard() {
        _stopThread = true;
        _thread.join();
    }

    std::string IrBoard::getVersion() const {
        return "0.99.3";
    }

} /* namespace irboard */
