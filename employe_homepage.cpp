#include "employe_homepage.h"
#include "ui_employe_homepage.h"

employe_homepage::employe_homepage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::employe_homepage)
{
    ui->setupUi(this);
}

employe_homepage::~employe_homepage()
{
    delete ui;
}
