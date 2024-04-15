#ifndef QUEL_CLIENT_H
#define QUEL_CLIENT_H

#include <QWidget>

namespace Ui {
class quel_client;
}

class quel_client : public QWidget
{
    Q_OBJECT

public:
    explicit quel_client(QWidget *parent = nullptr);
    ~quel_client();

private slots:
    void on_return_kiclient_clicked();

    void on_send_kiclient_clicked();

    void on_reduced_kiclient_clicked();

    void on_fullscreen_kiclient_clicked();

    void on_close_kiclient_clicked();



private:
    Ui::quel_client *ui;
};

#endif // QUEL_CLIENT_H
