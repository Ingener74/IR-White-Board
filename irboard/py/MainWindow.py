# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '../ui/MainWindow.ui'
#
# Created: Thu Apr 23 23:30:07 2015
#      by: pyside-uic 0.2.15 running on PySide 1.2.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(364, 406)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/main/webcam.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        MainWindow.setWindowIcon(icon)
        MainWindow.setTabShape(QtGui.QTabWidget.Triangular)
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout_2 = QtGui.QVBoxLayout(self.centralwidget)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.labelMainImage = QtGui.QLabel(self.centralwidget)
        self.labelMainImage.setText("")
        self.labelMainImage.setPixmap(QtGui.QPixmap(":/main/hourglass.png"))
        self.labelMainImage.setAlignment(QtCore.Qt.AlignCenter)
        self.labelMainImage.setObjectName("labelMainImage")
        self.verticalLayout_2.addWidget(self.labelMainImage)
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setSizeConstraint(QtGui.QLayout.SetMaximumSize)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.ButtonCalibrate = QtGui.QPushButton(self.centralwidget)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Minimum)
        sizePolicy.setHorizontalStretch(3)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.ButtonCalibrate.sizePolicy().hasHeightForWidth())
        self.ButtonCalibrate.setSizePolicy(sizePolicy)
        self.ButtonCalibrate.setWhatsThis("")
        self.ButtonCalibrate.setStyleSheet("")
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/main/calibrate.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ButtonCalibrate.setIcon(icon1)
        self.ButtonCalibrate.setIconSize(QtCore.QSize(96, 96))
        self.ButtonCalibrate.setObjectName("ButtonCalibrate")
        self.horizontalLayout.addWidget(self.ButtonCalibrate)
        self.verticalLayout = QtGui.QVBoxLayout()
        self.verticalLayout.setSizeConstraint(QtGui.QLayout.SetMaximumSize)
        self.verticalLayout.setObjectName("verticalLayout")
        self.ButtonSettings = QtGui.QPushButton(self.centralwidget)
        self.ButtonSettings.setText("")
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(":/main/cogwheel.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ButtonSettings.setIcon(icon2)
        self.ButtonSettings.setIconSize(QtCore.QSize(48, 48))
        self.ButtonSettings.setObjectName("ButtonSettings")
        self.verticalLayout.addWidget(self.ButtonSettings)
        self.ButtonToTray = QtGui.QPushButton(self.centralwidget)
        self.ButtonToTray.setText("")
        icon3 = QtGui.QIcon()
        icon3.addPixmap(QtGui.QPixmap(":/main/totray.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ButtonToTray.setIcon(icon3)
        self.ButtonToTray.setIconSize(QtCore.QSize(48, 48))
        self.ButtonToTray.setObjectName("ButtonToTray")
        self.verticalLayout.addWidget(self.ButtonToTray)
        self.horizontalLayout.addLayout(self.verticalLayout)
        self.verticalLayout_2.addLayout(self.horizontalLayout)
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QtGui.QApplication.translate("MainWindow", "Интерактивная ручка", None, QtGui.QApplication.UnicodeUTF8))
        MainWindow.setToolTip(QtGui.QApplication.translate("MainWindow", "Интерактивная ручка", None, QtGui.QApplication.UnicodeUTF8))
        self.ButtonCalibrate.setToolTip(QtGui.QApplication.translate("MainWindow", "Кнопка выполнения калибровки", None, QtGui.QApplication.UnicodeUTF8))
        self.ButtonCalibrate.setText(QtGui.QApplication.translate("MainWindow", "Калибровка", None, QtGui.QApplication.UnicodeUTF8))
        self.ButtonSettings.setToolTip(QtGui.QApplication.translate("MainWindow", "Настройки программы", None, QtGui.QApplication.UnicodeUTF8))
        self.ButtonToTray.setToolTip(QtGui.QApplication.translate("MainWindow", "Свернуть программу в трей", None, QtGui.QApplication.UnicodeUTF8))

import MainResource_rc
import MainResource_rc
