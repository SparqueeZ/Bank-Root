#include "historique_employe.h"
#include "ui_historique_employe.h"

historique_employe::historique_employe(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::historique_employe)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);

}

historique_employe::~historique_employe()
{
    delete ui;
}

void historique_employe::on_reduced_3_clicked()
{
    showMinimized();
}


void historique_employe::on_toolButton_31_clicked()
{
    close();
}


void historique_employe::on_toolButton_33_clicked()
{

}


void historique_employe::on_toolButton_34_clicked()
{

}


void historique_employe::on_toolButton_35_triggered(QAction *arg1)
{

}


void historique_employe::on_toolButton_35_clicked()
{

}


void historique_employe::on_fullscreen_3_clicked()
{

}


void historique_employe::on_reduced_3_triggered(QAction *arg1)
{

}

