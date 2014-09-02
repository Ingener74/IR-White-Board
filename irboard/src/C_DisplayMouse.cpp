

#include "C_DisplayMouse.h"

//////////////////////////////////////////////////////////////////////////
void DisplayMouseLeftDown( Point A_rCursorPoint, Size_<unsigned int> A_rDisplayResolution )
{
	mouse_event( 
		MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN, 
		(A_rCursorPoint.x * 65535)/A_rDisplayResolution.width,
		(A_rCursorPoint.y * 65535)/A_rDisplayResolution.height,
		0, 0);
}

//////////////////////////////////////////////////////////////////////////
void DisplayMouseMove( Point A_rCursorPoint, Size_<unsigned int> A_rDisplayResolution )
{
	mouse_event( 
		MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE/*|MOUSEEVENTF_LEFTDOWN*/, 
		(A_rCursorPoint.x * 65535)/A_rDisplayResolution.width,
		(A_rCursorPoint.y * 65535)/A_rDisplayResolution.height,
		0, 0);
}

//////////////////////////////////////////////////////////////////////////
void DisplayMouseLeftUp( Point A_rCursorPoint, Size_<unsigned int> A_rDisplayResolution )
{
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

//////////////////////////////////////////////////////////////////////////
void DisplayMouseRightDown( Point A_rCursorPoint, Size_<unsigned int> A_rDisplayResolution )
{
	mouse_event( 
		MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN, 
		(A_rCursorPoint.x * 65535)/A_rDisplayResolution.width,
		(A_rCursorPoint.y * 65535)/A_rDisplayResolution.height,
		0, 0);
}

//////////////////////////////////////////////////////////////////////////
void DisplayMouseRightUp( Point A_rCursorPoint, Size_<unsigned int> A_rDisplayResolution )
{
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}
