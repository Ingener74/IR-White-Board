

#ifndef _C_DISPLAYMOUSE_
#define _C_DISPLAYMOUSE_

#include <windows.h>
//#include <S_Point.h>
//#include <S_Size.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;

void DisplayMouseLeftDown	( Point A_rCursorPoint, Size_<unsigned int> A_rDisplayResolution );
void DisplayMouseLeftUp		( Point A_rCursorPoint, Size_<unsigned int> A_rDisplayResolution );

void DisplayMouseMove		( Point A_rCursorPoint, Size_<unsigned int> A_rDisplayResolution );

void DisplayMouseRightDown	( Point A_rCursorPoint, Size_<unsigned int> A_rDisplayResolution );
void DisplayMouseRightUp	( Point A_rCursorPoint, Size_<unsigned int> A_rDisplayResolution );

#endif
