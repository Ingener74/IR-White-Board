
#ifndef SETTINGS_WINDOW_H_
#define SETTINGS_WINDOW_H_

#include <string>
#include <memory>
#include <cstdint>

#include <opencv2/core/core.hpp>

#include <QtWidgets/QWidget>

#include <RemoteVariable.h>

class QCloseEvent;
class QShowEvent;
class Ui_WindowSettings;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SettingsWindow: public QWidget
{
Q_OBJECT
    void DrawPoints();

public:
    SettingsWindow(
            RemoteVariable<int> threshold,
            RemoteVariable<cv::Size> calibrationPoints,
            RemoteVariable<int> sensor,
            QWidget * parent = 0,
            Qt::WindowFlags f = 0);

    virtual ~SettingsWindow();

    void closeEvent(QCloseEvent* pEvent);
    void showEvent(QShowEvent* pEvent);

    int getImageSelector() const;
//    uint8_t getThreshold();

signals:
    void signalSettingsCaptureNoExist();
    void signalSettingsCaptureExist();
    void signalCameraChanged();

public slots:
    void changeCalibrationPointsHor(int i);
    void changeCalibrationPointsVer(int i);
    void slotDrawSensorImage(cv::Mat image);
    void slotSettingsNoCamera();

private:
    std::shared_ptr<Ui_WindowSettings> _ui;

    RemoteVariable<int>                _threshold;
    RemoteVariable<cv::Size>           _calibrationPoints;
    RemoteVariable<int>                _sensor;
};

#endif
