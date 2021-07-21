# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

QT += widgets network
TEMPLATE = app
TARGET = TianLi_Launcher
RC_ICONS = MainIcon.ico
DESTDIR = ../x64/Release
CONFIG += release
LIBS += -L"."
DEPENDPATH += .
MOC_DIR += .
OBJECTS_DIR += release
UI_DIR += .
RCC_DIR += .
HEADERS += ./SingleApplication.h\
	./ModulesManager.h \
    ./VersionNumber.h \
    ./DownloadManager.h \
    ./resource.h \
    ./SettingData.h \
    ./GenshinImpactNaturalLaw.h \
    ./QtWidgetsSetting.h \
    ./UpdataModule.h \
    ./QtWidgetsMessageBox.h
SOURCES += ./SingleApplication.cpp\
	./DownloadManager.cpp \
    ./ModulesManager.cpp \
    ./QtWidgetsMessageBox.cpp \
    ./QtWidgetsSetting.cpp \
    ./SettingData.cpp \
    ./UpdataModule.cpp \
    ./VersionNumber.cpp \
    ./GenshinImpactNaturalLaw.cpp \
    ./main.cpp
FORMS += ./GenshinImpactNaturalLaw.ui \
    ./QtWidgetsMessageBox.ui \
    ./QtWidgetsSetting.ui
RESOURCES += GenshinImpactNaturalLaw.qrc \
    QtWidgetsMessageBox.qrc \
    QtWidgetsSetting.qrc
# QMAKE_CXXFLAGS += -charset:utf-8