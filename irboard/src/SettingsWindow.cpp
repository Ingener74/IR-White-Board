
#include <iostream>

#include <QtGui/QCloseEvent>

#include <opencv2/imgproc/imgproc.hpp>

#include <ui_SettingsWindow.h>
#include <SettingsWindow.h>

using namespace std;
using namespace cv;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SettingsWindow::SettingsWindow(
        RemoteVariable<int> threshold,
        RemoteVariable<cv::Size> calibrationPoints,
        RemoteVariable<int> sensor,
        QWidget * parent /*= 0*/,
        Qt::WindowFlags f /*= 0 */) :
                QWidget(parent, f),
                _ui(make_shared<Ui_WindowSettings>()),
                _threshold(threshold),
                _calibrationPoints(calibrationPoints),
                _sensor(sensor)
{
    _ui->setupUi(this);

    _ui->spinBoxCamera->setValue(_sensor);

    connect(_ui->spinBoxCamera, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int i){ _sensor = i; });
    connect(_ui->ButtonApply, SIGNAL(clicked()), SLOT(hide()));

    QObject::connect(this, SIGNAL(signalSettingsCaptureNoExist()), SLOT(slotSettingsNoCamera()));

    QObject::connect(_ui->spinBoxHorPoints, SIGNAL(valueChanged(int)), this, SLOT(changeCalibrationPointsHor(int)));
    QObject::connect(_ui->spinBoxVetPoints, SIGNAL(valueChanged(int)), this, SLOT(changeCalibrationPointsVer(int)));

    _ui->horizontalSliderThreshold->setValue(_threshold);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SettingsWindow::~SettingsWindow()
{
    _threshold = _ui->horizontalSliderThreshold->value();
    cout << "SettingsWindow::~SettingsWindow()" << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SettingsWindow::closeEvent(QCloseEvent* pEvent)
{
    /*
     * Ignore closing just hide window
     */
    pEvent->ignore();
    hide();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SettingsWindow::DrawPoints()
{
    Mat points(Size(480, 360), CV_8UC3, CV_RGB(255, 178, 107));
    cv::Size calibrationPoints = _calibrationPoints;
    for (unsigned int py = 0; py < calibrationPoints.height; ++py)
    {
        for (unsigned int px = 0; px < calibrationPoints.width; ++px)
        {
            circle(points,
                    Point
                    (
                        px * points.cols / (calibrationPoints.width - 1),
                        py * points.rows / (calibrationPoints.height - 1)
                    ), 3, CV_RGB(255, 255, 255), -1);
        }
    }
    QImage im((uchar*) (points.data), points.cols, points.rows, QImage::Format_RGB888);
    _ui->labelPointsPositions->setPixmap(QPixmap::fromImage(im));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SettingsWindow::showEvent(QShowEvent* pEvent)
{
    _ui->horizontalSliderThreshold->setValue(_threshold);
    DrawPoints();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SettingsWindow::slotDrawSensorImage(Mat image)
{
    if (isHidden()) return;
    if (image.empty()) throw runtime_error("image is empty");

    Mat rgb, out;

    cvtColor(image, rgb, CV_RGB2BGR);

    cv::resize(rgb, out, Size(320, 240));

    QImage im((uchar*) out.data, out.cols, out.rows, QImage::Format_RGB888);
    _ui->labelSensorView->setPixmap(QPixmap::fromImage(im));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SettingsWindow::slotSettingsNoCamera()
{
    _ui->labelSensorView->setPixmap(QPixmap(QString::fromUtf8(":/main/no_web_camera_320240.png")));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SettingsWindow::changeCalibrationPointsHor(int i)
{
//    Size calibrationPoints = _calibrationPoints;
    _calibrationPoints = Size(i, static_cast<Size>(_calibrationPoints).height);
    DrawPoints();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SettingsWindow::changeCalibrationPointsVer(int i)
{
//    Size calibrationPoints = _calibrationPoints;
    _calibrationPoints = Size(static_cast<Size>(_calibrationPoints).width, i);
    DrawPoints();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t SettingsWindow::getThreshold()
{
    return max(0, min(_ui->horizontalSliderThreshold->value(), 255));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SettingsWindow::getImageSelector() const
{
    return _ui->comboBoxViewedImage->currentIndex();
}
