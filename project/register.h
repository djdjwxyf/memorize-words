#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include"database.h"
#include"user.h"
#include <QPainter>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

signals:
    void return_signup();    //返回信号
private slots:
    void on_btnregister_clicked();   //注册功能按钮

    void on_ptnreturn_clicked();      //返回登陆按钮
protected:
    //绘图事件函数
    void paintEvent(QPaintEvent *event);

private:
    Ui::Register *ui;
    Database *data;
};

#endif // REGISTER_H
