

#ifndef _C_RAWMOUSE_
#define _C_RAWMOUSE_

#include <algorithm>
#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;

float Distance(Point2f p1, Point2f p2);

typedef void (*pfn_RawMouseOnLeftDown  )( Point2f A_rPoint );
typedef void (*pfn_RawMouseOnLeftUp    )( Point2f A_rPoint );

typedef void (*pfn_RawMouseOnMove      )( Point2f A_rPoint );

typedef void (*pfn_RawMouseOnRightDown )( Point2f A_rPoint );
typedef void (*pfn_RawMouseOnRightUp   )( Point2f A_rPoint );

enum E_RawMouseButtonState{
	E_RAWMOUSEEMPTY,

	E_LEFTDOWN,
	E_LEFTUP,

	E_RIGHTDOWN,
	E_RIGHTUP,

	E_MOVE
};

class C_RawMouse
{
public:
	C_RawMouse();
	~C_RawMouse();
	
//	            C_RawMouse( C_RawMouse&& A_rrRawMouse );
//	C_RawMouse&	operator=( C_RawMouse&& A_rrRawMouse );

	void Process( Point2f A_rPoint, bool A_bExisting, float A_fSquareOfSpot );

	void SetLeftDownCallBack(  pfn_RawMouseOnLeftDown A_pLeftDownCallBack );
	void SetLeftUpCallBack(    pfn_RawMouseOnLeftUp A_pLeftUpCallBack );

	void SetMoveCallBack(      pfn_RawMouseOnMove A_pMoveCallBack );

	void SetRightDownCallBack( pfn_RawMouseOnRightDown A_pRightDownCallBack );
	void SetRightUpCallBack(   pfn_RawMouseOnRightUp A_pRightUpCallBack );

private:
					C_RawMouse( C_RawMouse& A_rRawMouse );
	C_RawMouse&		operator=( C_RawMouse& A_rRawMouse );

	class Private;
	Private *p;
};

#endif
