

#include "C_CoordinateTransform.h"
#include "C_RawMouse.h"

void PointOnLine( Point2f& out, Point2f& p1, Point2f& p2, float k){
	out = Point2f(
			k*(p2.x - p1.x) + p1.x,
			k*(p2.y - p1.y) + p1.y
			);
}

//////////////////////////////////////////////////////////////////////////
class C_CoordinateTransform::Private
{
public:
	matrix<Point2f>							m_oDisplayPoints;			/*corner points on screen*/

	matrix<Point2f>							m_oImagePoints;				/*points calculated after calibration*/

	matrix<Point2i>							m_oTransformationMatrix;	/*main transformation coordinate matrix*/

	Size_<unsigned int>						m_oMarkerPoints;			/*number of calibration points on horizontal and vertical*/

	long                                    m_lPointCounter;

	Size_<unsigned int>						m_oDisplayResolution;

	E_CoordinateTransformationSystemStatus  m_oCoordinateTransformationSystemStatus;

	Private():
		m_oDisplayPoints(),
		m_oImagePoints(),
		m_oTransformationMatrix(),
		m_oMarkerPoints(),
		m_lPointCounter(0),
		m_oDisplayResolution(),
		m_oCoordinateTransformationSystemStatus(E_ctssEMPTY)
		{}
};

//////////////////////////////////////////////////////////////////////////
/*
C_CoordinateTransform::C_CoordinateTransform()
	: p(new Private)
{
}
*/

//////////////////////////////////////////////////////////////////////////
C_CoordinateTransform::C_CoordinateTransform( 
	Size_<unsigned int>			A_rTransformationMatrixSize	,
	Size_<unsigned int>			A_rDisplayResolution		,
	Size_<unsigned int>			A_oMarkerPoints
	)
	: p(new Private)
{
	p->m_oDisplayResolution = A_rDisplayResolution;
	p->m_oMarkerPoints      = A_oMarkerPoints;

	p->m_oDisplayPoints = matrix<Point2f>( p->m_oMarkerPoints );
	p->m_oImagePoints	= matrix<Point2f>( p->m_oMarkerPoints );

	for ( unsigned int i = 0; i < p->m_oMarkerPoints.height; ++i )
	{
		for ( unsigned int j = 0; j < p->m_oMarkerPoints.width; ++j )
		{
			p->m_oDisplayPoints.get_element(j, i) = Point2f(
					(float)( (A_rDisplayResolution.width  / (p->m_oMarkerPoints.width  - 1))*j ),
					(float)( (A_rDisplayResolution.height / (p->m_oMarkerPoints.height - 1))*i )
					);
		}
	}
	p->m_oTransformationMatrix = matrix<Point2i>( A_rTransformationMatrixSize );
}

//////////////////////////////////////////////////////////////////////////
C_CoordinateTransform::C_CoordinateTransform( std::wstring A_rFileName, Size_<unsigned int> A_rDisplayResolution )
	: p(new Private)
{
	if ( LoadTransformationMatrix(A_rFileName) )
	{
		if ( p->m_oDisplayResolution != A_rDisplayResolution )
		{
			p = new Private();

			p->m_oCoordinateTransformationSystemStatus = E_ctssEMPTY;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
C_CoordinateTransform::~C_CoordinateTransform()
{
	delete p;
}

//////////////////////////////////////////////////////////////////////////
//C_CoordinateTransform::C_CoordinateTransform( C_CoordinateTransform&& A_rrTransformationMatrix )
//	: p(A_rrTransformationMatrix.p)
//{
//	A_rrTransformationMatrix.p = nullptr;
//}
//
////////////////////////////////////////////////////////////////////////////
//C_CoordinateTransform& C_CoordinateTransform::operator=( C_CoordinateTransform&& A_rrTransformationMatrix )
//{
//	std::swap(p, A_rrTransformationMatrix.p);
//	return *this;
//}

//////////////////////////////////////////////////////////////////////////
#include <fstream>

void C_CoordinateTransform::OnLeftDown( Point2f A_rPoint )
{
	if ( p->m_lPointCounter < (long)p->m_oImagePoints.matrix_data.size() )
	{
		for ( long i = 0; i < p->m_lPointCounter; ++i )
		{
			if ( Distance(p->m_oImagePoints.matrix_data[i], A_rPoint) < (float)(p->m_oTransformationMatrix.matrix_size.height / 20) ) return;
		}
		p->m_oImagePoints.matrix_data[p->m_lPointCounter] = A_rPoint;
		p->m_lPointCounter++;
	}
}

//////////////////////////////////////////////////////////////////////////
Point2f C_CoordinateTransform::GetCurrentDisplayPoint()
{
	return p->m_oDisplayPoints.matrix_data[p->m_lPointCounter];
}

//////////////////////////////////////////////////////////////////////////
E_CoordinateTransformationSystemStatus C_CoordinateTransform::GetStatus()
{
	E_CoordinateTransformationSystemStatus res = E_ctssEMPTY;
	if ( p->m_oCoordinateTransformationSystemStatus == E_ctssREADY											) res = E_ctssREADY;
	else if ( p->m_oCoordinateTransformationSystemStatus == E_ctssCALIBRATED								) res = E_ctssCALIBRATED;
	else if ( p->m_lPointCounter == 0																		) res = E_ctssEMPTY;
	else if ( p->m_lPointCounter >  0 && p->m_lPointCounter < (long)p->m_oImagePoints.matrix_data.size()	) res = E_ctssONCALIBRATION;
	else if ( p->m_lPointCounter == (long)p->m_oImagePoints.matrix_data.size()								) res = E_ctssREADY;

	return res;
}

//////////////////////////////////////////////////////////////////////////
bool C_CoordinateTransform::CalcTransformationMatrix()
{
	for ( unsigned int j = 0; j < p->m_oMarkerPoints.height - 1; ++j )
	{
		for ( unsigned int i = 0; i < p->m_oMarkerPoints.width - 1; ++i )
		{
			Point2f oIP1 = p->m_oImagePoints.get_element(i,     j);
			Point2f oIP2 = p->m_oImagePoints.get_element(i + 1, j);
			Point2f oIP3 = p->m_oImagePoints.get_element(i,     j + 1);
			Point2f oIP4 = p->m_oImagePoints.get_element(i + 1, j + 1);

			Point2f oDP1 = p->m_oDisplayPoints.get_element(i,		j);
			Point2f oDP2 = p->m_oDisplayPoints.get_element(i + 1,	j);
			Point2f oDP3 = p->m_oDisplayPoints.get_element(i,		j + 1);
			Point2f oDP4 = p->m_oDisplayPoints.get_element(i + 1,	j + 1);

			long lHE = (p->m_oTransformationMatrix.matrix_size.height / (p->m_oMarkerPoints.height - 1));
			long lWE = (p->m_oTransformationMatrix.matrix_size.width  / (p->m_oMarkerPoints.width  - 1));
			for ( long lY = 0; lY < lHE; ++lY )
			{
				for ( long lX = 0; lX < lWE; ++lX )
				{
					Point2f oIPy1, oIPy2;
					PointOnLine(oIPy1, oIP1, oIP3, (float)lY / (float)lHE );
					PointOnLine(oIPy2, oIP2, oIP4, (float)lY / (float)lHE );

					Point2f oIP;
					PointOnLine(oIP, oIPy1, oIPy2, (float)lX / (float)lWE );

					Point2f oDPy1, oDPy2;
					PointOnLine(oDPy1, oDP1, oDP3, (float)lY / (float)lHE );
					PointOnLine(oDPy2, oDP2, oDP4, (float)lY / (float)lHE );

					Point2f oDP;
					PointOnLine(oDP, oDPy1, oDPy2, (float)lX / (float)lWE );

					p->m_oTransformationMatrix.set_element((unsigned int)oIP.x, (unsigned int)oIP.y, Point2i( (long)oDP.x, (long)oDP.y ));
				}
			}
		}
	}

	p->m_oCoordinateTransformationSystemStatus = E_ctssCALIBRATED;

	return true;
}

//////////////////////////////////////////////////////////////////////////
Point2i C_CoordinateTransform::GetCoordinate( Point2f A_rPoint )
{

	Point2i oPoint((long)A_rPoint.x, (long)A_rPoint.y);
	return p->m_oTransformationMatrix.get_element(oPoint.x, oPoint.y);
}

//////////////////////////////////////////////////////////////////////////
Mat C_CoordinateTransform::getImageRepresentation() {
	Mat oDB3(p->m_oTransformationMatrix.matrix_size, CV_8UC3, Scalar(0));

	for(int y=0;y<oDB3.rows;++y){
		for(int x=0;x<oDB3.cols;++x){
			oDB3.at<Vec3b>(y, x) = Vec3b(
					(unsigned char)(255.0f*(float)p->m_oTransformationMatrix.matrix_data[y*oDB3.cols+x].x / (float)p->m_oDisplayResolution.width),
					(unsigned char)(255.0f*(float)p->m_oTransformationMatrix.matrix_data[y*oDB3.cols+x].y / (float)p->m_oDisplayResolution.height),
					0);
		}
	}
	return oDB3;
}

//////////////////////////////////////////////////////////////////////////
bool C_CoordinateTransform::SaveTransformationMatrix( std::wstring fileName )
{
	bool bResult = false;
	try
	{
		if ( p->m_oCoordinateTransformationSystemStatus == E_ctssCALIBRATED )
		{
			std::ofstream oFile;
			std::string fileN(fileName.begin(), fileName.end());
			oFile.open(fileN.c_str(), std::ios::binary);

			if ( oFile )
			{
				oFile.write((char*)&p->m_oDisplayResolution.width,  sizeof(unsigned int));
				oFile.write((char*)&p->m_oDisplayResolution.height, sizeof(unsigned int));

				oFile.write((char*)&p->m_oTransformationMatrix.matrix_size.width,  sizeof(unsigned int) );
				oFile.write((char*)&p->m_oTransformationMatrix.matrix_size.height, sizeof(unsigned int) );

				oFile.write((char*)p->m_oTransformationMatrix.matrix_data.data(),  p->m_oTransformationMatrix.matrix_data.size() * sizeof(Point2i));
			}
		}

		bResult = true;
	}
	catch ( bool bError )
	{
		bResult = bError;
	}
	return bResult;
}

unsigned int C_CoordinateTransform::GetNumberOfDisplayPoints() {
	return p->m_oDisplayPoints.matrix_data.size();
}

//////////////////////////////////////////////////////////////////////////
bool C_CoordinateTransform::LoadTransformationMatrix( std::wstring A_rFileName )
{
	bool bResult = false;
	try
	{
		std::ifstream oFile;
		std::string fileN(A_rFileName.begin(), A_rFileName.end());
		oFile.open(fileN.c_str(), std::ios::binary);
		if ( oFile )
		{
			Size_<unsigned int>	displayRes;

			oFile.read((char*)&displayRes.width,  sizeof(unsigned int));
			oFile.read((char*)&displayRes.height, sizeof(unsigned int));

			if ( displayRes == Size_<unsigned int>(0, 0) )
			{
				p->m_oCoordinateTransformationSystemStatus = E_ctssEMPTY;
				throw false;
			}

			p->m_oDisplayResolution = displayRes;

			Size_<unsigned int> size;

			oFile.read((char*)&size.width,  sizeof(unsigned int));
			oFile.read((char*)&size.height, sizeof(unsigned int));

			if ( size == Size_<unsigned int>(0, 0) )
			{
				p->m_oCoordinateTransformationSystemStatus = E_ctssEMPTY;
				throw false;
			}

			p->m_oTransformationMatrix = matrix<Point2i>(size);

			oFile.read( (char*)p->m_oTransformationMatrix.matrix_data.data(), p->m_oTransformationMatrix.matrix_data.size() * sizeof(Point2i) );

			p->m_oCoordinateTransformationSystemStatus = E_ctssCALIBRATED;
		}
		else
		{
			p->m_oCoordinateTransformationSystemStatus = E_ctssEMPTY;
			throw false;
		}

		bResult = true;
	}
	catch ( bool bError )
	{
		bResult = bError;
	}
	return bResult;
}



