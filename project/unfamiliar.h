#ifndef UNFAMILIAR_H
#define UNFAMILIAR_H

#include <QWidget>
#include <QTextEdit>
#include <QPainter>

namespace Ui {
class unfamiliar;
}

class unfamiliar : public QWidget
{
    Q_OBJECT

public:
    explicit unfamiliar(QWidget *parent = nullptr);
    ~unfamiliar();

private slots:
    void on_return_function2_clicked();   //返回功能选择界面

    void on_next_clicked();  //切换下一个生词

    void on_move_unknow_clicked();

signals:
    void return_function2();    //返回信号

protected:
    //绘图事件函数
    void paintEvent(QPaintEvent *event);

private:
    Ui::unfamiliar *ui;
    QTextEdit *m_TextEdit3, *m_TextEdit4;    //用于创建QTextEdit对象，好显示文字
};

#endif // UNFAMILIAR_H
