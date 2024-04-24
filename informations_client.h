#ifndef INFORMATIONS_CLIENT_H
#define INFORMATIONS_CLIENT_H
#include "home.h"
#include "user.h"
#include <QWidget>

namespace Ui {
class informations_client;
}

class informations_client : public QWidget
{
    Q_OBJECT

public slots:
    //void setUserInformation(const User& user);

public:
    explicit informations_client(QWidget *parent = nullptr);
    ~informations_client();
    void setUserInformations(User &user, User &userToCheck);
    void refreshUserInfo();

private slots:
    //void on_reduced_5_clicked();

    //void on_toolButton_19_clicked();

private slots:
    void on_deco_infoc_clicked();

    void on_reduced_infoc_clicked();

    void on_fullscreen_infoc_clicked();

    void on_close_infoc_clicked();
    void on_historyBtn_clicked();

    void on_creditBtn_clicked();

    void on_debitBtn_clicked();

private:
    Ui::informations_client *ui;
    QString m_userId;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint cur_pos;
    QPoint new_pos;
    User *currentUser;
    User currentUserChecked;
    Home *parentHome;
};

#endif // INFORMATIONS_CLIENT_H
