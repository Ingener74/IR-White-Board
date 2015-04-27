/*
 * IrBoard.cpp
 *
 *  Created on: Apr 24, 2015
 *      Author: pavel
 */

#include <vector>
#include <iostream>
#include <chrono>
#include <future>

#include "ImageOutput.h"
#include "IrBoard.h"

namespace irboard {

using namespace std;

IrBoard::IrBoard(ImageOutput *imageOutput) {

    if (imageOutput) {
        struct RGB {
            uint8_t r, g, b;
        };
        size_t width = 400, height = 400;
        vector<RGB> data { width * height };

        RGB *p = data.data();
        for (size_t i = 0; i < data.size(); ++p, ++i) {
            *p = RGB { 1, 255, 1 };
        }

        imageOutput->updateImage(data.data(), width, height);
    }

    _stopThread = true;

    _thread = thread([this]() {
        while (true) {
            try {

                auto bar = promise<exception_ptr>();
                auto foo = bar.get_future();

                thread processor([&, this]{

                    try {
                        // Инициализация

                        cout << "Инициализация" << endl;

                        // Цикл
                        while(_stopThread){
                            cout << "Обработка" << endl;

                            this_thread::sleep_for(chrono::seconds(2));
                        }

                    } catch (exception const& e) {
                        bar.set_exception(current_exception());
                    }

                });

                foo.wait();

                if(foo.get())
                    rethrow_exception(foo.get());

            } catch (exception const &e) {
                cerr << e.what() << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
    });
}

IrBoard::~IrBoard() {
    _stopThread = false;
    _thread.join();
}

std::string IrBoard::getVersion() const {
    return "0.99.3";
}

} /* namespace irboard */
