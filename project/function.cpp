#include "function.h"
#include "ui_function.h"

function::function(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::function)
{
    ui->setupUi(this);
    this->setWindowTitle("百词斩");
    this->setFixedSize(600,600);
}

function::~function()
{
    delete ui;
}

void function::on_memorize_words_clicked()   //背单词
{
    memorize *mem = new memorize;    //创建背单词对象
    connect(mem,&memorize::return_function,[=](){   //等待信号连接
        this->show();   //返回功能界面
    });
    mem->show();
    this->close();
}

void function::on_unfamiliar_word_clicked()  //生词本
{
    unfamiliar *unf = new unfamiliar;    //创建生词本对象
    connect(unf,&unfamiliar::return_function2,[=](){  //等待信号连接
        this->show();   //返回功能界面
    });
    unf->show();
    this->close();
}

void function::paintEvent(QPaintEvent *event)
{
    // 给子窗口画背景图
    QPainter p(this);    //创建画家对象
    QPixmap pixmap(":/image/image/blackgroud2.PNG");  //获取背景图路径
    p.drawPixmap(0,0,this->width(),this->height(),pixmap);  //绘制背景图
}
