#include "consulter_client.h"
#include "ui_consulter_client.h"

consulter_client::consulter_client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::consulter_client)
{
    ui->setupUi(this);
}

consulter_client::~consulter_client()
{
    delete ui;
}
