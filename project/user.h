#ifndef USER_H
#define USER_H
#include <QString>

class user
{
public:
    user(QString My_user,QString My_password);  //用户输入账号密码
    QString GetUserID();  //获取用户id
    QString GetUserPassword();  //获取用户密码
    QString ChangeUserIno(QString My_user,QString My_password);  //修改用户信息
private:
    QString UserID;  //用户账户
    QString UserPassword;  //用户密码
};

#endif // USER_H
