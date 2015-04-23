#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

from PySide.QtGui import QApplication, QMainWindow, QWidget

from MainWindow import Ui_MainWindow
from SettingsWindow import Ui_WindowSettings


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


def main():
    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()
    return app.exec_()


if __name__ == '__main__':
    main()