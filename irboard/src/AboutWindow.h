/*
 * C_AboutWindow.h
 *
 *  Created on: 14.07.2012
 *      Author: Ingener
 */

#ifndef C_ABOUTWINDOW_H_
#define C_ABOUTWINDOW_H_

#include <QtWidgets/QWidget>
#include <QtGui/QCloseEvent>

#include <ui_AboutWindow.h>

class AboutWindow: public QWidget
{
Q_OBJECT
public:
    AboutWindow();
    virtual ~AboutWindow();

    void closeEvent(QCloseEvent* pEvent);

private:
    Ui::formAbout _ui;
};

#endif /* C_ABOUTWINDOW_H_ */
