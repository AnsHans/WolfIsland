#include "animal.h"
#include "genericboard.h"
const short Animal::moves[9][2] = {{0,0},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1}};
QRandomGenerator Animal::randomnum;
short Animal::size;
GenericBoard* Animal::myBoard;


Animal::Animal()
{
}

Animal::Animal(short size, GenericBoard* Board)
{
    Animal::size = size;
    Animal::myBoard = Board;
}
void Animal::move()
{
    isNew = false;
    int newX = 0;
    int newY = 0;

    do{
    int new_parameters = rool();
    newY = getY() + this->moves[new_parameters][1];
    newX = getX() + this->moves[new_parameters][0];
    }while(!(newX >= 0 && newY >= 0 && newX < Animal::size && newY < Animal::size));

    setX(newX);
    setY(newY);
}

int Animal::getX()
{

    return this->x;
}

int Animal::getY()
{
    return this->y;
}

bool Animal::setX(int X)
{
   this->x = X;
   return true;
}

bool Animal::setY(int Y)
{
    this->y = Y;
    return true;
}

void Animal::setStaticMembers(short size, GenericBoard *boardId)
{
    Animal::size = size;
    Animal::myBoard = boardId;
}

int Animal::rool()
{
    return randomnum.bounded(9);
}

Bunny::Bunny(int x, int y)
{
    setX(x);
    setY(y);
}

void Bunny::reproduce()
{
    if(isNew == true) return;
    int result = randomnum.bounded(9);
    if(result == 1){
        Bunny* animal = new Bunny;
        animal->setX(this->getX());
        animal->setY(this->getY());
        this->myBoard->add(animal,animal->getX(),animal->getY());
    }
    else return;
}

void Bunny::relation()
{
    if(this->isNew == false){
        this->reproduce();
    }
}

Wolf_f::Wolf_f(int x, int y)
{
    this->setX(x);
    this->setY(y);
}

void Wolf_f::relation(){
    bool helpereat;
    if(!(this->haveEatten)){
        helpereat = this->eat();
        if(helpereat == false){

        }
    }
}

bool Wolf_f::eat()
{
    int myX = getX();
    int myY = getY();
    int i = 0;
    for(Animal* oneAnimal : this->myBoard->board[myX][myY].content){
        if(dynamic_cast<Bunny*>(oneAnimal) != nullptr){
            body_fat = body_fat + 1;
            this->myBoard->board[myX][myY].content.erase(this->myBoard->board[myX][myY].content.begin() + i);
            this->haveEatten = true;
            return true;
        }
        i++;
    }
    return false;
}
void Wolf_f::move()
{
    isNew = false;
    haveEatten = false;
    mated = false;
    this->body_fat = this->body_fat - 0.1;
    this->mated = false;
    //Sprawdz wszystkie komórki w okolicy
    for(int i = 0; i < 9; i++){

            int x = this->getX() + moves[i][0];
            int y = this->getY() + moves[i][1];
        if(x >= 0 && y >= 0 && y < Animal::size && x < Animal::size){
            if(this->myBoard->isThereBunny(x,y)){
                this->setX(x);
                this->setY(y);
                return;
            }
        }
    }
    int newX = 0;
    int newY = 0;

    do{
    int new_parameters = rool();
    newY = getY() + this->moves[new_parameters][1];
    newX = getX() + this->moves[new_parameters][0];
    }while(!(newX >= 0 && newY >= 0 && newX < Animal::size && newY < Animal::size));

    setX(newX);
    setY(newY);
}

bool Wolf_f::mate()
{
    if(this->mated == false && this->haveEatten == false){
    this->mated = true;
    return true;
    }
    else{
        return false;
    }
}
void Wolf_m::move()
{
    isNew = false;
    this->body_fat = this->body_fat - 0.1;
    int Wolf_fX = -1;
    int Wolf_fY = -1;
    //Sprawdz wszystkie komórki w okolicy
    for(int i = 0; i < 9; i++){
        int x = this->getX() + moves[i][0];
        int y = this->getY() + moves[i][1];
        if(this->myBoard->isThereBunny(x,y)){
            this->setX(x);
            this->setY(y);
            return;
        }
        if(this->myBoard->isThereWolf_f(x,y)){
            Wolf_fX = x;
            Wolf_fY = y;
        }
    }
    if(Wolf_fX != -1 && Wolf_fY != -1){
        this->setX(Wolf_fX);
        this->setY(Wolf_fY);
    }
    else{
    int rooled = Animal::rool();
    this->setX(this->getX() + Animal::moves[rooled][0]);
    this->setY(this->getY() + Animal::moves[rooled][1]);
    }
}

bool Wolf_m::mate()
{
    int myX = getX();
    int myY = getY();
    for(Animal* oneAnimal : this->myBoard->board[myX][myY].content){
        if(dynamic_cast<Wolf_f*>(oneAnimal) != nullptr){
            Wolf_f* partner = dynamic_cast<Wolf_f*>(oneAnimal);
            if(partner->mate() == true){
            //Wylosuj jakąś płeć i dodaj
            if(randomnum.bounded(2) == 1){
                Wolf_m* newWolf = new Wolf_m;
                this->myBoard->board[myX][myY].add(newWolf);
                return true;
            }
            else{
                Wolf_f* newWolf = new Wolf_f;
                this->myBoard->board[myX][myY].add(newWolf);
                return true;
            }
            }
        }
    }
    return false;
}

void Wolf_m::relation()
{
    if(eat() == false){
        mate();
    }
}
