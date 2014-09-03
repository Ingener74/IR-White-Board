
#ifndef CALIBRATIONWINDOW_H_
#define CALIBRATIONWINDOW_H_

#include <QtCore/QEvent>
#include <QtCore/QTimer>

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLColormap>

#include <QtGui/QKeyEvent>
#include <QtGui/QCloseEvent>

//#include "main.h"
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//#include "C_CoordinateTransform.h"

//////////////////////////////////////////////////////////////////////////
class CalibrationWindow: public QGLWidget
{
Q_OBJECT
public:
    CalibrationWindow(QWidget* pParent = 0);
protected:
    void initializeGL();
    void resizeGL(int iWidth, int iHeight);
    void paintGL();

    void keyPressEvent(QKeyEvent* pEvent);
    void timerEvent(QTimerEvent* pEvent);

//	void closeEvent( QCloseEvent* pEvent );

private:
};

//////////////////////////////////////////////////////////////////////////
////void DrawMark(S_Point<float>& A_rPoint);
//void DrawMark(cv::Point A_oPoint);

#endif
