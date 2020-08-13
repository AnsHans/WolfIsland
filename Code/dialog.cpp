#include "dialog.h"

Dialog::Dialog(QWidget *parent) : QWidget(parent)
{

    this->enterInt = new QSpinBox(this);
    this->acceptBttn = new QPushButton(this);
    acceptBttn->setText(QString("set size"));
    enterInt->setValue(6);

    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(enterInt,0,0);
    layout->addWidget(acceptBttn,1,0);
    setLayout(layout);
    setWindowTitle("Set");
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowFlag(Qt::Dialog);
    QObject::connect(acceptBttn, SIGNAL(released()), this, SLOT(setSize()));
}

QSize Dialog::sizeHint() const
{
    return QSize(200,70);
}

void Dialog::setSize()
{
    this->sizeToSet = enterInt->value();
    emit sendSize(sizeToSet);
}
