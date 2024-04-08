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

void quel_client::on_toolButton_4_clicked()
{
    close();
}


void quel_client::on_reduced_2_clicked()
{
    showMinimized();
}

