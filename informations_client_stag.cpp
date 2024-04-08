#include "informations_client_stag.h"
#include "ui_informations_client_stag.h"

informations_client_stag::informations_client_stag(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::informations_client_stag)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

informations_client_stag::~informations_client_stag()
{
    delete ui;
}
