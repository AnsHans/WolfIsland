#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    /* WolfWindow* simulation;
    QPushButton* start;
    QPushButton* stop;
    QPushButton* pause;
    QLCDNumber* numwolves;
    QLCDNumber* numrabbits;
    QSlider*  timerspeed;
    QTimer* timer; */
    GenericBoard* simulation = new GenericBoard(this, 5);
    clear = new QPushButton;
    start = new QPushButton;
    clear->setText(QString("Clear"));
    start->setText(QString("Start"));

    numwolves = new QLCDNumber;
    wolvesLabel = new QLabel;
    wolvesLabel->setText(QString("Numer of Wolves"));
    numrabbits = new QLCDNumber;
    rabbitsLabel = new QLabel;
    rabbitsLabel->setText(QString("Numer of Rabbits"));
    numwolves->display(0);
    numrabbits->display(0);

    timerspeed = new QSlider;
    timerspeed->setValue(3);
    timerspeed->setMinimum(1);
    timerspeed->setMaximum(10);
    timerspeed->setSingleStep(1);
    timerLabel = new QLabel;
    timerLabel->setText(QString("Set Timer Value [s]"));
    timer = new QTimer;
    timerLabel->setBuddy(timerspeed);
    wolvesLabel->setBuddy(numwolves);
    rabbitsLabel->setBuddy(numrabbits);
    QObject::connect(start, &QPushButton::released, simulation, &GenericBoard::start);
    QObject::connect(clear, &QPushButton::released, simulation, &GenericBoard::clear);

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(simulation, 0, 0, 4, 4);
    layout->addWidget(numwolves, 0, 5, Qt::AlignCenter);
    layout->addWidget(numrabbits, 1, 5, Qt::AlignCenter);
    layout->addWidget(timerspeed, 2, 5, Qt::AlignCenter);
    layout->addWidget(wolvesLabel, 0, 6);
    layout->addWidget(rabbitsLabel, 1, 6);
    layout->addWidget(timerLabel, 2, 6);
    layout->addWidget(clear, 3, 4);
    layout->addWidget(start, 3, 5);


    setLayout(layout);
    setWindowTitle(tr("WolfIslandWindow"));

}

MainWindow::~MainWindow()
{
}

