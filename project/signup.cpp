#include "signup.h"
#include "ui_signup.h"
#include <QFile>
SignUp::SignUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
    data = new Database;
    this->setWindowTitle("百词斩");
    this->setFixedSize(600,600);
}

SignUp::~SignUp()
{
    delete ui;
    delete data;
}

void SignUp::on_pushButton_2_clicked()
{
    user user1(ui->lineUser->text(),ui->linePassword->text());
    QString user_id = user1.GetUserID();
   if(data->Signup(user1))
   {
       //将用户id写到配置文件中，以便于生词本功能使用
       QFile file("user_id.txt");
       file.open(QIODevice::ReadWrite | QIODevice::Text);  //这两行的目的是判断文件是否存在，不存在则创建一个  不已追加的形式进行写入
       file.write(user_id.toUtf8());
       file.close();

       //显示功能界面
       function *fun = new function;
       fun->show();
       this->close();
   }
   else{
       QMessageBox::warning(this,"错误","登陆失败！用户名或密码不正确或用户名不存在！");
   }
}

void SignUp::on_btnregister_clicked()   //注册按钮
{
    Register *reg = new Register;    //创建注册对象，然后等待信号连接
    connect(reg,&Register::return_signup,[=](){
        this->show();   //显示登陆界面
    });
    reg->show();
    this->close();
}

void SignUp::paintEvent(QPaintEvent *event)
{
    // 给子窗口画背景图
    QPainter p(this);    //创建画家对象
    QPixmap pixmap(":/image/image/blackgroud1.PNG");  //获取背景图路径
    p.drawPixmap(0,0,this->width(),this->height(),pixmap);  //绘制背景图
}


