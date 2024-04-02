#include "home.h"
#include "credit.h"
#include "qevent.h"
#include "ui_home.h"
#include <QMessageBox>
#include <QGuiApplication>
#include <QDebug>
#include "debit.h"

Home::Home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

Home::~Home()
{
    delete ui;
}

void Home::on_reduced_clicked()
{
    showMinimized();
}


void Home::on_toolButton_3_clicked()
{
    close();
}

void Home::mousePressEvent(QMouseEvent *event) {
    if (ui->widget_7->underMouse()) { // Vérifie si le curseur est sur le widget_7
        cur_pos = event->globalPosition().toPoint();
    }
}

void Home::mouseMoveEvent(QMouseEvent *event) {
    if (ui->widget_7->underMouse()) { // Vérifie si le curseur est sur le widget_7
        new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
        move(x() + new_pos.x(), y() + new_pos.y());
        cur_pos = event->globalPosition().toPoint();
    }
}

void Home::on_fullscreen_clicked()
{
    QRect mainScreenSize = QGuiApplication::primaryScreen()->availableGeometry();
    setGeometry(mainScreenSize);
}

void Home::setUserInformation(const User& user)
{
    // Style
    ui->ActionBtnName->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->ActionBtnName_2->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->ActionBtnName_3->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->ActionBtnName_4->setAttribute(Qt::WA_TransparentForMouseEvents);
    // Convertir le solde en une chaîne de caractères avec le symbole €
    QString balanceString = QString::number(user.getBalance()) + " €";
    QString PELString = QString::number(user.getPELBalance()) + " €";
    QString LivretCString = QString::number(user.getLCBalance()) + " €";

    double lcBalance = user.getLCBalance();
    int progressPercentage = static_cast<int>((lcBalance / 10000.0) * 100.0);
    progressPercentage = std::min(std::max(progressPercentage, 0), 100);
    ui->progressBar_4->setValue(progressPercentage);

    // Utiliser les informations de l'utilisateur pour mettre à jour l'interface graphique de la page d'accueil
    ui->labelFirstName->setText(user.getFirstName());
    //ui->labelLastName->setText(user.getLastName());
    ui->labelFirstAccountBalance->setText(balanceString);

    // Ajoutez d'autres mises à jour d'interface utilisateur si nécessaire
    ui->labelPELAccountBalance->setText(PELString);
    ui->labelLCAccountBalance->setText(LivretCString);
}

void Home::on_toolButton_2_clicked()
{
    debit *debit = new class debit();
    debit->show();
    //this->hide();
}

void Home::on_toolButton_14_clicked()
{
    credit *credit = new class credit();
    credit->show();
    //this->hide();
}


