/*
 * C_AboutWindow.cpp
 *
 *  Created on: 14.07.2012
 *      Author: Ingener
 */

#include "C_AboutWindow.h"

C_AboutWindow::C_AboutWindow(): QWidget() {
	ui.setupUi(this);
}

C_AboutWindow::~C_AboutWindow() {
	// TODO Auto-generated destructor stub
}

//////////////////////////////////////////////////////////////////////////
void C_AboutWindow::closeEvent( QCloseEvent* pEvent )
{
	pEvent->ignore();
	hide();
}
