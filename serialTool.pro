QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    devicecombo.cpp \
    serialdevicelistmodel.cpp \
    statusbar.cpp \
    sessionmanager.cpp \
    datadisplay.cpp \
    datahighlighter.cpp \
    searchpanel.cpp \
    timeview.cpp \
    ctrlcharacterspopup.cpp \
    plugin.cpp \
    pluginmanager.cpp \
    macroplugin.cpp \
    macrosettings.cpp \
    netproxyplugin.cpp \
    netproxysettings.cpp \
    counterplugin.cpp \
    controlpanel.cpp

HEADERS  += mainwindow.h \
    controlpanel.h \
    settings.h \
    devicecombo.h \
    serialdevicelistmodel.h \
    statusbar.h \
    sessionmanager.h \
    datadisplay.h \
    datahighlighter.h \
    searchpanel.h \
    timeview.h \
    ctrlcharacterspopup.h \
    plugin.h \
    pluginmanager.h \
    macroplugin.h \
    macrosettings.h \
    netproxyplugin.h \
    netproxysettings.h \
    counterplugin.h
    
    
FORMS    += mainwindow.ui \
    controlpanel.ui \
    statusbar.ui \
    sessionmanager.ui \
    searchpanel.ui \
    macroplugin.ui \
    netproxyplugin.ui \
    macrosettings.ui \
    netproxysettings.ui \
    counterplugin.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    qt.astylerc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
