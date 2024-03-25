#include <QApplication>
#include <QMessageBox>
#include <QMainWindow>
#include <QProcess>
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

void virement::on_reduced_clicked()
{
    showMinimized();
}

void virement::on_return2_clicked()
{
    this->hide();
}

void virement::on_send_clicked()
{
    QString combien = ui->combien->text();
    QString aqui = ui->aqui->text();


    QMessageBox msgBox;
    msgBox.setText("Truc machin");
    msgBox.addButton(combien, QMessageBox::AcceptRole);
    msgBox.addButton(aqui, QMessageBox::AcceptRole);
    msgBox.setDefaultButton(QMessageBox::NoButton);
    int choice = msgBox.exec();

}
