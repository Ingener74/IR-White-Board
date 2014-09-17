
#ifndef SETTINGS_WINDOW_H_
#define SETTINGS_WINDOW_H_

#include <string>
#include <memory>
#include <cstdint>

#include <QtWidgets/QWidget>

#include <IrCameraProcessor.h>

//////////////////////////////////////////////////////////////////////////

class QCloseEvent;
class QShowEvent;
class Ui_WindowSettings;

class SettingsWindow: public QWidget
{
Q_OBJECT
    void DrawPoints();

public:
    SettingsWindow(Thresholder, QWidget * parent = 0, Qt::WindowFlags f = 0);
    virtual ~SettingsWindow();

    void closeEvent(QCloseEvent* pEvent);
    void showEvent(QShowEvent* pEvent);

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

    uint8_t getThreshold();

private:
    std::shared_ptr<Ui_WindowSettings> _ui;

    Thresholder _thresholder;

    uint8_t _threshold = 255 - 3;
};

#endif
