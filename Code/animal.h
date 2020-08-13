#ifndef ANIMAL_H
#define ANIMAL_H
#include <QRandomGenerator>
class GenericBoard;

class Animal
{
public:
    //Contructors destructors
    Animal();
    virtual ~Animal() = default;
    Animal(short size, GenericBoard* Board);
    static void setStaticMembers(short size, GenericBoard* boardId);

    //Coordination
    virtual void move();
    virtual int getX();
    virtual int getY();
    virtual bool setX(int X);
    virtual bool setY(int Y);
    static QRandomGenerator randomnum;
    static const short moves[9][2];
    static short size;
    static int rool();
    virtual bool isType(std::string string) = 0;

    //Game logic
    virtual void relation() = 0;

protected:
    static GenericBoard* myBoard;
    bool isNewlyBorn = true;
private:
    //Assistants to movement
    int x;
    int y;
    bool alive = true;
    //Type

};
/* ------------- BUNNY CLASS ---------------- */
class Bunny : public Animal{
public:
    Bunny() = default;
    Bunny(int x, int y);
    virtual ~Bunny() = default;
    virtual void reproduce();
    virtual void relation() override;
    virtual bool isType(std::string string) override;
protected:
};

/* ------------- Wolf_f CLASS ---------------- */

class Wolf_f : public Animal{
public:
    Wolf_f() = default;
    Wolf_f(int x, int y);
    virtual ~Wolf_f() = default;
    virtual bool eat();
    virtual void move() override;
    virtual bool mate();
    virtual bool haveMated();
    virtual void relation() override;
    virtual float getBodyFat();
    virtual bool isNew() {return this->isNewlyBorn;}
    virtual bool isType(std::string string) override;
protected:
    float body_fat = 1.0;
    bool mated = false;
    bool haveEatten = false;
    bool isNewlyBorn = true;
private:
};

class Wolf_m : public Wolf_f{
public:
    Wolf_m() = default;
    Wolf_m(int x, int y);
    virtual ~Wolf_m() = default;
    virtual void move() override;
    virtual bool mate() override;
    virtual void relation() override;
    virtual bool isType(std::string string) override;
private:

};



#endif // ANIMAL_H
