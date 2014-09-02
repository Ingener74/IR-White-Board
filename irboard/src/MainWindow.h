
#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <SettingsWindow.h>
#include <QtWidgets/QMainWindow>
#include <QtCore/QTimer>

#include <ui_MainWindow.h>
#include <memory>

//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/core/core.hpp>

//#include "C_DisplayMouse.h"

//////////////////////////////////////////////////////////////////////////
class MainWindow: public QMainWindow
{
Q_OBJECT

public:
    using Ptr = std::shared_ptr<MainWindow>;

    MainWindow(std::shared_ptr<QApplication> app, QWidget *parent = 0, Qt::WindowFlags flags = 0);
    virtual ~MainWindow();

    void closeEvent(QCloseEvent* pEvent);
    void timerEvent(QTimerEvent* pEvent);

public slots:
    void Calibration(void);

    void slotSystemNoCamera();
    void slotSystemAllOk();
    void slotSystemNotCalibrated();

    void slotPulledOut();

signals:
    void signalMainWindowExit();
    void signalSystemNoCamera();

    void signalAllOk();
    void signalCalibrationIsNeeded();

    void signalPulledOut();

private:
    Ui::MainWindow _ui;

    std::shared_ptr<QApplication> _app;

//    QSystemTrayIcon*                pSystemTray                 = 0;
//    QMenu*                          pSystemTrayMenu             = 0;
//
//    QAction*                        pSystemTrayMenuRestore      = 0;
//    QAction*                        pSystemTrayMenuCalibration  = 0;
//    QAction*                        pSystemTrayMenuSettings     = 0;
//    QAction*                        pSystemTrayMenuAbout        = 0;
//    QAction*                        pSystemTrayMenuClose        = 0;
//
    /** Settings window */
    std::shared_ptr<SettingsWindow> _settingsWindow;
    bool                            _bshown = false;
//
//    // capture system data
//    VideoCapture*                   pVideoCapture               = 0;
//    bool                            captureExist                = false;
//    Mat                             inputImage;
//
//    // pulled out checking
//    C_PulledOutOfCamera             poutcheck;
//    // end pulled out checking
//
//    // incorrect camera parameters
//    long                            lInCorrentCounter           = 0;
//    long                            lFullCounter                = 0;
//    // end incorrect
//
//    Mat                             mono;
//    Mat                             thresh;
//
//    Mat                             outImage;
//    unsigned int                    uiThreshold                 = 255 - 3;
//    unsigned int                    uiCurrentCamera             = 0;
//    unsigned int                    uiNextCamera                = 0;
//    float                           fps                         = 30.0f;
//
//    int                             captureTimer                = 0;
//    int                             findCaptureTimer            = 0;
//
//    // about window data
//    C_AboutWindow*                  pAboutWindow                = 0;
//
//    // calibration window data
//    C_CalibrationWindow*            pCalibrationWindow          = 0;
//    Size_<unsigned int>             calibrationPoints;
//
//    // mouse control data
//    C_RawMouse*                     pRawMouse                   = 0;
//    Point2f                         lastRawPosition;
//
//    C_CoordinateTransform*          pCoordinateTransform        = 0;
//    Size_<unsigned int>             screenResolution;
};

//Size_<unsigned int> getSystemResolution();

// callbacks
// for calibration
//void CoordinateTransformCalibrationOnLeftDown( Point2f A_rPoint );
//
//// for work
//void CoordinateTransformWorkOnLeftDown( Point2f A_rPoint );
//void CoordinateTransformWorkOnLeftUp( Point2f A_rPoint );
//void CoordinateTransformWorkOnMove( Point2f A_rPoint );
//void CoordinateTransformWorkOnRightDown( Point2f A_rPoint );
//void CoordinateTransformWorkOnRightUp( Point2f A_rPoint );
//
//bool ProbablyWroneCamera(vector<vector<Point> >& contours, Mat& threshImage);

//class C_PulledOutOfCamera
//{
//public:
//    C_PulledOutOfCamera() :
//            m_Buffer(25)
//    {
//    }
//
//    bool Check(Mat& image)
//    {
//        long lSum = 0;
//
//        for (int y = 0; y < image.rows; y += (image.rows - 5) / 10)
//        {
//            for (int x = 0; x < image.cols; ++x)
//            {
//                lSum += image.at<Vec3b>(y, x)[0] + image.at<Vec3b>(y, x)[1] + image.at<Vec3b>(y, x)[2];
//            }
//        }
//
//        // paste new sum of image rows in buffer
//        for (unsigned int i = 0; i < m_Buffer.size() - 1; ++i)
//        {
//            m_Buffer[i] = m_Buffer[i + 1];
//        }
//        m_Buffer[m_Buffer.size() - 1] = lSum;
//
//        // now check
//        bool match = true;
//        for (unsigned int i = 1; i < m_Buffer.size(); ++i)
//        {
//            if (m_Buffer[0] != m_Buffer[i] || m_Buffer[i] == 0) match = false;
//        }
//
//        return match;
//    }
//private:
//    vector<long> m_Buffer;
//};

#endif

