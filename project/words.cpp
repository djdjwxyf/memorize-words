#include "words.h"

words::words(int my_ID,QString my_english,QString my_chinese)
{
    this->id=my_ID;
    this->English=my_english;
    this->Chinese=my_chinese;
}

words::words(QString my_english)   //查询单词的构造函数
{
    this->English=my_english;
}

int words::GetID()
{
    return this->id;
}

QString words::GetEnglish()  //获取单词，返回单词
{
    return this->English;
}
QString words::GetChinese() //获取中文意思，返回中文意思
{
    return this->Chinese;
}
