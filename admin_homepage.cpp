#include "admin_homepage.h"
#include "creer_compte.h"
#include "creer_profil.h"
#include "historique_employe.h"
#include "historique_stagiaire.h"
#include "informations_client.h"
#include "qscreen.h"
#include "quel_client.h"
#include "quel_employe.h"
#include "quel_stagiaire.h"
#include "ui_admin_homepage.h"
#include "creer_utilisateur.h"

admin_homepage::admin_homepage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::admin_homepage)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);


}

admin_homepage::~admin_homepage()
{
    delete ui;
}

void admin_homepage::setUserInformation(const User& user)
{
    // Style
    ui->ActionBtnName_9->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->ActionBtnName_14->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->ActionBtnName_11->setAttribute(Qt::WA_TransparentForMouseEvents);

    ui->labelFirstName_3->setText(user.getFirstName());
    currentUser = new User(user);
}

void admin_homepage::on_toolButton_22_clicked()
{
    creer_utilisateur *CreerUtilisateur = new creer_utilisateur();
    CreerUtilisateur->show();
}


void admin_homepage::on_toolButton_30_clicked()
{
    creer_compte *CreerCompte = new creer_compte();
    CreerCompte->show();
}


void admin_homepage::on_toolButton_26_clicked()
{
    creer_profil *CreerProfil = new creer_profil();
    CreerProfil->show();
}



void admin_homepage::on_toolButton_33_clicked()
{
    quel_client *InfoClient = new quel_client();
    InfoClient->show();
}


void admin_homepage::on_toolButton_34_clicked()
{
    quel_stagiaire *HistoStagiaire = new quel_stagiaire();
    HistoStagiaire->show();
}


void admin_homepage::on_toolButton_36_clicked()
{
    quel_employe *HistoEmploye = new quel_employe();
    HistoEmploye->show();
}


void admin_homepage::on_toolButton_31_clicked()
{
    close();
}


void admin_homepage::on_reduced_3_clicked()
{
    showMinimized();
}

