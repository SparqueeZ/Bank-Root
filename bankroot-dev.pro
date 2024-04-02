QT       += core gui sql
QT += xml


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    credit.cpp \
    debit.cpp \
    home.cpp \
    main.cpp \
    login.cpp \
    operations.cpp \
    user.cpp \
    virement.cpp

HEADERS += \
    credit.h \
    debit.h \
    home.h \
    login.h \
    operations.h \
    user.h \
    virement.h

FORMS += \
    credit.ui \
    debit.ui \
    home.ui \
    login.ui \
    virement.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Fichier de ressources (assets)
RESOURCES += \
    ressource.qrc
# Icone de l'app
RC_ICONS = assets/logo.ico
