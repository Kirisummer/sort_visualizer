QT += core gui
CONFIG += c++17
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    bubblesortmodel.cpp \
    insertsortmodel.cpp \
    main.cpp \
    mainwindow.cpp \
    sortcontrol.cpp \
    sortmodel.cpp \
    sortview.cpp

HEADERS += \
    bubblesortmodel.h \
    insertsortmodel.h \
    mainwindow.h \
    sortcontrol.h \
    sortdef.h \
    sortmodel.h \
    sortview.h

FORMS += \
    mainwindow.ui \
    sortcontrol.ui \
    sortview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
