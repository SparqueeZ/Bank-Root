#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include "user.h"

namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public slots:
    void setUserInformation(const User& user);

public:
    explicit Home(QWidget parent = nullptr);
    ~Home();

private slots:
    void on_reduced_clicked();

    void on_fullscreen_clicked();

    void on_toolButton_3_clicked();

<<<<<<< Updated upstream
    void on_toolButton_2_clicked();

=======
>>>>>>> Stashed changes
private:
    Ui::Homeui;
    void mousePressEvent(QMouseEvent event);
    void mouseMoveEvent(QMouseEventevent);
    QPoint cur_pos;
    QPoint new_pos;
};

#endif // HOME_H
