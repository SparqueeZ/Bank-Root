#include "quel_stagiaire.h"
#include "ui_quel_stagiaire.h"

quel_stagiaire::quel_stagiaire(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::quel_stagiaire)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

quel_stagiaire::~quel_stagiaire()
{
    delete ui;
}

void quel_stagiaire::on_reduced_clicked()
{
    showMinimized();
}


void quel_stagiaire::on_toolButton_3_clicked()
{
    close();
}

