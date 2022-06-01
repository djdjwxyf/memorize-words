#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QMessageBox>
#include "database.h"
#include "user.h"
#include "register.h"
#include "function.h"
#include <QPainter>
#include <QString>


namespace Ui {
class SignUp;
}

class SignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

private slots:
    void on_pushButton_2_clicked();   //登录按钮

    void on_btnregister_clicked();   //注册按钮
protected:
    //绘图事件函数
    void paintEvent(QPaintEvent *event);

private:
    Ui::SignUp *ui;
    Database *data;
};

#endif // SIGNUP_H
