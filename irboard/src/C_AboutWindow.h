/*
 * C_AboutWindow.h
 *
 *  Created on: 14.07.2012
 *      Author: Ingener
 */

#ifndef C_ABOUTWINDOW_H_
#define C_ABOUTWINDOW_H_

#include <QtGui/qwidget.h>
#include <QtGui/QCloseEvent>

#include "ui_AboutWindow.h"

class C_AboutWindow: public QWidget {
	Q_OBJECT
public:
	C_AboutWindow();
	virtual ~C_AboutWindow();

	void closeEvent( QCloseEvent* pEvent );

private:
	Ui::formAbout ui;
};

#endif /* C_ABOUTWINDOW_H_ */
