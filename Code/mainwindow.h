#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <genericboard.h>
#include <QLCDNumber>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QGridLayout>
#include <QLabel>
#include <dialog.h>
#include <QInputDialog>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
    void test(int size);
public slots:
    void setSize(int SizeToSet);

private:
    GenericBoard* simulation;
    // BUTTONS
    QPushButton* start;
    QPushButton* clear;
    // LCD
    QLCDNumber* numwolves;
    QLabel* wolvesLabel;
    QLCDNumber* numrabbits;
    QLabel* rabbitsLabel;
    Dialog* myDialog;
    // Slider
    QSlider*  sizeSlider;
    QLabel* sizeLabel;
    QGridLayout* layout;


};
#endif // WIDGET_H
