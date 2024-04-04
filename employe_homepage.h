#ifndef EMPLOYE_HOMEPAGE_H
#define EMPLOYE_HOMEPAGE_H

#include <QWidget>

namespace Ui {
class employe_homepage;
}

class employe_homepage : public QWidget
{
    Q_OBJECT

public:
    explicit employe_homepage(QWidget *parent = nullptr);
    ~employe_homepage();

private:
    Ui::employe_homepage *ui;
};

#endif // EMPLOYE_HOMEPAGE_H
