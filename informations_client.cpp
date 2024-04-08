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

void informations_client::on_reduced_5_clicked()
{
    showMinimized();
}


void informations_client::on_toolButton_19_clicked()
{
    close();
}

