
#ifndef SETTINGS_WINDOW_H_
#define SETTINGS_WINDOW_H_

#include <string>

#include <QtWidgets/QWidget>
#include <QtGui/QCloseEvent>
#include <QtGui/QHideEvent>
#include <QtGui/QShowEvent>
#include <QtCore/QTimer>
#include <QtCore/QEvent>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <ui_SettingsWindow.h>

//////////////////////////////////////////////////////////////////////////

class SettingsWindow: public QWidget
{
Q_OBJECT
    void DrawPoints();

public:
    SettingsWindow(QWidget * parent = 0, Qt::WindowFlags f = 0);

    void closeEvent(QCloseEvent* pEvent);
    void showEvent(QShowEvent* pEvent);
    void timerEvent(QTimerEvent* pEvent);

signals:
    void signalSettingsCaptureNoExist();
    void signalSettingsCaptureExist();
    void signalCameraChanged();

public slots:
    void RefreshThreshold(int iThreshold);
    void SensorChange(int iIndex);

    void changeCalibrationPointsHor(int i);
    void changeCalibrationPointsVer(int i);

    void slotDrawSensorImage(cv::Mat image);

    void slotSettingsNoCamera();

private:
    Ui::WindowSettings _ui;
};

#endif
