#include "database.h"

Database::Database()
{
    ConnectSql();
}

void Database::ConnectSql()
{
    //打印QT支持的数据库驱动
    qDebug()<<QSqlDatabase::drivers();

    //获取数据库对象
    db=QSqlDatabase::addDatabase("QMYSQL");
    //配置数据库
    db.setHostName("127.0.0.1");   //我们要链接的数据库的ip地址
    db.setUserName("root");        //MYSQL数据库的登录名
    db.setPassword("123456");      //MYSQL数据库的密码
    db.setDatabaseName("Words");        //数据库名称
    //打开数据库
    if(db.open())
    {
        qDebug()<<"连接数据库成功";
        return;
    }
    else{
        qDebug()<<"连接数据库失败";
        return;
    }
    QSqlQuery query;  //如果当前项目只有一个QSqlDatabase对象，则默认绑定，如果有两个及以上，则query（）括号里要填具体的名字

    //query.exec("create table student(id int ...)");   创建表
    //query.exec("insert into student(id,name,age,score) values(1,'Tony,18,59')");  插入数据
}

bool Database::Signup(user myuser)   // 登录功能
{
    QString sql=QString("select UserPassword from Usertable where UserID='%1'").arg(myuser.GetUserID());
    QSqlQuery query;
    if(query.exec(sql))   //如果这个密码存在,query.exec(sql)会返回true
    {
        if(query.first())
        {
            QString pass=query.value(0).toString();
            pass=pass.remove(QRegExp("\\s"));    //去除空格操作ui控件中的空格
            if(pass==myuser.GetUserPassword()){    //如果返回的密码和当前输入的密码是一样的，说明成功了
                qDebug()<<"用户登陆成功";
                return true;
            }
            else{
                qDebug()<<"账号不存在";
                return false;
            }
        }else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool Database::Register(user myuser)  //向数据库写入注册者的信息
{
    QString sql=QString("insert into Usertable values('%1','%2')").arg(myuser.GetUserID()).arg(myuser.GetUserPassword());
    qDebug()<<sql;
    QSqlQuery query;
    if(query.exec(sql))
    {
        return true;
    }
    else{
        qDebug()<<"当前用户名已被注册";
        return false;   //因为可能会出现userID已存在的情况
    }

}

QString Database::Chaxun(words words1)
{
    QString sql=QString("select translate from words where word='%1'").arg(words1.GetEnglish());
    QSqlQuery query;
    QString translate1;
    if(query.exec(sql))  //如果这个单词的翻译存在
    {
        while(query.next())
        {
            qDebug()<<words1.GetEnglish()<<"的汉语意思为：";
            translate1 = query.value(0).toString();
            return translate1;
        }
    }
    else{
        return translate1;
    }
}


