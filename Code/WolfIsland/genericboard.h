#ifndef GENERICBOARD_H
#define GENERICBOARD_H
#include <QObject>
#include <QFrame>
#include "genericcell.h"
#include "QBasicTimer"
#include <QPainter>

//Ogólna zasada działania turowania GenericBoard to
//Porusz wszystkim do nowej tablicy
//Sprawdz relacje
//Elo

//Ogólny plan
/* I Etap
 * Zrobić relacje +
 * II etap
 * Zrobić jakiś początek +
 * III etap
 * Zrobić planszę
 * Planasza powinna mieć jakieś liczniki
 *
 * To chyba będzie ciężkie
 * IV etap
 * Dodać żywopłot i rysowanie go i jeszcze do tego rysowanie królików
 *
*/

class GenericBoard : public QFrame
{
   Q_OBJECT
public:
    friend class Animal;
    friend class Wolf_m;
    friend class Wolf_f;
    GenericBoard(QWidget *parent = nullptr, short size = 20);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    //Funkcje związane z renderowaniem
protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

public:
    //Game Logic
    void relations();
    void calibrate();
    void add(Animal* AnimalToPut, short x, short y);
    void moveAll();
    bool isThereBunny(short x, short y);
    bool isThereWolf_f(short x, short y);
    void oneRound();

public slots:
   void clear();
   void start();

private:
   int squareWidth() { return contentsRect().width() / size; }
   int squareHeight() { return contentsRect().height() / size; }
   void drawSquare(QPainter &painter, int x, int y);

   bool isStarted = false;
   bool isPaused = false;
   const short size;
   GenericCell** board;
   QBasicTimer timer;
};

#endif // GENERICBOARD_H
