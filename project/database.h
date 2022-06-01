#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>  //对数据库进行增删改查的头文件
#include "user.h"
#include "words.h"
#include <QSqlRecord>
class Database
{
public:
    Database();
    void ConnectSql();  //连接数据库
    bool Signup(user myuser);  //登陆判断，可以登录返回true,失败返回FALSE
    bool Register(user myuser);  //注册新用户   注册成功返回true,失败返回false
    QString Chaxun(words words1);  //查询单词
private:
    QSqlDatabase db;  //数据库对象
};

#endif // DATABASE_H
