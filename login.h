#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();
    void refresh();

private slots:
    void on_toolButton_3_clicked();

    void on_pushButton_clicked();

    void on_reduced_clicked();

    void on_fullscreen_clicked();



private:
    Ui::Login *ui;
    // Fenetre moovable
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
};
#endif // LOGIN_H
