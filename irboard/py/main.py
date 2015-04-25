#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys

from PySide.QtGui import QApplication, QMainWindow, QWidget, QSystemTrayIcon, QMenu, QIcon, QImage, QPixmap

from MainWindow import Ui_MainWindow
from SettingsWindow import Ui_WindowSettings

# sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../../build/libirboard')))
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), 'C:/Users/Pavel/.clion10/system/cmake/generated/ad0f564e/ad0f564e/Debug/libirboard')))
import IrBoard as ir

class TestImageOutput(ir.ImageOutput):
    def __init__(self, settings_window):
        ir.ImageOutput.__init__(self)

        self._settings_window = settings_window

    def updateImage(self, data, width, height):
        print 'image: ', width, ' x ', height
        # if(self._settings_window.isVisible):
            # self._settings_window.draw_image(data, width, height)

class SettingsWindow(QWidget, Ui_WindowSettings):
    def __init__(self, parent=None):
        super(SettingsWindow, self).__init__(parent)
        self.setupUi(self)

        # self.comboBoxViewedImage.

    def draw_image(self, data, width, height):
        image = QImage(buffer(data), width, height, QImage.Format_RGB888)
        self.labelSensorView.setPixmap(QPixmap.fromImage(image))

class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, settings, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)

        self.settings_window = settings

        self.ButtonSettings.clicked.connect(self.settings_window.show)
        self.ButtonCalibrate.clicked.connect(self.calibrate)
        self.ButtonToTray.clicked.connect(self.hide)



    def calibrate(self):
        print u"Калибровка"


def main():
    app = QApplication(sys.argv)

    settings = SettingsWindow()

    image_output = TestImageOutput(settings)
    ir_board = ir.IrBoard(image_output)
    print u"Версия библиотеки инфракрасная ручка ",ir_board.getVersion()

    win = MainWindow(settings)
    win.show()

    tray_menu = QMenu()
    tray_menu.addAction(QIcon(':/main/restore.png'), u"Восстановить", win.show)
    tray_menu.addAction(QIcon(':/main/calibrate.png'), u"Калибровка", win.calibrate)
    tray_menu.addAction(QIcon(':/main/cogwheel.png'), u"Настройка", win.settings_window.show)
    tray_menu.addSeparator()
    tray_menu.addAction(QIcon(':/main/close.png'), u"Выход", app.quit)

    tray = QSystemTrayIcon()
    tray.setIcon(QIcon(':/main/webcam.png'))
    tray.setContextMenu(tray_menu)
    tray.show()

    return app.exec_()


if __name__ == '__main__':
    main()