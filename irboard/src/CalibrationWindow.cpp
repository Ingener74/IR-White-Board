
#include <CalibrationWindow.h>

/*data definition*/
//extern	S_Size<long>            oSystemDisplayResolution;         /*���������� ������*/
//		HWND                    hCalibrationWindowWnd = 0;
//
//extern	C_CoordinateTransform   oCoordinateTransformSystem;       /*coordinate transformation system*/

//extern	cv::Size_<int>					oSystemDisplayResolution;
//extern	C_CoordinateTransform*			pCoordinateTransform;
//extern	float							fps;

//////////////////////////////////////////////////////////////////////////
CalibrationWindow::CalibrationWindow( QWidget* pParent /*= 0 */ )
	: QGLWidget(pParent)
{
//	startTimer( 1000 / fps );
}

//////////////////////////////////////////////////////////////////////////
void CalibrationWindow::initializeGL()
{
//	glClearColor(0.42f, 0.7f, 1.0f, 0);
}

//////////////////////////////////////////////////////////////////////////
void CalibrationWindow::resizeGL( int iWidth, int iHeight )
{
//	glViewport(0, 0, (GLint)iWidth, (GLint)iHeight);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	glOrtho(0.0f, (float)iWidth, 0.0f, (float)iHeight, -10, 10);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
}

//////////////////////////////////////////////////////////////////////////
void CalibrationWindow::paintGL()
{
//	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//	glClearColor(0.42f, 0.7f, 1.0f, 0);
//
//	glColor3f(1.0f, 1.0f, 1.0f);
//	glLineWidth(2.0f);

//	if(pCoordinateTransform != 0){
//		if(pCoordinateTransform->GetNumberOfDisplayPoints() > 0){
//			DrawMark(pCoordinateTransform->GetCurrentDisplayPoint());
//		}
//	}

//	glFlush();
//	glPopMatrix();
}

//////////////////////////////////////////////////////////////////////////
void CalibrationWindow::keyPressEvent( QKeyEvent* pEvent )
{
	if (pEvent->key() == Qt::Key_Escape)
	{
		this->close();
	}
}

//////////////////////////////////////////////////////////////////////////
void CalibrationWindow::timerEvent( QTimerEvent* pEvent ){
	paintGL();
	updateGL();
}

//////////////////////////////////////////////////////////////////////////
//void C_CalibrationWindow::closeEvent( QCloseEvent* pEvent )
//{
//	pEvent->ignore();
//
//	hide();
//}

//////////////////////////////////////////////////////////////////////////
//void DrawMark(cv::Point A_oPoint) {
//		glColor3f(1, 1, 1);
//
//		glBegin(GL_LINES);
//			glVertex2f(A_oPoint.x - 20, A_oPoint.y);
//			glVertex2f(A_oPoint.x + 20, A_oPoint.y);
//
//			glVertex2f(A_oPoint.x, A_oPoint.y - 20);
//			glVertex2f(A_oPoint.x, A_oPoint.y + 20);
//		glEnd();
//
//		long  lPies = 20;
//		float fR  = 20.0f;
//		float fdR = (360.0f / lPies) * (3.1415f / 180.0f);
//
//		glLineWidth(3);
//		glBegin(GL_LINES);
//		for ( long i = 0; i < lPies; ++i )
//		{
//			cv::Point2f oPP( fR * cos(fdR*i), fR * sin(fdR*i));
//			glVertex2f( A_oPoint.x + fR * cos(fdR*i),		A_oPoint.y + fR*sin(fdR*i));
//			glVertex2f( A_oPoint.x + fR * cos(fdR*(i+1)),	A_oPoint.y + fR*sin(fdR*(i+1)));
//		}
//		glEnd();
//}
