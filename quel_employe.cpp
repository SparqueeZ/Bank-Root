#include "quel_employe.h"
#include "ui_quel_employe.h"

quel_employe::quel_employe(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::quel_employe)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);
}

quel_employe::~quel_employe()
{
    delete ui;
}
