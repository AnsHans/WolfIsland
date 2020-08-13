#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    myDialog = new Dialog(this);
    myDialog->show();
    QObject::connect(myDialog, SIGNAL(sendSize(int)), this, SLOT(setSize(int)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::setSize(int SizeToSet)
{
    GenericBoard* simulation = new GenericBoard(this, SizeToSet);
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
    wolvesLabel->setBuddy(numwolves);
    rabbitsLabel->setBuddy(numrabbits);
    QObject::connect(start, &QPushButton::released, simulation, &GenericBoard::start);
    QObject::connect(clear, &QPushButton::released, simulation, &GenericBoard::clear);
    connect(simulation, &GenericBoard::numWolvesChanged,
                numwolves, QOverload<int>::of(&QLCDNumber::display));
    connect(simulation, &GenericBoard::numBunniesChanged,
                numrabbits, QOverload<int>::of(&QLCDNumber::display));


    layout = new QGridLayout;
    layout->addWidget(simulation, 0, 0, 4, 4);
    layout->addWidget(numwolves, 0, 5, Qt::AlignCenter);
    layout->addWidget(numrabbits, 1, 5, Qt::AlignCenter);
    layout->addWidget(wolvesLabel, 0, 6);
    layout->addWidget(rabbitsLabel, 1, 6);
    layout->addWidget(clear, 3, 4);
    layout->addWidget(start, 3, 5);

    setLayout(layout);
    setWindowTitle(tr("WolfIslandWindow"));

    update();
    delete myDialog;
    myDialog = nullptr;
}

