TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Nos_Fichiers/source/DisplayUtils.cpp \
        Nos_Fichiers/source/Game.cpp \
        Nos_Fichiers/source/GameUtils.cpp \
        Nos_Fichiers/source/InputUtils.cpp \
        Nos_Fichiers/source/MenuUtils.cpp \
        Nos_Fichiers/source/SettingUtils.cpp \
        main.cpp

HEADERS += \
    Nos_Fichiers/source/DisplayUtils.h \
    Nos_Fichiers/source/Game.h \
    Nos_Fichiers/source/GameUtils.h \
    Nos_Fichiers/source/InputUtils.h \
    Nos_Fichiers/source/MenuUtils.h \
    Nos_Fichiers/source/SettingUtils.h \
    Nos_Fichiers/source/types.h
