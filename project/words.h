#ifndef WORDS_H
#define WORDS_H
#include <QString>

class words
{
public:
    words(int,QString,QString);
    words(QString);
    int GetID();           //获取单词ID
    QString GetEnglish();  //获取单词，返回单词
    QString GetChinese();  //获取中文意思，返回中文意思
private:
    QString English;
    QString Chinese;
    int id;
};

#endif // WORDS_H
