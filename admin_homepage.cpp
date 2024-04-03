#include "admin_homepage.h"
#include "ui_admin_homepage.h"

admin_homepage::admin_homepage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::admin_homepage)
{
    ui->setupUi(this);
}

admin_homepage::~admin_homepage()
{
    delete ui;
}
