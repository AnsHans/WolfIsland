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

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    // Slider
    QSlider*  timerspeed;
    QLabel* timerLabel;

    QTimer* timer;


};
#endif // WIDGET_H
