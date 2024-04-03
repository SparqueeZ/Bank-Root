QT       += core gui sql
QT += xml


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin_homepage.cpp \
    choix_principal.cpp \
    consulter_client.cpp \
    consulter_client_stagiaire.cpp \
    credit.cpp \
    creer_compte.cpp \
    creer_profil.cpp \
    creer_utilisateur.cpp \
    debit.cpp \
    employe_homepage.cpp \
    historique_employe.cpp \
    historique_stagiaire.cpp \
    home.cpp \
    main.cpp \
    login.cpp \
    operations.cpp \
    stagiaire_homepage.cpp \
    user.cpp \
    virement.cpp

HEADERS += \
    admin_homepage.h \
    choix_principal.h \
    consulter_client.h \
    consulter_client_stagiaire.h \
    credit.h \
    creer_compte.h \
    creer_profil.h \
    creer_utilisateur.h \
    debit.h \
    employe_homepage.h \
    historique_employe.h \
    historique_stagiaire.h \
    home.h \
    login.h \
    operations.h \
    stagiaire_homepage.h \
    user.h \
    virement.h

FORMS += \
    admin_homepage.ui \
    choix_principal.ui \
    consulter_client.ui \
    consulter_client_stagiaire.ui \
    credit.ui \
    creer_compte.ui \
    creer_profil.ui \
    creer_utilisateur.ui \
    debit.ui \
    employe_homepage.ui \
    historique_employe.ui \
    historique_stagiaire.ui \
    home.ui \
    login.ui \
    stagiaire_homepage.ui \
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
