
#include <iostream>

#include <QtGui/QCloseEvent>

#include <opencv2/imgproc/imgproc.hpp>

#include <ui_SettingsWindow.h>
#include <SettingsWindow.h>

using namespace std;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
SettingsWindow::SettingsWindow(
        GetThreshold getThreshold,
        PutThreshold putThreshold,
        GetCalibrationPoints getCalibPoints,
        PutCalibrationPoints putCalibPoints,
        QWidget * parent /*= 0*/,
        Qt::WindowFlags f /*= 0 */) :
                QWidget(parent, f),
                _ui(make_shared<Ui_WindowSettings>()),
                _getThreshold(getThreshold ? getThreshold : throw invalid_argument("in settings window get threshold is invalid")),
                _putThreshold(putThreshold ? putThreshold : throw invalid_argument("in settings window put threshold is invalid")),
                _getCalibPoints(getCalibPoints ? getCalibPoints : throw invalid_argument("get calibration points is invalid")),
                _putCalibPoints(putCalibPoints ? putCalibPoints : throw invalid_argument("put calibration points is invalid"))
{
    _ui->setupUi(this);

    function<void(int)> a = [](int i){
        cout << "i = " << i << endl;
    };

    connect(_ui->spinBoxCamera, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), a);
    connect(_ui->ButtonApply, SIGNAL(clicked()), SLOT(hide()));

    QObject::connect(this, SIGNAL(signalSettingsCaptureNoExist()), SLOT(slotSettingsNoCamera()));

    QObject::connect(_ui->spinBoxHorPoints, SIGNAL(valueChanged(int)), this, SLOT(changeCalibrationPointsHor(int)));
    QObject::connect(_ui->spinBoxVetPoints, SIGNAL(valueChanged(int)), this, SLOT(changeCalibrationPointsVer(int)));

    _ui->horizontalSliderThreshold->setValue(_getThreshold());
}

SettingsWindow::~SettingsWindow()
{
    _putThreshold(_ui->horizontalSliderThreshold->value());
    cout << "SettingsWindow::~SettingsWindow()" << endl;
}

//////////////////////////////////////////////////////////////////////////
void SettingsWindow::closeEvent(QCloseEvent* pEvent)
{
    /*
     * Ignore closing just hide window
     */
    pEvent->ignore();
    hide();
}

void SettingsWindow::DrawPoints()
{
    Mat points(Size(480, 360), CV_8UC3, CV_RGB(255, 178, 107));
    auto calibrationPoints = _getCalibPoints();
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

//////////////////////////////////////////////////////////////////////////
void SettingsWindow::showEvent(QShowEvent* pEvent)
{
    _ui->horizontalSliderThreshold->setValue(_getThreshold());
    DrawPoints();
}

//////////////////////////////////////////////////////////////////////////
void SettingsWindow::slotDrawSensorImage(Mat image)
{
    if (!isHidden())
    {
        Mat rgb, out;

        cvtColor(image, rgb, CV_RGB2BGR);

        cv::resize(rgb, out, Size(320, 240));

        QImage im((uchar*) out.data, out.cols, out.rows, QImage::Format_RGB888);
        _ui->labelSensorView->setPixmap(QPixmap::fromImage(im));
    }
}

void SettingsWindow::slotSettingsNoCamera()
{
    _ui->labelSensorView->setPixmap(QPixmap(QString::fromUtf8(":/main/no_web_camera_320240.png")));
}

void SettingsWindow::changeCalibrationPointsHor(int i)
{
    auto calibrationPoints = _getCalibPoints();
    _putCalibPoints(Size(i, calibrationPoints.height));
    DrawPoints();
}

void SettingsWindow::changeCalibrationPointsVer(int i)
{
    auto calibrationPoints = _getCalibPoints();
    _putCalibPoints(Size(calibrationPoints.width, i));
    DrawPoints();
}

uint8_t SettingsWindow::getThreshold()
{
    return max(0, min(_ui->horizontalSliderThreshold->value(), 255));
}

int SettingsWindow::getImageSelector() const
{
    return _ui->comboBoxViewedImage->currentIndex();
}
