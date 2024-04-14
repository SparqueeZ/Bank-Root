#ifndef INFORMATIONS_CLIENT_H
#define INFORMATIONS_CLIENT_H

#include "user.h"
#include <QWidget>

namespace Ui {
class informations_client;
}

class informations_client : public QWidget
{
    Q_OBJECT

public slots:
    void setUserInformation(const User& user);

public:
    explicit informations_client(QWidget *parent = nullptr);
    ~informations_client();
    void setUserId(const QString &userId);
private slots:
    void on_reduced_5_clicked();

    void on_toolButton_19_clicked();

private slots:
    void on_deco_infoc_clicked();

    void on_reduced_infoc_clicked();

    void on_fullscreen_infoc_clicked();

    void on_close_infoc_clicked();
private:
    Ui::informations_client *ui;
    QString m_userId;
};

#endif // INFORMATIONS_CLIENT_H
