#ifndef CALIBRATIONWINDOW_H_
#define CALIBRATIONWINDOW_H_

#include <memory>

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFunctions>

namespace cv {

template<typename _Tp> class Point_;
typedef Point_<int> Point2i;
typedef Point2i Point;

}  // namespace cv
class QKeyEvent;
class QTimerEvent;
class QCloseEvent;

using CalibrationPoint = std::function<cv::Point()>;

class CalibrationWindow: public QGLWidget, public QGLFunctions
{
Q_OBJECT
public:
    using Ptr = std::shared_ptr<CalibrationWindow>;

    CalibrationWindow(CalibrationPoint, QWidget* pParent = 0);
    virtual ~CalibrationWindow();
protected:
    void initializeGL();
    void resizeGL(int iWidth, int iHeight);
    void paintGL();

    void keyPressEvent(QKeyEvent* pEvent);
    void timerEvent(QTimerEvent* pEvent);

    void closeEvent(QCloseEvent* pEvent);

    void DrawMark(cv::Point point);

private:
    CalibrationPoint _calibrationPoint;
};

#endif
