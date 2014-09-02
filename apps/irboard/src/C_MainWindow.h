

#ifndef _C_MAINWINDOW_H_
#define _C_MAINWINDOW_H_

#include <QtGui/QMainWindow>
#include <QtCore/qtimer.h>


#include "ui_MainWindow.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include "C_DisplayMouse.h"

using namespace cv;
using namespace std;

//////////////////////////////////////////////////////////////////////////
class C_MainWindow: public QMainWindow
{
	Q_OBJECT

public:
	C_MainWindow( QWidget *parent = 0, Qt::WFlags flags = 0 );
	virtual ~C_MainWindow();

	void closeEvent( QCloseEvent* pEvent );
	void timerEvent( QTimerEvent* pEvent );

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
	Ui::MainWindow ui;
};

Size_<unsigned int> getSystemResolution();

// callbacks
// for calibration
void CoordinateTransformCalibrationOnLeftDown( Point2f A_rPoint );

// for work
void CoordinateTransformWorkOnLeftDown( Point2f A_rPoint );
void CoordinateTransformWorkOnLeftUp( Point2f A_rPoint );
void CoordinateTransformWorkOnMove( Point2f A_rPoint );
void CoordinateTransformWorkOnRightDown( Point2f A_rPoint );
void CoordinateTransformWorkOnRightUp( Point2f A_rPoint );

bool ProbablyWroneCamera(vector<vector<Point> >& contours, Mat& threshImage);

class C_PulledOutOfCamera{
public:
	C_PulledOutOfCamera(): m_Buffer(25){}

	bool Check(Mat& image){
		long lSum=0;

		for(int y=0;y<image.rows; y+= (image.rows - 5) / 10 ){
			for(int x=0;x<image.cols;++x){
				lSum+= image.at<Vec3b>(y, x)[0] + image.at<Vec3b>(y, x)[1] + image.at<Vec3b>(y, x)[2];
			}
		}

		// paste new sum of image rows in buffer
		for(unsigned int i=0;i<m_Buffer.size()-1;++i){
			m_Buffer[i]=m_Buffer[i+1];
		}
		m_Buffer[m_Buffer.size()-1]=lSum;

		// now check
		bool match=true;
		for(unsigned int i=1;i<m_Buffer.size();++i){
			if(m_Buffer[0]!=m_Buffer[i] || m_Buffer[i]==0 )
				match = false;
		}

		return match;
	}
private:
	vector<long> m_Buffer;
};

#endif













