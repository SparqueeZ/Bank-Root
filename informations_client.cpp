#include "informations_client.h"
#include "ui_informations_client.h"

informations_client::informations_client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::informations_client)
{
    ui->setupUi(this);
}

informations_client::~informations_client()
{
    delete ui;
}
