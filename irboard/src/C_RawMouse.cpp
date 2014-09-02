

#include "C_RawMouse.h"

//#include "tools.h"

enum	E_RawMouseEvent{
	E_rmeNULL,
	E_rmeDOWN,
	E_rmeUP
};

struct S_RawMouseEvent
{
	Point2f				m_oPoint;
	E_RawMouseEvent		m_oMouseEvent;
	long				m_lTimeFromPreviousEvent;

	S_RawMouseEvent( Point2f A_oPoint = Point2f(), E_RawMouseEvent A_oMouseEvent = E_rmeNULL, long A_lTimeFromPreviousEvent = 0)
		: m_oPoint(A_oPoint), m_oMouseEvent(A_oMouseEvent), m_lTimeFromPreviousEvent(A_lTimeFromPreviousEvent){}
};

float Distance(Point2f p1, Point2f p2){
	return sqrt( (p2.y - p1.y)*(p2.y - p1.y)  -  (p2.x - p1.x)*(p2.x - p1.x) );
}

//////////////////////////////////////////////////////////////////////////
class C_RawMouse::Private
{
public:
	Private():
		oRawCursorPoint(Point2f()),
		oRawMouseState(E_RAWMOUSEEMPTY), 

		bPreviousExistingState(false),

		oLeftDownCallBack( 0 ),
		oLeftUpCallBack(0),

		oMoveCallBack(0),

		oRightDownCallBack(0),
		oRightUpCallBack(0),

		m_lRightClickCounter(0),
		m_oRightClickPoint(),
		m_bRightBlocker(false),

		m_lDoubleClickCounter(0),
		m_oDoubleClickPoint(),
		m_bDoubleClickActiveCounter(false),

		m_oMouseEventHistory(3),
		m_lBetweenEventCounter(0)
		{}

	Point2f							oRawCursorPoint;
	E_RawMouseButtonState			oRawMouseState;

	bool							bPreviousExistingState;

	pfn_RawMouseOnLeftDown			oLeftDownCallBack;
	pfn_RawMouseOnLeftUp			oLeftUpCallBack;

	pfn_RawMouseOnMove				oMoveCallBack;

	pfn_RawMouseOnRightDown			oRightDownCallBack;
	pfn_RawMouseOnRightUp			oRightUpCallBack;

	long							m_lRightClickCounter;
	Point2f							m_oRightClickPoint;
	bool							m_bRightBlocker;

	long							m_lDoubleClickCounter;
	Point2f							m_oDoubleClickPoint;
	bool							m_bDoubleClickActiveCounter;

	std::vector<S_RawMouseEvent>	m_oMouseEventHistory;
	long							m_lBetweenEventCounter;
};

//////////////////////////////////////////////////////////////////////////
C_RawMouse::C_RawMouse(): p(new Private)
{

}

//////////////////////////////////////////////////////////////////////////
//C_RawMouse::C_RawMouse( C_RawMouse&& A_rrRawMouse ): p(A_rrRawMouse.p)
//{
//	A_rrRawMouse.p = nullptr;
//}
//
////////////////////////////////////////////////////////////////////////////
//C_RawMouse& C_RawMouse::operator=( C_RawMouse&& A_rrRawMouse )
//{
//	std::swap(p, A_rrRawMouse.p);
//	return *this;
//}

//////////////////////////////////////////////////////////////////////////
C_RawMouse::~C_RawMouse()
{
	delete p;
}

//////////////////////////////////////////////////////////////////////////
void C_RawMouse::Process( Point2f A_rPoint, bool A_bExisting, float A_fSquareOfSpot )
{
	/*засекаем позицию при каждом нажатии и отпускании вспышки

	если одно нажатие и отпукание произошло в одном месте это щелкок левой кнопкой

	если прошло нажатие и удерживается больше опред времени это правый щелчок

	если прошло нажатие и отпукание по 2 раза в одном месте и между ними прошёл определённый интервал времени то это двойной щелчок*/

	p->oRawCursorPoint = A_rPoint;
	float fS = 0.03f;

	if ( A_bExisting && !p->bPreviousExistingState && A_fSquareOfSpot < fS ) // mouse down
	{
		p->m_lRightClickCounter++;
		p->m_oRightClickPoint = A_rPoint;
		p->m_bRightBlocker = false;

		if ( !p->m_bDoubleClickActiveCounter ) p->m_bDoubleClickActiveCounter = true;
		if ( p->m_bDoubleClickActiveCounter && p->m_lDoubleClickCounter >= 30 && Distance(p->m_oDoubleClickPoint, A_rPoint) < 10.0f )
		{
			if ( p->oLeftDownCallBack	!= 0 ) (*p->oLeftDownCallBack)(A_rPoint); // first click
			if ( p->oLeftUpCallBack		!= 0 ) (*p->oLeftUpCallBack)(A_rPoint);

			if ( p->oLeftDownCallBack	!= 0 ) (*p->oLeftDownCallBack)(A_rPoint); // second click
			if ( p->oLeftUpCallBack		!= 0 ) (*p->oLeftUpCallBack)(A_rPoint);
		}
		else
		{
			p->m_lDoubleClickCounter = 0;
			if ( p->oLeftDownCallBack != 0 ) (*p->oLeftDownCallBack)(A_rPoint); // else only one click
		}

//		p->m_oMouseEventHistory[2] = S_RawMouseEvent( A_rPoint, E_rmeDOWN, p->m_lBetweenEventCounter );
//		p->m_lBetweenEventCounter = 0;
//
//		if ( p->m_oMouseEventHistory[2].m_oMouseEvent == E_rmeDOWN ) // mouse left button click
//		{
//			if ( p->oLeftDownCallBack != 0 ) (*p->oLeftDownCallBack)(A_rPoint);
//		}
//
//		if (
//			p->m_oMouseEventHistory[0].m_oMouseEvent == E_rmeDOWN	&&
//			p->m_oMouseEventHistory[1].m_oMouseEvent == E_rmeUP		&&
//			p->m_oMouseEventHistory[2].m_oMouseEvent == E_rmeDOWN	&&
//			Distance(p->m_oMouseEventHistory[0].m_oPoint, p->m_oMouseEventHistory[1].m_oPoint) < 10.0f &&
//			Distance(p->m_oMouseEventHistory[1].m_oPoint, p->m_oMouseEventHistory[2].m_oPoint) < 10.0f &&
//			p->m_oMouseEventHistory[1].m_lTimeFromPreviousEvent < 4	&&
//			p->m_oMouseEventHistory[2].m_lTimeFromPreviousEvent < 4		)
//		{
//			long n1 = 0;
//		}
	}
	else if ( !A_bExisting && p->bPreviousExistingState && /*A_fSquareOfSpot < fS &&*/ !p->m_bRightBlocker ) // mouse up
	{
		if ( p->oLeftUpCallBack != 0 ) (*p->oLeftUpCallBack)(A_rPoint);

		p->m_lRightClickCounter = 0;

//		p->m_oMouseEventHistory[2] = S_RawMouseEvent( A_rPoint, E_rmeUP, p->m_lBetweenEventCounter );
//		p->m_lBetweenEventCounter = 0;
//
//		if ( p->m_oMouseEventHistory[2].m_oMouseEvent == E_rmeUP )
//		{
//			if ( p->oLeftUpCallBack		!= 0 )(*p->oLeftUpCallBack)(A_rPoint);
//		}
	}
	else if ( A_bExisting && p->bPreviousExistingState && A_fSquareOfSpot < fS && !p->m_bRightBlocker ) // mouse move
	{
		if ( Distance(A_rPoint, p->m_oRightClickPoint) < 10.0f ) // for right click
		{
			p->m_lRightClickCounter++;
		}
		if ( p->m_lRightClickCounter >= 5 )
		{
			if ( p->oRightDownCallBack	!= 0 ) (*p->oRightDownCallBack)(A_rPoint);
			if ( p->oRightUpCallBack	!= 0 ) (*p->oRightUpCallBack)(A_rPoint);

			p->m_bRightBlocker = true;
			p->m_lRightClickCounter = 0;
		}
		if ( p->oMoveCallBack		!= 0 ) (*p->oMoveCallBack)(A_rPoint);

//		if (																	// mouse right button click
//				p->m_oMouseEventHistory[2].m_oMouseEvent == E_rmeDOWN &&
//				p->m_lBetweenEventCounter >= 10 &&
//				Distance(p->m_oMouseEventHistory[2].m_oPoint, A_rPoint) > 10.0f
//		)
//		{
//			if ( p->oRightDownCallBack	!= 0 )(*p->oRightDownCallBack)(A_rPoint);
//			if ( p->oRightUpCallBack	!= 0 )(*p->oRightUpCallBack)(A_rPoint);
//		}
//
//		if ( p->oMoveCallBack != 0 )(*p->oMoveCallBack)(A_rPoint);
	}
	/*циклическая перестановка событий*/
//	S_RawMouseEvent oTE = p->m_oMouseEventHistory[0];
//	for ( long i = 0; i < 2; ++i )
//	{
//		p->m_oMouseEventHistory[i] = p->m_oMouseEventHistory[i + 1];
//	}
//	p->m_oMouseEventHistory[2] = oTE;
//
//	p->m_lBetweenEventCounter++;

	if ( p->m_bDoubleClickActiveCounter ) p->m_lDoubleClickCounter++;
	
	p->bPreviousExistingState = A_bExisting;
}

//////////////////////////////////////////////////////////////////////////
void C_RawMouse::SetLeftDownCallBack( pfn_RawMouseOnLeftDown A_pLeftDownCallBack )
{
	p->oLeftDownCallBack = A_pLeftDownCallBack;
}

//////////////////////////////////////////////////////////////////////////
void C_RawMouse::SetLeftUpCallBack( pfn_RawMouseOnLeftUp A_pLeftUpCallBack )
{
	p->oLeftUpCallBack = A_pLeftUpCallBack;
}

//////////////////////////////////////////////////////////////////////////
void C_RawMouse::SetRightDownCallBack( pfn_RawMouseOnRightDown A_pRightDownCallBack )
{
	p->oRightDownCallBack = A_pRightDownCallBack;
}

//////////////////////////////////////////////////////////////////////////
void C_RawMouse::SetRightUpCallBack( pfn_RawMouseOnRightUp A_pRightUpCallBack )
{
	p->oRightUpCallBack = A_pRightUpCallBack;
}

//////////////////////////////////////////////////////////////////////////
void C_RawMouse::SetMoveCallBack( pfn_RawMouseOnMove A_pMoveCallBack )
{
	p->oMoveCallBack = A_pMoveCallBack;
}
