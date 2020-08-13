#ifndef GENERICBOARD_H
#define GENERICBOARD_H
#include <QObject>
#include <QFrame>
#include <QMouseEvent>
#include "genericcell.h"
#include "QBasicTimer"
#include <QPainter>
#include "animal.h"

class GenericBoard : public QFrame
{
   Q_OBJECT
public:
    friend class Animal;
    friend class Wolf_m;
    friend class Wolf_f;

    //Constructors
    GenericBoard(QWidget *parent = nullptr, short size = 20);
    virtual ~GenericBoard();
    virtual QSize sizeHint() const override;
    virtual QSize minimumSizeHint() const override;

    //Funkcje związane z renderowaniem
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void timerEvent(QTimerEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;

public:
/* -------------------- GAME LOGIC -------------------------- */
    virtual void oneRound();
    virtual void moveAll();
    virtual void calibrate();
    virtual void relations();
    virtual void emitForWidgets();
    virtual void add(Animal* AnimalToPut, short x, short y);
    virtual bool isThereBunny(short x, short y);
    virtual bool isThereWolf_f(short x, short y);
    virtual void killMe(Animal* AnimalToKill, short x, short y);
    virtual void cleanUp();
    virtual void resize(int BoardSize);


public slots:
   virtual void clear();
   virtual void start();
signals:
    void numWolvesChanged(int numWolves);
    void numBunniesChanged(int numBunnies);

private:
   //Rendering
   virtual int squareWidth() { return contentsRect().width() / size; }
   virtual int squareHeight() { return contentsRect().height() / size; }
   virtual void drawSquare(QPainter &painter, int x, int y);

   //Timing
   bool isStarted = false;
   bool isPaused = false;
   short size;
   GenericCell** board;
   QBasicTimer timer;
   QString key = "Q";
};

#endif // GENERICBOARD_H
