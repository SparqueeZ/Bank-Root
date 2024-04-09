#include "quel_client.h"
#include "ui_quel_client.h"

quel_client::quel_client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::quel_client)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

quel_client::~quel_client()
{
    delete ui;
}

void quel_client::on_reduced_kiclient_clicked()
{
    showMinimized();
}


void quel_client::on_close_kiclient_clicked()
{
    close();
}


void quel_client::on_fullscreen_kiclient_clicked()
{

}


void quel_client::on_return_kiclient_clicked()
{

}


void quel_client::on_send_kiclient_clicked()
{

}
