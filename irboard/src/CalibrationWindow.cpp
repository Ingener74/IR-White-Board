#include <iostream>

#include <opencv2/core/core.hpp>

#include <CalibrationWindow.h>
#include <QtGui/QKeyEvent>

using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
CalibrationWindow::CalibrationWindow(CalibrationPoint cp, QWidget* pParent /*= 0 */) :
        QGLWidget(pParent), _calibrationPoint(cp ? cp : throw invalid_argument("calibration point getter is invalid"))
{
    startTimer(1000 / 30 /*FIXME fps??? */);
}

CalibrationWindow::~CalibrationWindow()
{
    cout << "CalibrationWindow::~CalibrationWindow()" << endl;
}

//////////////////////////////////////////////////////////////////////////
void CalibrationWindow::initializeGL()
{
    glClearColor(0.42f, 0.7f, 1.0f, 0);
}

//////////////////////////////////////////////////////////////////////////
void CalibrationWindow::resizeGL(int iWidth, int iHeight)
{
    glViewport(0, 0, (GLint) iWidth, (GLint) iHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0f, (float) iWidth, 0.0f, (float) iHeight, -10, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//////////////////////////////////////////////////////////////////////////
void CalibrationWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.42f, 0.7f, 1.0f, 0);

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);

    DrawMark(_calibrationPoint());

    glFlush();
    glPopMatrix();
}

//////////////////////////////////////////////////////////////////////////
void CalibrationWindow::keyPressEvent(QKeyEvent* pEvent)
{
    if (pEvent->key() == Qt::Key_Escape)
    {
        this->close();
    }
}

//////////////////////////////////////////////////////////////////////////
void CalibrationWindow::timerEvent(QTimerEvent* pEvent)
{
    paintGL();
    updateGL();
}

//////////////////////////////////////////////////////////////////////////
void CalibrationWindow::closeEvent(QCloseEvent* pEvent)
{
    pEvent->ignore();
    hide();
}

//////////////////////////////////////////////////////////////////////////
void CalibrationWindow::DrawMark(Point point)
{
    glColor3f(1, 1, 1);

    glBegin(GL_LINES);
    glVertex2f(point.x - 20, point.y);
    glVertex2f(point.x + 20, point.y);

    glVertex2f(point.x, point.y - 20);
    glVertex2f(point.x, point.y + 20);
    glEnd();

    long lPies = 20;
    float fR = 20.0f;
    float fdR = (360.0f / lPies) * (3.1415f / 180.0f);

    glLineWidth(3);
    glBegin(GL_LINES);
    for (long i = 0; i < lPies; ++i)
    {
        cv::Point2f oPP(fR * cos(fdR * i), fR * sin(fdR * i));
        glVertex2f(point.x + fR * cos(fdR * i), point.y + fR * sin(fdR * i));
        glVertex2f(point.x + fR * cos(fdR * (i + 1)), point.y + fR * sin(fdR * (i + 1)));
    }
    glEnd();
}
