#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
Добавить сохранение pyside-rcc.exe и pyside-uic.py в json файл
'''
import json
import os

import sys
import subprocess
from PySide.QtGui import QFileDialog, QApplication


def get_pyside_rcc():
    pyside_rcc, _ = QFileDialog.getOpenFileName(caption=u"Выбери pyside-rcc.exe")
    return pyside_rcc


def get_pyside_uic():
    pyside_uic, _ = QFileDialog.getOpenFileName(caption=u"Выбери pyside-uic.py")
    return pyside_uic


def main():
    app = QApplication(sys.argv)

    CONFIG_FILE       = 'config.json'
    CONFIG_PYSIDE_RCC = 'pyside_rcc'
    CONFIG_PYSIDE_UIC = 'pyside_uic'

    json_ = json.load(open(CONFIG_FILE, mode='r+'))

    pyside_rcc = json_[CONFIG_PYSIDE_RCC] if os.path.exists(json_[CONFIG_PYSIDE_RCC]) else get_pyside_rcc()
    pyside_uic = json_[CONFIG_PYSIDE_UIC] if os.path.exists(json_[CONFIG_PYSIDE_RCC]) else get_pyside_uic()

    subprocess.Popen([pyside_rcc, '../resources/MainResource.qrc', '-o', 'MainResource_rc.py'])
    subprocess.Popen(['python', pyside_uic, '../ui/MainWindow.ui', '-o', 'MainWindow.py'])
    subprocess.Popen(['python', pyside_uic, '../ui/SettingsWindow.ui', '-o', 'SettingsWindow.py'])
    subprocess.Popen(['python', pyside_uic, '../ui/ErrorLogWindow.ui', '-o', 'ErrorLogWindow.py'])

    json_[CONFIG_PYSIDE_RCC] = pyside_rcc
    json_[CONFIG_PYSIDE_UIC] = pyside_uic
    with open(CONFIG_FILE, 'w') as json_file:
        json.dump(json_, json_file, sort_keys=True, indent=4, separators=(',', ':'))

    app.quit()


if __name__ == '__main__':
    main()