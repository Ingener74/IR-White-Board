#ifndef LICENTER_H_
#define LICENTER_H_

#include <QtGui/qwidget.h>
#include "ui_lic.h"

class licenter: public QWidget {
	Q_OBJECT
public:
	licenter();
	virtual ~licenter();

public slots:
	void checkLc();

private:
	Ui::licForm ui;
};

#endif /* LICENTER_H_ */
