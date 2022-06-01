#ifndef FILLOUT_H
#define FILLOUT_H

#include <QWidget>

namespace Ui {
class fillout;
}

class fillout : public QWidget
{
    Q_OBJECT

public:
    explicit fillout(QWidget *parent = nullptr);
    ~fillout();

private:
    Ui::fillout *ui;
};

#endif // FILLOUT_H
