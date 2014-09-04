//============================================================================
// Name        : MainWindow.cpp
// Author      : Shnayder Pavel aka Ingener74
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <QtWidgets/QMenu>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QGraphicsPixmapItem>

#include <QtGui/QIcon>
#include <QtGui/QPixmap>
#include <QtGui/QCloseEvent>

#include <QtCore/QTimer>
#include <QtCore/QString>
#include <QtCore/QTextCodec>

#include <MainWindow.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::MainWindow(shared_ptr<QApplication> app, QWidget *parent /*= 0*/, Qt::WindowFlags flags /*= 0 */) :
        QMainWindow(parent, flags), _app(app)
{
    _ui.setupUi(this);

//	calibrationPoints = Size_<unsigned int>(5,4);
//
//	screenResolution = getSystemResolution();
//
//	pCoordinateTransform = new C_CoordinateTransform(wstring(L"tm.data"), screenResolution);
//	if(pCoordinateTransform->GetStatus()==E_ctssEMPTY){
//		delete pCoordinateTransform;
//		pCoordinateTransform = 0;
//	}else{
////		imwrite("tm_data.png", pCoordinateTransform->getImageRepresentation());
//	}
//
//	QTextCodec *codec = QTextCodec::codecForName("cp1251");
//	QTextCodec::setCodecForTr(codec);

    _settingsWindow = make_shared<SettingsWindow>();
    _settingsWindow->setWindowFlags(_settingsWindow->windowFlags() & ~(Qt::WindowMinimizeButtonHint));
    _settingsWindow->setWindowFlags(_settingsWindow->windowFlags() &~(Qt::WindowMaximizeButtonHint));

//	pAboutWindow = new C_AboutWindow();

    _calibrationWindow = make_shared<CalibrationWindow>();

    _systemTrayMenu = make_shared<QMenu>();

    _systemTrayMenuRestore = shared_ptr<QAction>(
            _systemTrayMenu->addAction(QIcon(QString::fromUtf8(":/main/restore.png")), QObject::tr("Restore")));

    _systemTrayMenu->addSeparator();

    _systemTrayMenuCalibration = shared_ptr<QAction>(
            _systemTrayMenu->addAction(QIcon(QString::fromUtf8(":/main/calibrate.png")), QObject::tr("Calibrate")));
    _systemTrayMenuSettings = shared_ptr<QAction>(
            _systemTrayMenu->addAction(QIcon(QString::fromUtf8(":/main/cogwheel.png")), QObject::tr("Settings")));

    _systemTrayMenu->addSeparator();

    _systemTrayMenuAbout = shared_ptr<QAction>(
            _systemTrayMenu->addAction(QIcon(QString::fromUtf8(":/main/help.png")), QObject::tr("About")));

    _systemTrayMenu->addSeparator();

    _systemTrayMenuClose = shared_ptr<QAction>(
            _systemTrayMenu->addAction(QIcon(QString::fromUtf8(":/main/close.png")), QObject::tr("Close")));

    QIcon oTrayIcon;
    oTrayIcon.addFile(QString::fromUtf8(":/main/webcam.png"), QSize(), QIcon::Normal, QIcon::Off);
    _systemTray = make_shared<QSystemTrayIcon>(oTrayIcon);
    _systemTray->setContextMenu(_systemTrayMenu.get());
    _systemTray->show();

//	QObject::connect(this,								SIGNAL(signalPulledOut()),			this,					SLOT(slotPulledOut())			);
//
//	QObject::connect(this,								SIGNAL(signalSystemNoCamera()),		this,					SLOT(slotSystemNoCamera())		);
//	QObject::connect(this,								SIGNAL(signalSystemNoCamera()),		pSettingsWindow,		SLOT(slotSettingsNoCamera())	);

    QObject::connect(_ui.ButtonSettings,                SIGNAL(clicked()),               _settingsWindow.get(),     SLOT(show())                    );
    QObject::connect(_systemTrayMenuSettings.get(),     SIGNAL(triggered()),             _settingsWindow.get(),     SLOT(show())                    );

    QObject::connect(_systemTrayMenuClose.get(),        SIGNAL(triggered()),             this,                      SLOT(close())                   );

    QObject::connect(_ui.ButtonToTray,                  SIGNAL(clicked()),               this,                      SLOT(hide())                    );
    QObject::connect(_systemTrayMenuRestore.get(),      SIGNAL(triggered()),             this,                      SLOT(show())                    );

//	QObject::connect(ui.ButtonCalibrate,					SIGNAL(clicked()),					this,					SLOT(Calibration())				);
//	QObject::connect(pSystemTrayMenuCalibration,			SIGNAL(triggered()),				this,					SLOT(Calibration())				);
//
//	QObject::connect(pSystemTrayMenuAbout,				SIGNAL(triggered()),				pAboutWindow,			SLOT(show())					);
//
//	QObject::connect(pSettingsWindow,					SIGNAL(signalSettingsCaptureNoExist()),this,					SLOT(slotSystemNoCamera())		);
//
//	QObject::connect(this,								SIGNAL(signalAllOk()),				this,					SLOT(slotSystemAllOk())			);
//	QObject::connect(this,								SIGNAL(signalCalibrationIsNeeded()),this,					SLOT(slotSystemNotCalibrated())	);
//
//	pRawMouse = new C_RawMouse();
//
//	pVideoCapture = new VideoCapture();
//	pVideoCapture->open(uiCurrentCamera);
//
//	if(!pVideoCapture->isOpened()){
////		slotSystemNoCamera();
//		emit signalSystemNoCamera();
//
//	}else{
//		captureExist = true;
//		if( pCoordinateTransform != 0 ){
//			if(pCoordinateTransform->GetStatus()==E_ctssCALIBRATED){
//				slotSystemAllOk();
//			}else{
//				slotSystemNotCalibrated();
//			}
//		}else{
//			slotSystemNotCalibrated();
//		}
//
//		captureTimer = startTimer(1000 / fps);
//	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MainWindow::~MainWindow()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::closeEvent(QCloseEvent* pEvent)
{
//	if(pVideoCapture != 0){
//		pVideoCapture->release();
//		delete pVideoCapture;
//	}
//	if(plicense != 0)
//		plicense->close();
//	if(pCoordinateTransform!=0)
//		pCoordinateTransform->SaveTransformationMatrix(wstring(L"tm.data"));

    _settingsWindow->close();
    _systemTray->hide();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::timerEvent(QTimerEvent* pEvent)
{
	// check system resolution
//	Size_<unsigned int> res = getSystemResolution();
//	if( res != screenResolution ){
//		slotSystemNotCalibrated();
//		screenResolution = res;
//	}
	// end check system resolution

	//                fps * sec * min  -> to reset in correct camera checking every 10 minutes
//	if(lFullCounter > fps * 60  * 10){
//		lFullCounter = 1;
//		lInCorrentCounter = 0;
//	}
//
//	if(uiNextCamera != uiCurrentCamera){
//
//		// for incorrect checking
//		lFullCounter=1;
//		lInCorrentCounter=0;
//		// end checking
//
//		uiCurrentCamera = uiNextCamera;
//
//		captureExist = false;
//
//		pVideoCapture->release();
//		delete pVideoCapture; pVideoCapture = 0;
//		pVideoCapture = new VideoCapture();
//		pVideoCapture->open(uiCurrentCamera);
//
//		if(!pVideoCapture->isOpened()){
//			captureExist=false;
//			emit signalSystemNoCamera();
//		}else{
//			captureExist=true;
//		}
//
//	}

//	if( pEvent->timerId() == captureTimer ){
//		if(captureExist){
//			if(pVideoCapture->grab()){
//				if(pVideoCapture->retrieve(inputImage)){
//					if(inputImage.cols != 0 && inputImage.rows != 0){
//
//						if(bshown){
//							pSettingsWindow->slotDrawSensorImage(inputImage);
//						}
//
//						// pulled out checking
////						if(poutcheck.Check(inputImage)){
////							emit signalPulledOut();
////						}
//						// end pulled out checking
//
//						cvtColor(inputImage, mono, CV_BGR2GRAY);
//						threshold(mono, thresh, uiThreshold, (unsigned char)(-1), CV_THRESH_BINARY);
//
//						vector<vector<Point> >	contours;
//						findContours(thresh, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//
//						outImage = Mat(thresh.size(), CV_8UC3, Scalar(0));
//						cvtColor(thresh, outImage, CV_GRAY2BGR);
//
//						drawContours(outImage, contours, -1, CV_RGB(0, 255, 0), 1);
//
//						// contour processing for search right contour appropriate flash from pen
//
//						// first way is find most of contour and send raw mouse his center mass and area
//						// second way is search right contour metod interrelation function
//
//						if(!contours.empty()){
//
//							// check that the correct camera
//							if( ProbablyWroneCamera(contours, thresh) ){
//								lInCorrentCounter++;
//							}
//							lFullCounter++;
//							// end check
//
//							unsigned int maxi=0,maxlen=0;
//							for(unsigned int i=0;i<contours.size();++i){
//								if(contours[i].size()>maxlen){
//									maxlen=contours[i].size();
//									maxi=i;
//								}
//							}
//							float maxarea=contourArea(contours[maxi]);
//							Moments mom = moments(contours[maxi]);
//							float cx = mom.m10 / mom.m00, cy = mom.m01 / mom.m00;
//
//							if( (int)cx < inputImage.cols &&
//								(int)cx >= 0 &&
//								(int)cy < inputImage.rows &&
//								(int)cy >= 0 ){
//
//								lastRawPosition = Point2f(cx, cy);
//
//								circle(outImage, Point(lastRawPosition.x, lastRawPosition.y), 2, CV_RGB(255, 255, 0), -1);
//
//								maxarea /= (outImage.cols*outImage.rows);
//
//								pRawMouse->Process(lastRawPosition, true, maxarea);
//							}
//
//						}else if(contours.empty()){
//							pRawMouse->Process(lastRawPosition, false, 0);
//						}
//
//					}
//				}
//			}
//		}
//	}else if(pEvent->timerId() == findCaptureTimer){
//		// capture device not opened or not exist in system, then we try to open default device or check every 500 ms to exist default
//
//		if(pVideoCapture != 0){
//			captureExist=false;
//			pVideoCapture->release();
//			delete pVideoCapture; pVideoCapture = 0;
//		}
//
//		pVideoCapture = new VideoCapture;
//
//		pVideoCapture->open(uiCurrentCamera);
//
//		if(!pVideoCapture->isOpened()){
//			captureExist=false;
//		}else{
//			if(pVideoCapture->grab()){
//				if(pVideoCapture->retrieve(inputImage)){
//					if(inputImage.cols!=0&&inputImage.rows!=0){
//						captureExist=true;
//
//						emit signalCalibrationIsNeeded();
//					}else{
//						captureExist=false;
//					}
//				}
//			}
//		}
//
//////		if(!bshown){
////			oVideoCapturer.open(uiCurrentCamera);
////			if(oVideoCapturer.isOpened()){
////				if(Size_<unsigned int>(oVideoCapturer.get(CV_CAP_PROP_FRAME_WIDTH), oVideoCapturer.get(CV_CAP_PROP_FRAME_HEIGHT)) != Size_<unsigned int>(0, 0) ){
////					captureExist = true;
////
////					// emit signal all ok or need to calibrate
////
////				}
////			}
//////		}
//	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::Calibration(void)
{
//	if(pCoordinateTransform != 0){ // for new calibration matrix clear old
//		delete pCoordinateTransform;
//		pCoordinateTransform = 0;
//	}
//	pCoordinateTransform = new C_CoordinateTransform(
//			outImage.size(),
//			screenResolution,
//			Size_<unsigned int>(5, 4)
//			);
//
//	pRawMouse->SetLeftDownCallBack(CoordinateTransformCalibrationOnLeftDown);
//	pRawMouse->SetLeftUpCallBack(0);
//	pRawMouse->SetMoveCallBack(0);
//	pRawMouse->SetRightDownCallBack(0);
//	pRawMouse->SetRightUpCallBack(0);
//
//	pCalibrationWindow->showFullScreen();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::slotSystemNoCamera()
{
//	if(pRawMouse!=0){
//		pRawMouse->SetLeftDownCallBack(0);
//		pRawMouse->SetLeftUpCallBack(0);
//		pRawMouse->SetMoveCallBack(0);
//		pRawMouse->SetRightDownCallBack(0);
//		pRawMouse->SetRightUpCallBack(0);
//	}
//
//	if(findCaptureTimer==0){
//		findCaptureTimer = startTimer(500);
//	}
//
//	ui.labelMainImage->setPixmap(QPixmap(QString(":/main/no_web_camera.png")));
//
//	pSystemTray->showMessage(QObject::tr("������������� �����"), QObject::tr("��� ����� �������..."), QSystemTrayIcon::Information, 1000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::slotSystemAllOk()
{
//	if(pRawMouse!=0){
//		pRawMouse->SetLeftDownCallBack(CoordinateTransformWorkOnLeftDown);
//		pRawMouse->SetLeftUpCallBack(CoordinateTransformWorkOnLeftUp);
//		pRawMouse->SetMoveCallBack(CoordinateTransformWorkOnMove);
//		pRawMouse->SetRightDownCallBack(CoordinateTransformWorkOnRightDown);
//		pRawMouse->SetRightUpCallBack(CoordinateTransformWorkOnRightUp);
//	}
//
//	if(findCaptureTimer!=0){
//		killTimer(findCaptureTimer);
//		findCaptureTimer=0;
//	}
//
//	if(captureTimer==0){
//		captureTimer = startTimer(500);
//	}
//
//	this->hide();
//
//	ui.labelMainImage->setPixmap(QPixmap(QString(":/main/allok.png")));
//
//	pSystemTray->showMessage(QObject::tr("������������� �����"), QObject::tr("������� � ������� ���������"), QSystemTrayIcon::Information, 1000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::slotSystemNotCalibrated()
{
//	if(findCaptureTimer!=0){
//		killTimer(findCaptureTimer);
//		findCaptureTimer=0;
//	}
//
//	if(captureTimer==0){
//		captureTimer = startTimer(500);
//	}
//	if(pRawMouse!=0){
//		pRawMouse->SetLeftDownCallBack(0);
//		pRawMouse->SetLeftUpCallBack(0);
//		pRawMouse->SetMoveCallBack(0);
//		pRawMouse->SetRightDownCallBack(0);
//		pRawMouse->SetRightUpCallBack(0);
//	}
//
//	show();
//
//	ui.labelMainImage->setPixmap(QPixmap(QString::fromUtf8(":/main/calibrate.png")));
//
//	pSystemTray->showMessage(QObject::tr("������������� �����"), QObject::tr("���������� ����������"), QSystemTrayIcon::Information, 1000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void CoordinateTransformCalibrationOnLeftDown( Point2f A_rPoint ){
//	pCoordinateTransform->OnLeftDown(A_rPoint);
//	if( pCoordinateTransform->GetStatus() == E_ctssREADY ){
//		// after calibration
//		pCalibrationWindow->close();
//
//		pCoordinateTransform->CalcTransformationMatrix();
//
//		if(pCoordinateTransform->GetStatus()==E_ctssCALIBRATED){
//
//			// all ok
//			pMainWindow->slotSystemAllOk();
//		}
//	}
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Size_<unsigned int> getSystemResolution() {
//	QDesktopWidget desk;
//	QRect systemRes = desk.screenGeometry();
//	return Size_<unsigned int>( systemRes.width(), systemRes.height() );
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void CoordinateTransformWorkOnLeftDown( Point2f A_rPoint )
//{
//	if(lc){
//		Point2i oPoint = pCoordinateTransform->GetCoordinate(A_rPoint);
//		if ( oPoint != Point(0, 0) )
//		{
//			oPoint = Point( oPoint.x, screenResolution.height - oPoint.y );
//
//			DisplayMouseLeftDown(oPoint, screenResolution);
//		}
//	}
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void CoordinateTransformWorkOnLeftUp( Point2f A_rPoint )
//{
//	if(lc){
//		Point oPoint = pCoordinateTransform->GetCoordinate(A_rPoint);
//		oPoint = Point( oPoint.x, screenResolution.height - oPoint.y );
//		DisplayMouseLeftUp(oPoint, screenResolution);
//	}
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void CoordinateTransformWorkOnMove( Point2f A_rPoint )
//{
//	Point oPoint = pCoordinateTransform->GetCoordinate(A_rPoint);
//	if ( oPoint != Point(0, 0) )
//	{
//		oPoint = Point( oPoint.x, screenResolution.height - oPoint.y );
//
//		DisplayMouseMove(oPoint, screenResolution);
//	}
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void CoordinateTransformWorkOnRightDown( Point2f A_rPoint )
//{
//	if(lc){
//		Point oPoint = pCoordinateTransform->GetCoordinate(A_rPoint);
//		if ( oPoint != Point(0, 0) )
//		{
//			oPoint = Point( oPoint.x, screenResolution.height - oPoint.y );
//			DisplayMouseRightDown(oPoint, screenResolution);
//		}
//	}
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void CoordinateTransformWorkOnRightUp( Point2f A_rPoint )
//{
//	if(lc){
//		Point oPoint = pCoordinateTransform->GetCoordinate(A_rPoint);
//		oPoint = Point( oPoint.x, screenResolution.height - oPoint.y );
//		DisplayMouseRightUp(oPoint, screenResolution);
//	}
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//bool ProbablyWroneCamera(vector<vector<Point> >& contours, Mat& threshImage){
//
//	float fSumArea=0;
//	for(unsigned int i=0;i<contours.size();++i){
//		fSumArea += contourArea(contours[i]);
//	}
//
//	if( fSumArea > (threshImage.cols * threshImage.rows * 0.03) && contours.size() > 3 )
//		return true;
//	else
//		return false;
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::slotPulledOut()
{
}

void MainWindow::putImage(cv::Mat)
{
}
