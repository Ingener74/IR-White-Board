/*
 * main.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: pavel
 */

#include <iostream>

#include <boost/program_options.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

/*
enum
{
    EVENT_MOUSEMOVE      =0,
    EVENT_LBUTTONDOWN    =1,
    EVENT_RBUTTONDOWN    =2,
    EVENT_MBUTTONDOWN    =3,
    EVENT_LBUTTONUP      =4,
    EVENT_RBUTTONUP      =5,
    EVENT_MBUTTONUP      =6,
    EVENT_LBUTTONDBLCLK  =7,
    EVENT_RBUTTONDBLCLK  =8,
    EVENT_MBUTTONDBLCLK  =9
};

enum
{
    EVENT_FLAG_LBUTTON   =1,
    EVENT_FLAG_RBUTTON   =2,
    EVENT_FLAG_MBUTTON   =4,
    EVENT_FLAG_CTRLKEY   =8,
    EVENT_FLAG_SHIFTKEY  =16,
    EVENT_FLAG_ALTKEY    =32
};
*/

void mouseCallback(int event, int x, int y, int flags, void* userdata)
{
    auto callback = *static_cast<function<void(Point)>*>(userdata);

    if (event == EVENT_LBUTTONDOWN && flags == EVENT_FLAG_LBUTTON)
    {
        callback(Point(x, y));
    }
}

int main(int argc, char **argv)
{
    namespace po = boost::program_options;

    try
    {
        po::options_description od("Help");

        od.add_options()
                ("help,h", "Show help")
                ("image,i", po::value<string>(), "Path to test file");

        po::variables_map vm;

        po::store(po::parse_command_line(argc, argv, od), vm);
        notify(vm);

        if (vm.count("help"))
        {
            od.print(cout);
            return 0;
        }

        if(!vm.count("image")) throw runtime_error("set image file");

        /*
         * 1. show monitor image
         * 2. listen mouse movement
         * 3. create faik test ir video with calibration and work
         */

        Mat image = imread(vm["image"].as<string>());
        if(image.empty()) throw runtime_error("image is empty");

        cout << "image size " << image.size() << endl;

        VideoWriter vw;



        while (true)
        {
            imshow("ir-tester", image);

            std::function<void(Point)> callback = [](Point p){
                cout << "mouse callback " << p << endl;
            };

            setMouseCallback("ir-tester", mouseCallback, &callback);

            if (waitKey(1000 / 30) == 27)
            {
                return 0;
            }
        }

        return 0;
    }
    catch (exception const & e)
    {
        cerr << e.what() << endl;
        return 1;
    }
}
