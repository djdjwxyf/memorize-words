#include "user.h"

user::user(QString My_user,QString My_password)
{
    this->UserID=My_user;
    this->UserPassword=My_password;
}

QString user::GetUserID()
{
    return this->UserID;
}

QString user::GetUserPassword()
{
    return this->UserPassword;
}

QString user::ChangeUserIno(QString My_user,QString My_password)
{
    this->UserID=My_user;
    this->UserPassword=My_password;
}
