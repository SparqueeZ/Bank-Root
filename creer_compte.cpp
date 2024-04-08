#include "creer_compte.h"
#include "ui_creer_compte.h"

creer_compte::creer_compte(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::creer_compte)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);


}

creer_compte::~creer_compte()
{
    delete ui;
}
