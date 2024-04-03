#ifndef CREER_COMPTE_H
#define CREER_COMPTE_H

#include <QWidget>

namespace Ui {
class creer_compte;
}

class creer_compte : public QWidget
{
    Q_OBJECT

public:
    explicit creer_compte(QWidget *parent = nullptr);
    ~creer_compte();

private:
    Ui::creer_compte *ui;
};

#endif // CREER_COMPTE_H
