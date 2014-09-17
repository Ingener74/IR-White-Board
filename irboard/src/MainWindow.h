
#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <memory>

#include <QtCore/QTimer>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSystemTrayIcon>

#include <ui_MainWindow.h>

#include <SettingsWindow.h>
#include <CalibrationWindow.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

//////////////////////////////////////////////////////////////////////////
class MainWindow: public QMainWindow
{
Q_OBJECT

public:
    using Ptr = std::shared_ptr<MainWindow>;

    MainWindow(
            std::shared_ptr<QApplication>,
            SettingsWindow::Ptr,
            CalibrationWindow::Ptr,
            QWidget *parent = 0, Qt::WindowFlags flags = 0);
    virtual ~MainWindow();

    void closeEvent(QCloseEvent* pEvent);
    void timerEvent(QTimerEvent* pEvent);

public slots:
    void Calibration(void);

    void slotSystemNoCamera();
    void slotSystemAllOk();
    void slotSystemNotCalibrated();

signals:
    void signalMainWindowExit();
    void signalSystemNoCamera();

    void signalAllOk();
    void signalCalibrationIsNeeded();

    void signalPulledOut();

private:
    Ui::MainWindow                      _ui;

    std::shared_ptr<QApplication>       _app;

    std::shared_ptr<QSystemTrayIcon>    _systemTray;
    std::shared_ptr<QMenu>              _systemTrayMenu;

    std::shared_ptr<QAction>            _systemTrayMenuRestore;
    std::shared_ptr<QAction>            _systemTrayMenuCalibration;
    std::shared_ptr<QAction>            _systemTrayMenuSettings;
    std::shared_ptr<QAction>            _systemTrayMenuAbout;
    std::shared_ptr<QAction>            _systemTrayMenuClose;

    SettingsWindow::Ptr                 _settingsWindow;

//    Mat                             outImage;
//    unsigned int                    uiThreshold                 = 255 - 3;
//    unsigned int                    uiCurrentCamera             = 0;
//    unsigned int                    uiNextCamera                = 0;
//    float                           fps                         = 30.0f;
//
//    int                             captureTimer                = 0;
//    int                             findCaptureTimer            = 0;
//
//    // calibration window data
    CalibrationWindow::Ptr              _calibrationWindow;
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

#endif

