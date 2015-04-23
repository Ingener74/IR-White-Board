# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '../ui/SettingsWindow.ui'
#
# Created: Thu Apr 23 22:39:19 2015
#      by: pyside-uic 0.2.15 running on PySide 1.2.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_WindowSettings(object):
    def setupUi(self, WindowSettings):
        WindowSettings.setObjectName("WindowSettings")
        WindowSettings.resize(625, 515)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/main/main.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        WindowSettings.setWindowIcon(icon)
        self.verticalLayout = QtGui.QVBoxLayout(WindowSettings)
        self.verticalLayout.setObjectName("verticalLayout")
        self.tabWidget = QtGui.QTabWidget(WindowSettings)
        self.tabWidget.setObjectName("tabWidget")
        self.TabSensor = QtGui.QWidget()
        self.TabSensor.setFocusPolicy(QtCore.Qt.NoFocus)
        self.TabSensor.setAccessibleName("")
        self.TabSensor.setObjectName("TabSensor")
        self.verticalLayout_2 = QtGui.QVBoxLayout(self.TabSensor)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.groupBox = QtGui.QGroupBox(self.TabSensor)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Maximum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.groupBox.sizePolicy().hasHeightForWidth())
        self.groupBox.setSizePolicy(sizePolicy)
        self.groupBox.setFlat(False)
        self.groupBox.setCheckable(False)
        self.groupBox.setObjectName("groupBox")
        self.formLayout = QtGui.QFormLayout(self.groupBox)
        self.formLayout.setFieldGrowthPolicy(QtGui.QFormLayout.AllNonFixedFieldsGrow)
        self.formLayout.setObjectName("formLayout")
        self.label = QtGui.QLabel(self.groupBox)
        self.label.setObjectName("label")
        self.formLayout.setWidget(0, QtGui.QFormLayout.LabelRole, self.label)
        self.spinBoxCamera = QtGui.QSpinBox(self.groupBox)
        self.spinBoxCamera.setMinimum(0)
        self.spinBoxCamera.setMaximum(9)
        self.spinBoxCamera.setObjectName("spinBoxCamera")
        self.formLayout.setWidget(0, QtGui.QFormLayout.FieldRole, self.spinBoxCamera)
        self.label_2 = QtGui.QLabel(self.groupBox)
        self.label_2.setObjectName("label_2")
        self.formLayout.setWidget(1, QtGui.QFormLayout.LabelRole, self.label_2)
        self.comboBoxViewedImage = QtGui.QComboBox(self.groupBox)
        self.comboBoxViewedImage.setObjectName("comboBoxViewedImage")
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/main/webcam.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.comboBoxViewedImage.addItem(icon1, "")
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(":/main/pictures.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.comboBoxViewedImage.addItem(icon2, "")
        self.formLayout.setWidget(1, QtGui.QFormLayout.FieldRole, self.comboBoxViewedImage)
        self.verticalLayout_2.addWidget(self.groupBox)
        self.groupBoxThreshold = QtGui.QGroupBox(self.TabSensor)
        self.groupBoxThreshold.setObjectName("groupBoxThreshold")
        self.verticalLayout_4 = QtGui.QVBoxLayout(self.groupBoxThreshold)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.horizontalSliderThreshold = QtGui.QSlider(self.groupBoxThreshold)
        self.horizontalSliderThreshold.setMaximum(255)
        self.horizontalSliderThreshold.setProperty("value", 255)
        self.horizontalSliderThreshold.setSliderPosition(255)
        self.horizontalSliderThreshold.setOrientation(QtCore.Qt.Horizontal)
        self.horizontalSliderThreshold.setObjectName("horizontalSliderThreshold")
        self.verticalLayout_4.addWidget(self.horizontalSliderThreshold)
        self.verticalLayout_2.addWidget(self.groupBoxThreshold)
        self.labelSensorView = QtGui.QLabel(self.TabSensor)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.labelSensorView.sizePolicy().hasHeightForWidth())
        self.labelSensorView.setSizePolicy(sizePolicy)
        self.labelSensorView.setText("")
        self.labelSensorView.setPixmap(QtGui.QPixmap(":/main/no_web_camera_320240.png"))
        self.labelSensorView.setAlignment(QtCore.Qt.AlignCenter)
        self.labelSensorView.setObjectName("labelSensorView")
        self.verticalLayout_2.addWidget(self.labelSensorView)
        self.tabWidget.addTab(self.TabSensor, icon1, "")
        self.TabOtherSettings = QtGui.QWidget()
        self.TabOtherSettings.setObjectName("TabOtherSettings")
        self.verticalLayout_3 = QtGui.QVBoxLayout(self.TabOtherSettings)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.horizontalLayout_2 = QtGui.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.label_3 = QtGui.QLabel(self.TabOtherSettings)
        self.label_3.setObjectName("label_3")
        self.horizontalLayout_2.addWidget(self.label_3)
        self.spinBoxHorPoints = QtGui.QSpinBox(self.TabOtherSettings)
        self.spinBoxHorPoints.setMinimum(2)
        self.spinBoxHorPoints.setMaximum(5)
        self.spinBoxHorPoints.setProperty("value", 5)
        self.spinBoxHorPoints.setObjectName("spinBoxHorPoints")
        self.horizontalLayout_2.addWidget(self.spinBoxHorPoints)
        self.label_4 = QtGui.QLabel(self.TabOtherSettings)
        self.label_4.setObjectName("label_4")
        self.horizontalLayout_2.addWidget(self.label_4)
        self.spinBoxVetPoints = QtGui.QSpinBox(self.TabOtherSettings)
        self.spinBoxVetPoints.setMinimum(2)
        self.spinBoxVetPoints.setMaximum(4)
        self.spinBoxVetPoints.setProperty("value", 4)
        self.spinBoxVetPoints.setObjectName("spinBoxVetPoints")
        self.horizontalLayout_2.addWidget(self.spinBoxVetPoints)
        self.verticalLayout_3.addLayout(self.horizontalLayout_2)
        self.labelPointsPositions = QtGui.QLabel(self.TabOtherSettings)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Minimum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.labelPointsPositions.sizePolicy().hasHeightForWidth())
        self.labelPointsPositions.setSizePolicy(sizePolicy)
        self.labelPointsPositions.setAlignment(QtCore.Qt.AlignCenter)
        self.labelPointsPositions.setObjectName("labelPointsPositions")
        self.verticalLayout_3.addWidget(self.labelPointsPositions)
        self.tabWidget.addTab(self.TabOtherSettings, icon, "")
        self.verticalLayout.addWidget(self.tabWidget)
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.ButtonApply = QtGui.QPushButton(WindowSettings)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(2)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.ButtonApply.sizePolicy().hasHeightForWidth())
        self.ButtonApply.setSizePolicy(sizePolicy)
        icon3 = QtGui.QIcon()
        icon3.addPixmap(QtGui.QPixmap(":/main/apply.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ButtonApply.setIcon(icon3)
        self.ButtonApply.setIconSize(QtCore.QSize(24, 24))
        self.ButtonApply.setObjectName("ButtonApply")
        self.horizontalLayout.addWidget(self.ButtonApply)
        self.verticalLayout.addLayout(self.horizontalLayout)

        self.retranslateUi(WindowSettings)
        self.tabWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(WindowSettings)

    def retranslateUi(self, WindowSettings):
        WindowSettings.setWindowTitle(QtGui.QApplication.translate("WindowSettings", "Настройки", None, QtGui.QApplication.UnicodeUTF8))
        WindowSettings.setToolTip(QtGui.QApplication.translate("WindowSettings", "Окно настроек программы", None, QtGui.QApplication.UnicodeUTF8))
        self.groupBox.setTitle(QtGui.QApplication.translate("WindowSettings", "Настройки датчика:", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("WindowSettings", "Выбор датчика", None, QtGui.QApplication.UnicodeUTF8))
        self.label_2.setText(QtGui.QApplication.translate("WindowSettings", "Изображение с датчика:", None, QtGui.QApplication.UnicodeUTF8))
        self.comboBoxViewedImage.setItemText(0, QtGui.QApplication.translate("WindowSettings", "Оригинальное изображение", None, QtGui.QApplication.UnicodeUTF8))
        self.comboBoxViewedImage.setItemText(1, QtGui.QApplication.translate("WindowSettings", "Обработанное изображение", None, QtGui.QApplication.UnicodeUTF8))
        self.groupBoxThreshold.setTitle(QtGui.QApplication.translate("WindowSettings", "Порог датчика", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.TabSensor), QtGui.QApplication.translate("WindowSettings", "Настройки датчика", None, QtGui.QApplication.UnicodeUTF8))
        self.label_3.setText(QtGui.QApplication.translate("WindowSettings", "Точек по горизонтали: ", None, QtGui.QApplication.UnicodeUTF8))
        self.label_4.setText(QtGui.QApplication.translate("WindowSettings", "Точек по вертикали:", None, QtGui.QApplication.UnicodeUTF8))
        self.labelPointsPositions.setToolTip(QtGui.QApplication.translate("WindowSettings", "<html><head/><body><p>Расположение меток калибровки на экране</p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.labelPointsPositions.setText(QtGui.QApplication.translate("WindowSettings", "TextLabel", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.TabOtherSettings), QtGui.QApplication.translate("WindowSettings", "Прочие настройки", None, QtGui.QApplication.UnicodeUTF8))
        self.ButtonApply.setText(QtGui.QApplication.translate("WindowSettings", "Закрыть", None, QtGui.QApplication.UnicodeUTF8))

import MainResource_rc