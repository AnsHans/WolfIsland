#ifndef ANIMAL_H
#define ANIMAL_H
#include <QRandomGenerator>
class GenericBoard;

class Animal
{
public:
    Animal();
    Animal(short size, GenericBoard* Board);
    virtual ~Animal() = default;
    virtual void move();
    virtual int getX();
    virtual int getY();
    virtual bool setX(int X);
    virtual bool setY(int Y);
    virtual void relation() = 0;

    static void setStaticMembers(short size, GenericBoard* boardId);
    static QRandomGenerator randomnum;
    static const short moves[9][2];
    static short size;
    static int rool();
protected:
    static GenericBoard* myBoard;
    bool isNew = true;
private:
    //Assistants to movement
    int x;
    int y;
    bool alive = true;
};

class Bunny : public Animal{
public:
    Bunny() = default;
    Bunny(int x, int y);
    virtual ~Bunny() = default;
    virtual void reproduce();
    virtual void relation() override;
};

class Wolf_f : public Animal{
public:
    Wolf_f() = default;
    Wolf_f(int x, int y);
    virtual ~Wolf_f() = default;
    virtual bool eat();
    virtual void move() override;
    virtual bool mate();
    virtual void relation() override;
protected:
    float body_fat = 1;
    bool mated = false;
    bool haveEatten = false;

};

class Wolf_m : public Wolf_f{
public:
    Wolf_m() = default;
    virtual ~Wolf_m() = default;
    void move() override;
    bool mate() override;
    virtual void relation() override;
private:
};


#endif // ANIMAL_H
