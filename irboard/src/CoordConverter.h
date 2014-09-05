

#ifndef _C_COORDINATETRANSFORM_
#define _C_COORDINATETRANSFORM_

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <string>
#include <vector>
#include <fstream>

//#include "matrix.h"

using namespace std;
using namespace cv;

enum E_CoordinateTransformationSystemStatus{
	E_ctssEMPTY,
	E_ctssONCALIBRATION,
	E_ctssREADY,
	E_ctssCALIBRATED
};

class C_CoordinateTransform
{
public:
							C_CoordinateTransform( 
								Size_<unsigned int>			A_rTransformationMatrixSize		= Size_<unsigned int>(),
								Size_<unsigned int>			A_rDisplayResolution			= Size_<unsigned int>(),
								Size_<unsigned int>			A_oMarkerPoints					= Size_<unsigned int>()
								);

							C_CoordinateTransform( 
								std::wstring				A_rFileName,
								Size_<unsigned int>			A_rDisplayResolution
								);

							~C_CoordinateTransform();

//							C_CoordinateTransform( C_CoordinateTransform&& A_rrTransformationMatrix );
//	C_CoordinateTransform&	                operator=( C_CoordinateTransform&& A_rrTransformationMatrix );

	void                                    OnLeftDown( Point2f A_rPoint );

	E_CoordinateTransformationSystemStatus  GetStatus();

	Point2f									GetCurrentDisplayPoint();
	unsigned int							GetNumberOfDisplayPoints();

	bool                                    CalcTransformationMatrix();

	Point2i									GetCoordinate( Point2f A_rPoint );

	Mat										getImageRepresentation();

	bool                                    SaveTransformationMatrix( std::wstring fileName );
	bool                                    LoadTransformationMatrix( std::wstring A_rFileName );

private:
							C_CoordinateTransform( C_CoordinateTransform& A_rTransformationMatrix );
	C_CoordinateTransform&	operator=( C_CoordinateTransform& A_rTransformationMatrix );

	class Private;
	Private *p;
};

#endif
