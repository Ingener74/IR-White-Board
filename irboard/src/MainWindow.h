
#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <memory>
#include <QtWidgets/QMainWindow>

class Ui_MainWindow;
class SettingsWindow;
class CalibrationWindow;
class QTimerEvent;
class QCloseEvent;
class QSystemTrayIcon;
class QMenu;
class QAction;

//////////////////////////////////////////////////////////////////////////
class MainWindow: public QMainWindow
{
Q_OBJECT

public:
    using Ptr = std::shared_ptr<MainWindow>;

    MainWindow(
            std::shared_ptr<QApplication>,
            std::shared_ptr<SettingsWindow>,
            std::shared_ptr<CalibrationWindow>,
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
    std::shared_ptr<Ui_MainWindow>      _ui;

    std::shared_ptr<QApplication>       _app;

    std::shared_ptr<QSystemTrayIcon>    _systemTray;
    std::shared_ptr<QMenu>              _menu;

    std::shared_ptr<QAction>            _menuRestore;
    std::shared_ptr<QAction>            _menuCalibration;
    std::shared_ptr<QAction>            _menuSettings;
    std::shared_ptr<QAction>            _menuClose;

    std::shared_ptr<SettingsWindow>     _settingsWindow;

    std::shared_ptr<CalibrationWindow>  _calibrationWindow;

//    Size_<unsigned int>             calibrationPoints;

//    // mouse control data
//    C_RawMouse*                     pRawMouse                   = 0;
//    Point2f                         lastRawPosition;
//
//    Size_<unsigned int>             screenResolution;
};

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

#endif

