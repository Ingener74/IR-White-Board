#!/bin/bash

qt5_include=`zenity --text='Select Qt5 include directory' --file-selection --directory`
build_type=`zenity --list --text='Select DCMAKE_BUILD_TYPE' --column='Build types' Release Debug`

cmake .. -DCMAKE_PREFIX_PATH=$(qt5_include) -DCMAKE_BUILD_TYPE=$(build_type)
