QT       += core gui sql network
QT += xml


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_beneficiaire.cpp \
    admin_homepage.cpp \
    centralbank.cpp \
    choix_principal.cpp \
    credit.cpp \
    credit_admin.cpp \
    creer_compte.cpp \
    creer_profil.cpp \
    creer_utilisateur.cpp \
    debit.cpp \
    debit_admin.cpp \
    employe_homepage.cpp \
    f_admin.cpp \
    historique_employe.cpp \
    historique_stagiaire.cpp \
    home.cpp \
    informations_client.cpp \
    informations_client_stag.cpp \
    main.cpp \
    login.cpp \
    operations.cpp \
    quel_client.cpp \
    quel_employe.cpp \
    quel_stagiaire.cpp \
    stagiaire_homepage.cpp \
    user.cpp \
    virement.cpp

HEADERS += \
    add_beneficiaire.h \
    admin_homepage.h \
    centralbank.h \
    choix_principal.h \
    credit.h \
    credit_admin.h \
    creer_compte.h \
    creer_profil.h \
    creer_utilisateur.h \
    debit.h \
    debit_admin.h \
    employe_homepage.h \
    f_admin.h \
    historique_employe.h \
    historique_stagiaire.h \
    home.h \
    informations_client.h \
    informations_client_stag.h \
    login.h \
    operations.h \
    quel_client.h \
    quel_employe.h \
    quel_stagiaire.h \
    stagiaire_homepage.h \
    user.h \
    virement.h

FORMS += \
    add_beneficiaire.ui \
    admin_homepage.ui \
    choix_principal.ui \
    credit.ui \
    credit_admin.ui \
    creer_compte.ui \
    creer_profil.ui \
    creer_utilisateur.ui \
    debit.ui \
    debit_admin.ui \
    employe_homepage.ui \
    historique_employe.ui \
    historique_stagiaire.ui \
    home.ui \
    informations_client.ui \
    informations_client_stag.ui \
    login.ui \
    quel_client.ui \
    quel_employe.ui \
    quel_stagiaire.ui \
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
