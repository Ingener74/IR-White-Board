/*
 * C_AboutWindow.cpp
 *
 *  Created on: 14.07.2012
 *      Author: Ingener
 */

#include <AboutWindow.h>

AboutWindow::AboutWindow() :
        QWidget()
{
    _ui.setupUi(this);
}

AboutWindow::~AboutWindow()
{
}

//////////////////////////////////////////////////////////////////////////
void AboutWindow::closeEvent(QCloseEvent* pEvent)
{
    pEvent->ignore();
    hide();
}
