#include "stagiaire_homepage.h"
#include "ui_stagiaire_homepage.h"

stagiaire_homepage::stagiaire_homepage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::stagiaire_homepage)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

stagiaire_homepage::~stagiaire_homepage()
{
    delete ui;
}
