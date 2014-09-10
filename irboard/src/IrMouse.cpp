/*
 * IrMouse.cpp
 *
 *  Created on: Sep 10, 2014
 *      Author: pavel
 */

#include <iostream>

#include <opencv2/highgui/highgui.hpp>

#include <CoordinateConverter.h>
#include <IrCameraProcessor.h>
#include <IrMouse.h>
#include <Platform.h>

using namespace std;
using namespace std::placeholders;
using namespace cv;

IrMouse::IrMouse(ImageOutput imageOut)
{
    _thread = thread([imageOut]()
    {
        for(;;)
        {
            try
            {
                auto platform = make_shared<Platform>();

                auto coordConverter = make_shared<CoordinateConverter>(
                    bind(&Platform::mouseCommand, platform.get(), _1, _2, _3, _4),
                    bind(&Platform::loadTransformer, platform.get()),
                    bind(&Platform::saveTransformer, platform.get(), _1)
                );

                auto irCameraProcessor = make_shared<IrCameraProcessor>(
                    bind(&Platform::createVideoSource, platform.get()),
                    bind(&CoordinateConverter::putCoordinates, coordConverter.get(), _1, _2),
                    imageOut
                );
            }
            catch (exception const & e)
            {
                cerr << "IrMouse error: " << e.what() << endl;
            }
        }
    });
    _thread.detach();
}

IrMouse::~IrMouse()
{
    _thread = thread();
}

