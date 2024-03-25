#include "virement.h"
#include "ui_virement.h"

virement::virement(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::virement)
{
    ui->setupUi(this);
}

virement::~virement()
{
    delete ui;
}
