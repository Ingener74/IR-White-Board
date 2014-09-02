/*
 * licenter.cpp
 *
 *  Created on: 22.07.2012
 *      Author: Ingener
 */

#include "licenter.h"
#include "md5.h"
#include <fstream>

using namespace std;

extern	char plcstr[];
extern	bool lc;

licenter::licenter(): QWidget() {
	ui.setupUi(this);

	connect(ui.pushButtonCheck, SIGNAL(clicked()), SLOT(checkLc()));
}

licenter::~licenter() {
}

void licenter::checkLc(){
	QString lcstrin = ui.lineEdit->text();

	string lchexbase;
	lchexbase.append(plcstr);

	string lcstring1 = lcstrin.toStdString();
	MD5 md(lcstring1);

	if(lchexbase.compare(md.hexdigest()) == 0){
		ofstream file;
		file.open("lc.data");
		if(file.is_open()){
			file << md.hexdigest();
		}
		file.flush();
		file.close();
	}
	close();
}
