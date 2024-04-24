#include "admin_homepage.h"
#include "choix_principal.h"
#include "creer_compte.h"
#include "creer_profil.h"
#include "login.h"
#include "quel_client.h"
#include "quel_employe.h"
#include "quel_stagiaire.h"
#include "ui_admin_homepage.h"
#include "creer_utilisateur.h"
#include "user.h"
#include "qevent.h"
#include <QGuiApplication>

admin_homepage::admin_homepage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::admin_homepage)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);

    // Background transparent
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
}

admin_homepage::~admin_homepage()
{
    delete ui;
}

void admin_homepage::mousePressEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        cur_pos = event->globalPosition().toPoint();
    }
}

void admin_homepage::mouseMoveEvent(QMouseEvent *event) {
    if (ui->topbar->underMouse()) {
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void admin_homepage::setUserInformation(const User& user)
{
    // Style
    ui->ActionBtnName_9->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->ActionBtnName_14->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->ActionBtnName_11->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->ActionBtnName_12->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->LittleActionBtnName->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->LittleActionBtnName_2->setAttribute(Qt::WA_TransparentForMouseEvents);

    ui->labelFirstName_3->setText("Bienvenue " + user.getActual_firstname());
    currentUser = user;
}

void admin_homepage::on_cruser_adm_clicked()
{
    creer_utilisateur *CreerUtilisateur = new creer_utilisateur();
    CreerUtilisateur->show();
}


void admin_homepage::on_associer_adm_clicked()
{
    creer_compte *CreerCompte = new creer_compte();
    CreerCompte->show();
}


void admin_homepage::on_crprofil_adm_clicked()
{
    creer_profil *CreerProfil = new creer_profil();
    CreerProfil->show();
}



void admin_homepage::on_logcl_adm_clicked()
{
    quel_client *InfoClient = new quel_client();
    InfoClient->setUserInformations(currentUser);
    InfoClient->show();
}


void admin_homepage::on_logst_adm_clicked()
{
    quel_stagiaire *HistoStagiaire = new quel_stagiaire();
    HistoStagiaire->show();
}


void admin_homepage::on_logem_adm_clicked()
{
    quel_employe *HistoEmploye = new quel_employe();
    HistoEmploye->show();
}

void admin_homepage::on_close_adm_clicked()
{
    close();
}

void admin_homepage::on_reduced_adm_clicked()
{
    showMinimized();
}

void admin_homepage::on_fullscreen_adm_clicked()
{

}

void admin_homepage::on_logoff_clicked()
{
    Login *login = new class Login();
    login->show();
    close();
}


void admin_homepage::on_switchRole_clicked()
{
    choix_principal *choixPrincipal = new choix_principal();
    choixPrincipal->setUserInformation(currentUser);
    choixPrincipal->show();
    this->hide();
}

