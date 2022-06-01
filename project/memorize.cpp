#include "memorize.h"
#include "ui_memorize.h"
#include <QTime>      //用于生成随机数，来控制id，返回单词
#include <QString>
#include <QDebug>
#include <QSqlQuery>  //对数据库进行增删改查的头文件
#include <QFile>
#include <QMessageBox>

memorize::memorize(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::memorize)
{
    ui->setupUi(this);
    this->setWindowTitle("百词斩");
    this->setFixedSize(600,600);

    m_TextEdit1 = new QTextEdit(this);
    m_TextEdit1->setGeometry(80,80,220,300);
    m_TextEdit1->setAlignment(Qt::AlignCenter);

    m_TextEdit2 = new QTextEdit(this);
    m_TextEdit2->setGeometry(350,80,220,300);
    m_TextEdit2->setAlignment(Qt::AlignCenter);

}

memorize::~memorize()
{
    delete ui;
}

void memorize::on_return_function_clicked()
{
    emit return_function();    //发送返回信号
    this->close();
}

void memorize::on_begin_clicked()
{
    QTime randtime;
    randtime = QTime::currentTime();
    qsrand(randtime.msec()+randtime.second()*1000); //以当前时间ms为随机种子

    QString sql="select count(id) from words";
    QSqlQuery query;
    int sum; //用于记录数据表中共有多少个单词
    if(query.exec(sql)) //执行sql语句是否成功
    {
        query.next();
        sum =query.value(0).toInt();
    }else{
        qDebug()<<"查询数据库中单词总数失败";
    }

    int n = (qrand() % sum) + 1;    //产生10以内的随机整数,+1是为了防止id为0。  可以通过控制%后面的数来调整随机数的范围
    QString sql1=QString("select englishWord,chineseWord from words where id='%2'").arg(n);   //获取数据库中单词的英文和中文
    QString sql2=QString("select englishInstance1,chineseInstance1 from words where id='%1'").arg(n);  //获取数据库中单词的英文例句和中文解释
    QString sql3="\n \n";
    if(query.exec(sql1)) //执行sql语句是否成功
    {
        //将当前单词的id存入id.txt文件中，用于生词本功能
        QFile file("word_id.txt");
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.write(QString("%1").arg(n).toUtf8());
        //关闭文件
        file.close();

        while(query.next())//指向下一条
        {
            //根据下标将返回结果进行分割
            QString TEXT1=query.value(0).toString();
            QString TEXT2=query.value(1).toString();
            m_TextEdit1->setText("单词： "+TEXT1+sql3+"解释： "+TEXT2);
        }

    }else
    {
        qDebug()<<"获取单词失败";
    }
    if(query.exec(sql2)) //执行sql语句是否成功
    {
        //qDebug()<<"find record num:"<<query.size();//查询结果记录条数

        while(query.next())//指向下一条
        {
            //根据下标找到对应字段值
            QString TEXT3=query.value(0).toString();
            QString TEXT4=query.value(1).toString();
            m_TextEdit2->setText("例句： "+TEXT3+sql3+"解释： "+TEXT4);
        }

    }else
    {
        qDebug()<<"获取单词失败";
    }

}

void memorize::paintEvent(QPaintEvent *event)   //绘制图片背景
{
   // 给子窗口画背景图
   QPainter p(this);    //创建画家对象
   QPixmap pixmap(":/image/image/blackgroud2.PNG");  //获取背景图路径
   p.drawPixmap(0,0,this->width(),this->height(),pixmap);  //绘制背景图
}


void memorize::on_join_unknow_clicked()  //加入生词本
{
    QString userid,wordid;
    QFile file1("user_id.txt");  //参数就是读取用户id文件的路径
    file1.open(QIODevice::ReadOnly);//只读模式
    userid = file1.readLine(); //按行读，追加
    file1.close();

    QFile file2("word_id.txt");    //读取单词id的文件路径
    file2.open(QIODevice::ReadOnly);//只读模式
    wordid = file2.readLine(); //按行读，追加
    qDebug()<<userid<<wordid;
    file1.close();

    QString sql=QString("insert into Unword values('%1','%2')").arg(userid).arg(wordid);
    qDebug()<<sql;
    QSqlQuery query;
    if(query.exec(sql))
    {
        QMessageBox::information(this,
               tr("百词斩"),
               tr("成功添加到生词本"),
               QMessageBox::Ok);

    }
    else{
        QMessageBox::warning(this,
               tr("百词斩"),
               tr("这个词已经存在于单词本中了哦！"),
               QMessageBox::Ok);
    }

}

