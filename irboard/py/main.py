#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys

from PySide.QtGui import QApplication, QMainWindow, QWidget, QSystemTrayIcon, QMenu, QIcon

from MainWindow import Ui_MainWindow
from SettingsWindow import Ui_WindowSettings

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../../build/libirboard')))
import IrBoard as ir

class SettingsWindow(QWidget, Ui_WindowSettings):
    def __init__(self, parent=None):
        super(SettingsWindow, self).__init__(parent)
        self.setupUi(self)


class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)

        self.settings_window = SettingsWindow()

        self.ButtonSettings.clicked.connect(self.settings_window.show)
        self.ButtonCalibrate.clicked.connect(self.calibrate)
        self.ButtonToTray.clicked.connect(self.hide)
        
        self.ir_board = ir.IrBoard()
        print u"Версия библиотеки инфракрасная ручка ",self.ir_board.getVersion()


    def calibrate(self):
        print u"Калибровка"


def main():
    app = QApplication(sys.argv)
    win = MainWindow()
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