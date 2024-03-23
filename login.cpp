#include "login.h"
#include "home.h"
#include "login.h"
#include "ui_login.h"
#include "user.h"
#include "user.cpp"
#include "main.cpp"
#include "home.cpp"
#include <QMessageBox>
#include <QGuiApplication>

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);

    // Background transparent
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
}

Login::~Login()
{
    delete ui;
}

void Login::mousePressEvent(QMouseEvent *event) {
    // Fenetre moovable
    cur_pos = event->globalPosition().toPoint();
}

void Login::mouseMoveEvent(QMouseEvent *event) {
    // Fenetre moovable
    new_pos = QPoint(event-> globalPosition().toPoint() - cur_pos );
    move(x()+new_pos.x(), y() + new_pos.y());
    cur_pos = event->globalPosition().toPoint();
}

void Login::on_toolButton_3_clicked()
{
    close();
}


void Login::on_pushButton_clicked()
{
    QString username = ui->lineEdit_3->text();
    QString password = ui->lineEdit_2->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
    } else {
        User user;

        if (user.logIn(username, password)) {
            Home *home = new Home();
            home->show();

            this->hide();
        } else {
            // Afficher un message d'erreur si l'authentification a échoué

        }
    }
}

void Login::on_reduced_clicked()
{
    showMinimized();
}

void Login::on_fullscreen_clicked()
{
    QRect mainScreenSize = QGuiApplication::primaryScreen()->availableGeometry();
    setGeometry(mainScreenSize);
}

