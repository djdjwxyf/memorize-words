#include "unfamiliar.h"
#include "ui_unfamiliar.h"
#include <QDebug>
#include <QFile>
#include <QSqlQuery>  //对数据库进行增删改查的头文件
#include <QVector>
#include <QTime>      //用于生成随机数，来控制id，返回单词
#include <QMessageBox>

unfamiliar::unfamiliar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::unfamiliar)
{
    ui->setupUi(this);
    this->setWindowTitle("百词斩");
    this->setFixedSize(600,600);

    m_TextEdit3 = new QTextEdit(this);
    m_TextEdit3->setGeometry(80,80,220,300);
    m_TextEdit3->setAlignment(Qt::AlignCenter);

    m_TextEdit4 = new QTextEdit(this);
    m_TextEdit4->setGeometry(350,80,220,300);
    m_TextEdit4->setAlignment(Qt::AlignCenter);
}

unfamiliar::~unfamiliar()
{
    delete ui;
}

void unfamiliar::on_return_function2_clicked()
{
    emit return_function2();    //发送返回信号
    this->close();
}

void unfamiliar::paintEvent(QPaintEvent *event)
{
    // 给子窗口画背景图
    QPainter p(this);    //创建画家对象
    QPixmap pixmap(":/image/image/blackgroud2.PNG");  //获取背景图路径
    p.drawPixmap(0,0,this->width(),this->height(),pixmap);  //绘制背景图
}

void unfamiliar::on_next_clicked()  //切换下一个生词
{
    //获取用户ID
    QString userid;
    QFile file1("user_id.txt");  //参数就是读取用户id文件的路径
    file1.open(QIODevice::ReadOnly);//只读模式
    userid = file1.readLine(); //按行读，追加
    file1.close();

    QString sql=QString("select id from Unword where UserID='%2'").arg(userid);
    QSqlQuery query;
    QVector<int> Arr_id;     //储存返回的id，因为一个用户可能有点多个不会的单词

    if(query.exec(sql)) //执行sql语句是否成功
    {
        if(query.size()==0){    //如果返回结果为空，说明Unword表中，没有当前用户不会的单词id
            QMessageBox::information(this,
                   tr("百词斩"),
                   tr("可能是你太强了，目前生词本中还没有生词哦！"),
                   QMessageBox::Ok);
            return;
        }
        for(int i=0; i<query.size();i++){   //这个for循环的作用是将用户不会的单词id存放到id数组中
            //根据下标将返回结果进行分割
            query.next();
            Arr_id.push_back(query.value(0).toInt());
            qDebug()<<query.value(0).toInt();
            qDebug()<<(Arr_id[i]);
        }

        //从Arr_id.size()中随机生成一个id,用于随机复习生词本中的单词
        QTime randtime;
        randtime = QTime::currentTime();
        qsrand(randtime.msec()+randtime.second()*1000); //以当前时间ms为随机种子
        int n = (qrand() % Arr_id.size());

        QString sql1=QString("select englishWord,chineseWord from words where id='%1'").arg(Arr_id[n]);   //获取数据库中单词的英文和中文
        QString sql2=QString("select englishInstance1,chineseInstance1 from words where id='%1'").arg(Arr_id[n]);  //获取数据库中单词的英文例句和中文解释
        QString sql3="\n \n";
        QSqlQuery query;
        if(query.exec(sql1)) //执行sql语句是否成功
        {
            //将当前单词的id存入unknow_id.txt文件中，用于生词本功能
            QFile file("unknow_id.txt");
            file.open(QIODevice::ReadWrite | QIODevice::Text);
            //向文件中写入两行字符串
            file.write(QString("%2").arg(n).toUtf8());   //因为一次只向数据库插一条数据(用户id,单词id)，所以不能用追加读写的方式
            //关闭文件
            file.close();

            while(query.next())//指向下一条
            {
                //根据下标将返回结果进行分割
                QString TEXT1=query.value(0).toString();
                QString TEXT2=query.value(1).toString();
                m_TextEdit3->setText("单词： "+TEXT1+sql3+"解释： "+TEXT2);
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
                m_TextEdit4->setText("例句： "+TEXT3+sql3+"解释： "+TEXT4);
            }

        }else
        {
            qDebug()<<"获取单词失败";
        }
    }


}

void unfamiliar::on_move_unknow_clicked()  //移除生词本中的单词  通过检测当前m_TextEdit3中显示的是哪个单词，然后在words数据表中查找这个单词的ID，最后在Unword数据表中将用户ID对应的单词id删除
{
    QString texts = m_TextEdit3->toPlainText();  //检测当前m_TextEdit3中显示的是哪个单词
    qDebug()<<texts;
    QString englishWord;
    for(int i = 4; i < texts.size(); i++){
        if('a'<=texts[i-4]<='z'){
            englishWord+=texts[i];
        }
        if(englishWord.size()>0&&'\n'==texts[i+1]){
            break;
        }
    }
    QString sql=QString("select id from words where englishWord='%2'").arg(englishWord);   //获取words数据表中这个单词的ID
    QSqlQuery query;
    int id;
    if(query.exec(sql)) //执行sql语句是否成功
    {
        query.next();
        id=query.value(0).toInt();
        qDebug()<<id;
    }else{
        qDebug()<<"查询当前单词id失败";
    }

    QString userid;        //获取用户id
    QFile file1("user_id.txt");
    file1.open(QIODevice::ReadOnly);
    userid = file1.readLine();
    file1.close();

    QString sql2=QString("DELETE FROM Unword WHERE id='%1' AND UserID='%2';").arg(id).arg(userid);   //获取words数据表中这个单词的ID
    QSqlQuery query2;
    if(query2.exec(sql2)) //执行sql语句是否成功
    {
        QMessageBox::information(this,
               tr("百词斩"),
               tr("恭喜你，又学会了一个单词"),
               QMessageBox::Ok);
    }else{
        qDebug()<<"将该生词移除单词本失败";
    }
}
