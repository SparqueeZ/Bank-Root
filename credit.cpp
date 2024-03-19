#include "credit.h"
#include "ui_credit.h"

credit::credit(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::credit)
{
    ui->setupUi(this);
}

credit::~credit()
{
    delete ui;
}
