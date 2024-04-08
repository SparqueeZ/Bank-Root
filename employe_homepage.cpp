#include "employe_homepage.h"
#include "ui_employe_homepage.h"

employe_homepage::employe_homepage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::employe_homepage)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

employe_homepage::~employe_homepage()
{
    delete ui;
}

void employe_homepage::on_reduced_5_clicked()
{
    showMinimized();
}


void employe_homepage::on_toolButton_44_clicked()
{
    close();
}

