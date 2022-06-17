QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += openglwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32: LIBS += -lopengl32
include(QtGifImage-master/src/gifimage/qtgifimage.pri)

SOURCES += \
    gl_view.cpp \
    main.cpp \
    mainwindow.cpp \
    models/affinity.c \
    models/data.c \
    models/s21_matrix.c \
    models/objparser.c \
    models/polygons.c \
    models/string_util.c \
    s21_conf.c

HEADERS += \
    gl_view.h \
    mainwindow.h \
    models/affinity.h \
    models/data.h \
    models/s21_matrix.h \
    models/objparser.h \
    models/polygons.h \
    models/string_util.h \
    s21_conf.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
