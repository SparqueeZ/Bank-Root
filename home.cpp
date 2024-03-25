#include "home.h"
#include "qevent.h"
#include "ui_home.h"
#include <QMessageBox>
#include <QGuiApplication>
#include "login.h"
#include "virement.h"

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
    // Fenetre moovable
    cur_pos = event->globalPosition().toPoint();
}

void Home::mouseMoveEvent(QMouseEvent *event) {
    // Fenetre moovable
    new_pos = QPoint(event-> globalPosition().toPoint() - cur_pos );
    move(x()+new_pos.x(), y() + new_pos.y());
    cur_pos = event->globalPosition().toPoint();
}

void Home::on_fullscreen_clicked()
{
    QRect mainScreenSize = QGuiApplication::primaryScreen()->availableGeometry();
    setGeometry(mainScreenSize);
}

void Home::on_logoff_clicked()
{
    Login *login = new Login();
    login->show();

    this->hide();
}

void Home::on_virement_clicked()
{
    virement *Virement = new virement();
    Virement->show();
}
