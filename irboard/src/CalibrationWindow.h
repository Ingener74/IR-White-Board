#ifndef CALIBRATIONWINDOW_H_
#define CALIBRATIONWINDOW_H_

#include <opencv2/core/core.hpp>

#include <QtCore/QEvent>
#include <QtCore/QTimer>

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLColormap>

#include <QtGui/QKeyEvent>
#include <QtGui/QCloseEvent>

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

    void closeEvent(QCloseEvent* pEvent);

    void DrawMark(cv::Point point);

private:
};

#endif
