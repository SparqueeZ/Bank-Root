#ifndef STAGIAIRE_HOMEPAGE_H
#define STAGIAIRE_HOMEPAGE_H

#include <QWidget>

namespace Ui {
class stagiaire_homepage;
}

class stagiaire_homepage : public QWidget
{
    Q_OBJECT

public:
    explicit stagiaire_homepage(QWidget *parent = nullptr);
    ~stagiaire_homepage();

private slots:
    void on_reduced_3_clicked();

    void on_toolButton_31_clicked();

private:
    Ui::stagiaire_homepage *ui;
};

#endif // STAGIAIRE_HOMEPAGE_H
