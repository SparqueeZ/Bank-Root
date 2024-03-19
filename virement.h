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

private:
    Ui::virement *ui;
};

#endif // VIREMENT_H
