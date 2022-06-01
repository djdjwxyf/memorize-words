#include "register.h"
#include "ui_register.h"
#include<QMessageBox>
Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    data = new Database;
    this->setWindowTitle("百词斩");
    this->setFixedSize(600,600);
}

Register::~Register()
{
    delete ui;
    delete data;
}

void Register::on_btnregister_clicked()  //注册按钮
{
    if(ui->lineUser->text()==""||ui->linePassword->text()==""||ui->linePassword2->text()=="")
    {
        QMessageBox::warning(this,"错误！","所填内容不能为空！");
        return;
    }

    if(ui->linePassword->text()==ui->linePassword2->text())
    {
        user user1(ui->lineUser->text(),ui->linePassword->text());
        if(data->Register(user1))  //Register返回的是用户是否成功注册
        {
            QMessageBox::information(this,"提示","注册成功");
        }
        else{
            QMessageBox::warning(this,"注册失败","该用户名已被注册");
        }
    }
    else{
        QMessageBox::warning(this,"错误","两次密码输入有误");
    }

}

void Register::on_ptnreturn_clicked()    //返回登陆按钮
{
    emit return_signup();    //发送返回
    this->close();
}

void Register::paintEvent(QPaintEvent *event)
{
    // 给子窗口画背景图
    QPainter p(this);    //创建画家对象
    QPixmap pixmap(":/image/image/blackgroud1.PNG");  //获取背景图路径
    p.drawPixmap(0,0,this->width(),this->height(),pixmap);  //绘制背景图
}
