#include "debit.h"
#include "ui_debit.h"

debit::debit(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::debit)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowType::FramelessWindowHint);

}

debit::~debit()
{
    delete ui;
}
