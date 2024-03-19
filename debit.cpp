#include "debit.h"
#include "ui_debit.h"

debit::debit(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::debit)
{
    ui->setupUi(this);
}

debit::~debit()
{
    delete ui;
}
