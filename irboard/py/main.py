#!/usr/bin/env python
# -*- coding: utf-8 -*-

from PySide.QtGui import QMainWindow, QApplication

__author__ = 'Pavel'


class MainWindow(QMainWindow):
    def __init__(self):
        super(QMainWindow, self).__init__(self)

        print 'Паша'

        pass


def main():
    app = QApplication
    win = MainWindow()
    win.show()
    return app.exec_()
    pass


if __name__ == '__main__':
    main()