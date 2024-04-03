#ifndef CONSULTER_CLIENT_H
#define CONSULTER_CLIENT_H

#include <QWidget>

namespace Ui {
class consulter_client;
}

class consulter_client : public QWidget
{
    Q_OBJECT

public:
    explicit consulter_client(QWidget *parent = nullptr);
    ~consulter_client();

private:
    Ui::consulter_client *ui;
};

#endif // CONSULTER_CLIENT_H
