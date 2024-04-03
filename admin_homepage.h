#ifndef ADMIN_HOMEPAGE_H
#define ADMIN_HOMEPAGE_H

#include <QWidget>

namespace Ui {
class admin_homepage;
}

class admin_homepage : public QWidget
{
    Q_OBJECT

public:
    explicit admin_homepage(QWidget *parent = nullptr);
    ~admin_homepage();

private:
    Ui::admin_homepage *ui;
};

#endif // ADMIN_HOMEPAGE_H
