#ifndef VIREMENT_H
#define VIREMENT_H

#include <QDialog>

namespace Ui {
class virement;
}

class virement : public QDialog
{
    Q_OBJECT

public:
    explicit virement(QWidget *parent = nullptr);
    ~virement();

private slots:
    void on_reduced_clicked();

    void on_return2_clicked();

    void on_send_clicked();

private:
    Ui::virement *ui;
};

#endif // VIREMENT_H
