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
