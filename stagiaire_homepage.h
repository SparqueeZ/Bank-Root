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
    void on_consulter_st_clicked();

    void on_reduced_st_clicked();

    void on_fullscreen_st_clicked();

    void on_close_st_clicked();

private:
    Ui::stagiaire_homepage *ui;
};

#endif // STAGIAIRE_HOMEPAGE_H
