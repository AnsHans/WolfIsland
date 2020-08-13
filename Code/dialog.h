#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>

class Dialog : public QWidget
{
    Q_OBJECT
public:
    Dialog(QWidget *parent = nullptr);
    virtual QSize sizeHint() const override;
signals:
   void sendSize(int size);
private slots:
    void setSize();

private:
    QPushButton* acceptBttn;
    QSpinBox* enterInt;
    int sizeToSet = 7;
};

#endif // DIALOG_H
