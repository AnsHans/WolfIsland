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
    isNewlyBorn = false;
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
    if(isNewlyBorn == true) return;
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
    if(this->isNewlyBorn == false){
        this->reproduce();
    }
}

bool Bunny::isType(std::string string)
{
    if(string == "Bunny") return true;
    else return false;
}

Wolf_f::Wolf_f(int x, int y)
{
    this->setX(x);
    this->setY(y);
}
void Wolf_f::relation(){
    eat();
}
float Wolf_f::getBodyFat()
{
    return this->body_fat;
}

bool Wolf_f::isType(std::string string)
{
    if(string == "Wolf_f") return true;
    else return false;
}
bool Wolf_f::eat()
{
    if (haveEatten == true) return true;
    for(int i = 0; i < myBoard->board[getX()][getY()].content.size(); i++){
        Animal* oneAnimal;
        oneAnimal = myBoard->board[getX()][getY()].content.at(i);
        if(dynamic_cast<Bunny*>(oneAnimal) != nullptr){
               myBoard->killMe(oneAnimal, getX(),getY());
               this->body_fat = this->body_fat + 1;
               return true;
        }
    }
    return false;
}
void Wolf_f::move()
{
    mated = false;
    isNewlyBorn = false;
    //Czy tutaj dać śmierć TODO
    this->body_fat = this->body_fat - 0.1;
    int possible_movements[9][2] = {-1,-1};
    int possible_iterator = -1;
    //Sprawdz wszystkie komórki w okolicy
    for(int i = 0; i < 9; i++){
            int x = this->getX() + moves[i][0];
            int y = this->getY() + moves[i][1];
        if(x >= 0 && y >= 0 && y < Animal::size && x < Animal::size && this->myBoard->board[x][y].getSafety()){
            if(this->myBoard->isThereBunny(x,y)){
                possible_iterator++;
                possible_movements[possible_iterator][0] = x;
                possible_movements[possible_iterator][1] = y;
            }
        }
    }
    if( possible_iterator == -1){
    int newX = 0;
    int newY = 0;

    do{
    int new_parameters = rool();
    newY = getY() + this->moves[new_parameters][1];
    newX = getX() + this->moves[new_parameters][0];
    }while(!(newX >= 0 && newY >= 0 && newX < Animal::size && newY < Animal::size && this->myBoard->board[newX][newY].getSafety()));
    setX(newX);
    setY(newY);
    return;
    }
    // IF WE FOUND A BUNNY !!!
    else{
        int position = randomnum.bounded(possible_iterator+1);
        setX(possible_movements[position][0]);
        setY(possible_movements[position][1]);
        return;
    }
}
bool Wolf_f::mate()
{
    if(this->mated == false && this->isNewlyBorn == false){
        mated = true;
        return true;
    }
    else return false;
}

bool Wolf_f::haveMated()
{
    return this->mated;
}

Wolf_m::Wolf_m(int x, int y)
{
    setX(x);
    setY(y);
}
void Wolf_m::move()
{
    haveEatten = false;
    mated = false;
    this->body_fat = this->body_fat - 0.1;

    int possible_movements[9][2] = {{-1},{-1}};
    int possible_iterator = -1;

    //Sprawdz wszystkie komórki w okolicy dla krolikow
    {
    for(int i = 0; i < 9; i++){
            int x = this->getX() + moves[i][0];
            int y = this->getY() + moves[i][1];
        if(x >= 0 && y >= 0 && y < Animal::size && x < Animal::size && this->myBoard->board[x][y].getSafety()){
            if(this->myBoard->isThereBunny(x,y)){
                possible_iterator++;
                possible_movements[possible_iterator][0] = x;
                possible_movements[possible_iterator][1] = y;
            }
        }
    }
    }
    if(possible_iterator == -1){
        for(int i = 0; i < 9; i++){
                int x = this->getX() + moves[i][0];
                int y = this->getY() + moves[i][1];
            if(x >= 0 && y >= 0 && y < Animal::size && x < Animal::size && this->myBoard->board[x][y].getSafety()){
                if(this->myBoard->isThereWolf_f(x,y)){
                    possible_iterator++;
                    possible_movements[possible_iterator][0] = x;
                    possible_movements[possible_iterator][1] = y;
                }
            }
        }
    }
    //
    if( possible_iterator == -1){
    int newX = 0;
    int newY = 0;

    do{
    int new_parameters = rool();
    newY = getY() + this->moves[new_parameters][1];
    newX = getX() + this->moves[new_parameters][0];
    }while(!(newX >= 0 && newY >= 0 && newX < Animal::size && newY < Animal::size) && this->myBoard->board[newX][newY].getSafety());
    setX(newX);
    setY(newY);
    return;
    }
    // IF WE FOUND A BUNNY OR WOLF_F!!!
    else {
        int position = randomnum.bounded(possible_iterator+1);
        setX(possible_movements[position][0]);
        setY(possible_movements[position][1]);
        return;
    }
}
bool Wolf_m::mate()
{
   for(Animal* oneAnimal : myBoard->board[getX()][getY()].content){
        if(dynamic_cast<Wolf_f*>(oneAnimal) != nullptr){
            Wolf_f* partner = dynamic_cast<Wolf_f*>(oneAnimal);
            //Przypisz wskaźnik do samicy
            //Jezeli moze zostac partnerka
            if(body_fat > 1.35){
            if(partner->isType("Wolf_f") && partner != nullptr){
                //wylosuj plec
                if(randomnum.bounded(2) == 0){
                    Wolf_f* newAnimal;
                    newAnimal = new Wolf_f(getX(),getY());
                    newAnimal->setX(getX());
                    newAnimal->setY(getY());
                    myBoard->board[getX()][getY()].add(newAnimal);
                    return true;
                }
                else{
                    Wolf_m* newAnimal;
                    newAnimal = new Wolf_m(getX(),getY());
                    newAnimal->setX(getX());
                    newAnimal->setY(getY());
                    myBoard->board[getX()][getY()].add(newAnimal);
                    return true;
                }
            }
            }
        }
    }
    return false;
}
void Wolf_m::relation()
{
    if(eat() == false) mate();
}

bool Wolf_m::isType(std::string string)
{
    if(string == "Wolf_m") return true;
    else return false;
}
