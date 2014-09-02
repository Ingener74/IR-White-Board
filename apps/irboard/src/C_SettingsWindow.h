

#include <string>

#include <QtGui/QWidget>
#include <QtGui/QCloseEvent>
#include <QtGui/QHideEvent>
#include <QtGui/QShowEvent>
#include <QtGui/qevent.h>
#include <QtCore/qtimer.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include "ui_SettingsWindow.h"

using namespace cv;

//////////////////////////////////////////////////////////////////////////

class C_SettingsWindow: public QWidget
{
	Q_OBJECT
	void DrawPoints();

public:
	C_SettingsWindow( QWidget * parent = 0, Qt::WindowFlags f = 0 );

	void closeEvent( QCloseEvent* pEvent );
	void showEvent( QShowEvent* pEvent );
	void timerEvent( QTimerEvent* pEvent );

signals:
	void signalSettingsCaptureNoExist();
	void signalSettingsCaptureExist();
	void signalCameraChanged();

public slots:
	void RefreshThreshold(int iThreshold);
	void SensorChange( int iIndex );

	void changeCalibrationPointsHor(int i);
	void changeCalibrationPointsVer(int i);

	void slotDrawSensorImage(Mat& image);

	void slotSettingsNoCamera();

//	void Apply();

private:
	

	Ui::WindowSettings ui;
};
