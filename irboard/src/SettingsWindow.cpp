
#include <iostream>

#include <SettingsWindow.h>

using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
SettingsWindow::SettingsWindow(QWidget * parent /*= 0*/, Qt::WindowFlags f /*= 0 */) :
        QWidget(parent, f)
{
    _ui.setupUi(this);

    QObject::connect(_ui.horizontalSliderThreshold, SIGNAL(valueChanged(int)), this, SLOT(RefreshThreshold(int)));

    connect(_ui.spinBoxCamera, SIGNAL(valueChanged(int)), SLOT(SensorChange(int)));
    connect(_ui.ButtonApply, SIGNAL(clicked()), SLOT(hide()));

    QObject::connect(this, SIGNAL(signalSettingsCaptureNoExist()), SLOT(slotSettingsNoCamera()));
//    QObject::connect(this, SIGNAL(signalSettingsCaptureNoExist()), pMainWindow, SLOT(slotSystemNoCamera()));

//    QObject::connect(this, SIGNAL(signalSettingsCaptureExist()), pMainWindow, SLOT(slotSystemNotCalibrated()));

    QObject::connect(_ui.spinBoxHorPoints, SIGNAL(valueChanged(int)), this, SLOT(changeCalibrationPointsHor(int)));
    QObject::connect(_ui.spinBoxVetPoints, SIGNAL(valueChanged(int)), this, SLOT(changeCalibrationPointsVer(int)));

//    _ui.horizontalSliderThreshold->setValue(uiThreshold);

//	startTimer(1000 / 30);
}

//////////////////////////////////////////////////////////////////////////
void SettingsWindow::closeEvent(QCloseEvent* pEvent)
{
    pEvent->ignore();
    hide();
}

void SettingsWindow::DrawPoints()
{
    Mat points(Size_<unsigned int>(480, 360), CV_8UC3, CV_RGB(255, 178, 107));
//    for (unsigned int py = 0; py < calibrationPoints.height; ++py)
//    {
//        for (unsigned int px = 0; px < calibrationPoints.width; ++px)
//        {
//            circle(points,
//                    Point(px * points.cols / (calibrationPoints.width - 1),
//                            py * points.rows / (calibrationPoints.height - 1)), 3, CV_RGB(255, 255, 255), -1);
//        }
//    }
    QImage im((uchar*) (points.data), points.cols, points.rows, QImage::Format_RGB888);
    _ui.labelPointsPositions->setPixmap(QPixmap::fromImage(im));
}

//////////////////////////////////////////////////////////////////////////
void SettingsWindow::showEvent(QShowEvent* pEvent)
{
//    ui.horizontalSliderThreshold->setValue(uiThreshold);
//
//    DrawPoints();
}

//////////////////////////////////////////////////////////////////////////
void SettingsWindow::timerEvent(QTimerEvent* pEvent)
{
}

//////////////////////////////////////////////////////////////////////////
void SettingsWindow::RefreshThreshold(int threshold)
{
    _threshold = threshold;
}

//////////////////////////////////////////////////////////////////////////
void SettingsWindow::SensorChange(int iIndex)
{
//    uiNextCamera = iIndex - 1;
}

void SettingsWindow::slotDrawSensorImage(Mat image)
{
//    if ((float) lInCorrentCounter / (float) lFullCounter > 0.1)
//    {
//        rectangle(resized, Point(5, 5), Point(resized.cols - 5, resized.rows - 5), CV_RGB(0, 0, 255), 5);
//    }

    if (!isHidden())
    {
//        if (_ui.comboBoxViewedImage->currentIndex() == 0)
//        {
//            cvtColor(inputImage, dest, CV_BGR2RGB);
//        }
//        else
//        {
//            cvtColor(outImage, dest, CV_BGR2RGB);
//        }

        Mat rgb, out;

        cvtColor(image, rgb, CV_RGB2BGR);

        cv::resize(rgb, out, Size(320, 240));

        QImage im((uchar*) out.data, out.cols, out.rows, QImage::Format_RGB888);
        _ui.labelSensorView->setPixmap(QPixmap::fromImage(im));
    }
}

void SettingsWindow::slotSettingsNoCamera()
{
    _ui.labelSensorView->setPixmap(QPixmap(QString::fromUtf8(":/main/no_web_camera_320240.png")));
}

void SettingsWindow::changeCalibrationPointsHor(int i)
{
//    calibrationPoints = Size_<unsigned int>(i, calibrationPoints.height);
    DrawPoints();
}

void SettingsWindow::changeCalibrationPointsVer(int i)
{
//    calibrationPoints = Size_<unsigned int>(calibrationPoints.width, i);
    DrawPoints();
}

uint8_t SettingsWindow::getThreshold()
{
    return max(0, min(_ui.horizontalSliderThreshold->sliderPosition(), 255));
}
