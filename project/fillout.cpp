#include "fillout.h"
#include "ui_fillout.h"

fillout::fillout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fillout)
{
    ui->setupUi(this);
}

fillout::~fillout()
{
    delete ui;
}
