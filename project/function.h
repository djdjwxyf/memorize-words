#ifndef FUNCTION_H
#define FUNCTION_H

#include "memorize.h"
#include "unfamiliar.h"
#include <QWidget>
#include <QPainter>

namespace Ui {
class function;
}

class function : public QWidget
{
    Q_OBJECT

public:
    explicit function(QWidget *parent = nullptr);
    ~function();

private slots:
    void on_memorize_words_clicked();    //打开背单词界面

    void on_unfamiliar_word_clicked();

protected:
    //绘图事件函数
    void paintEvent(QPaintEvent *event);

private:
    Ui::function *ui;
};

#endif // FUNCTION_H
