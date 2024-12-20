QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    adminwindow.cpp \
    database.cpp \
    lecturer.cpp \
    lecturerwindow.cpp \
    login.cpp \
    loginwindow.cpp \
    main.cpp \
    student.cpp \
    studentswindow.cpp \
    user.cpp

HEADERS += \
    admin.h \
    adminwindow.h \
    database.h \
    lecturer.h \
    lecturerwindow.h \
    login.h \
    loginwindow.h \
    student.h \
    studentswindow.h \
    user.h

FORMS += \
    adminwindow.ui \
    lecturerwindow.ui \
    loginwindow.ui \
    studentswindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT += core gui sql
QT += widgets
QMAKE_CXXFLAGS += -frtti
