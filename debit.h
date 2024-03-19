#ifndef DEBIT_H
#define DEBIT_H

#include <QDialog>

namespace Ui {
class debit;
}

class debit : public QDialog
{
    Q_OBJECT

public:
    explicit debit(QWidget *parent = nullptr);
    ~debit();

private:
    Ui::debit *ui;
};

#endif // DEBIT_H
