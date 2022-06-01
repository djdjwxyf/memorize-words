#ifndef MEMORIZE_H
#define MEMORIZE_H

#include <QWidget>
#include <QTextEdit>
#include <QPainter>
#include "user.h"   //用于获取用户id
namespace Ui {
class memorize;
}

class memorize : public QWidget
{
    Q_OBJECT

public:
    explicit memorize(QWidget *parent = nullptr);
    ~memorize();

private slots:
    void on_return_function_clicked();

    void on_begin_clicked();

    void on_join_unknow_clicked();  //加入生词本

signals:
    void return_function();    //返回信号

protected:
    //绘图事件函数
    void paintEvent(QPaintEvent *event);

private:
    Ui::memorize *ui;

    QTextEdit *m_TextEdit1, *m_TextEdit2;    //用于创建QTextEdit对象，好显示文字  (1显示单词和意思，2显示例句)
};

#endif // MEMORIZE_H
