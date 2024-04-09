#include "informations_client.h"
#include "ui_informations_client.h"

informations_client::informations_client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::informations_client)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

informations_client::~informations_client()
{
    delete ui;
}

void informations_client::on_reduced_infoc_clicked()
{
    showMinimized();
}


void informations_client::on_close_infoc_clicked()
{
    close();
}

void informations_client::on_fullscreen_infoc_clicked()
{

}

void informations_client::on_deco_infoc_clicked()
{

}
