#ifndef QUEL_EMPLOYE_H
#define QUEL_EMPLOYE_H

#include <QWidget>

namespace Ui {
class quel_employe;
}

class quel_employe : public QWidget
{
    Q_OBJECT

public:
    explicit quel_employe(QWidget *parent = nullptr);
    ~quel_employe();

private:
    Ui::quel_employe *ui;
};

#endif // QUEL_EMPLOYE_H
