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

map<int, string> events_{
    {EVENT_MOUSEMOVE    , "EVENT_MOUSEMOVE"},
    {EVENT_LBUTTONDOWN  , "EVENT_LBUTTONDOWN"},
    {EVENT_RBUTTONDOWN  , "EVENT_RBUTTONDOWN"},
    {EVENT_MBUTTONDOWN  , "EVENT_MBUTTONDOWN"},
    {EVENT_LBUTTONUP    , "EVENT_LBUTTONUP"},
    {EVENT_RBUTTONUP    , "EVENT_RBUTTONUP"},
    {EVENT_MBUTTONUP    , "EVENT_MBUTTONUP"},
    {EVENT_LBUTTONDBLCLK, "EVENT_LBUTTONDBLCLK"},
    {EVENT_RBUTTONDBLCLK, "EVENT_RBUTTONDBLCLK"},
    {EVENT_MBUTTONDBLCLK, "EVENT_MBUTTONDBLCLK"},
};

map<int, string> flags_{
    {EVENT_FLAG_LBUTTON , "EVENT_FLAG_LBUTTON"},
    {EVENT_FLAG_RBUTTON , "EVENT_FLAG_RBUTTON"},
    {EVENT_FLAG_MBUTTON , "EVENT_FLAG_MBUTTON"},
    {EVENT_FLAG_CTRLKEY , "EVENT_FLAG_CTRLKEY"},
    {EVENT_FLAG_SHIFTKEY, "EVENT_FLAG_SHIFTKEY"},
    {EVENT_FLAG_ALTKEY  , "EVENT_FLAG_ALTKEY"},
};

void mouseCallback(int event, int x, int y, int flags, void* userdata)
{
    auto callback = *static_cast<function<void(Point)>*>(userdata);

    cout << events_[event] << ", " << flags << endl;

    if (event == EVENT_LBUTTONDOWN || (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)))
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

        VideoWriter vw{"test.mpg", CV_FOURCC('M','J','P','G'), 30, Size{640, 480}};

        if(!vw.isOpened()) throw runtime_error("video writer not ready");

        Point fakeIr{-1, -1};

        while (true)
        {
            cout << "begin" << endl;
            std::function<void(Point)> callback = [&fakeIr](Point p){
                cout << "mouse callback " << p << endl;
                fakeIr = p;
            };

            imshow("ir-tester", image);
            setMouseCallback("ir-tester", mouseCallback, &callback);

            if ( waitKey(1000 / 30) == 27 ) return 0;

            Mat blackImage{480, 640, CV_8UC3, Scalar{0, 0, 0}};

//            stringstream ss;
//            ss << fakeIr;
//            putText(blackImage, ss.str(), Point{10, 20}, FONT_HERSHEY_PLAIN, 1, Scalar{255,255,0});

            circle(blackImage, fakeIr, 3, Scalar{255,255,255}, -1);

            vw << blackImage;

            imshow("fake camera image", blackImage);

            fakeIr = Point{-1, -1};
            cout << "fake ir " << fakeIr << endl;
        }

        vw.release();

        return 0;
    }
    catch (exception const & e)
    {
        cerr << e.what() << endl;
        return 1;
    }
}
