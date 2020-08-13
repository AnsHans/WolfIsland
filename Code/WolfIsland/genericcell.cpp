#include "genericcell.h"

GenericCell::GenericCell()
{

}

bool GenericCell::isThereBunny()
{
    for(Animal* i : this->content){
      if(dynamic_cast<Bunny*>(i) != nullptr) return true;
    }
    return false;
}

void GenericCell::add(Animal *newAnimal)
{
    this->content.push_back(newAnimal);
    if(dynamic_cast<Wolf_m*>(newAnimal) != nullptr) males++;
    else if(dynamic_cast<Wolf_f*>(newAnimal) != nullptr) females++;
    else if(dynamic_cast<Bunny*>(newAnimal) != nullptr) rabbits++;

}
bool GenericCell::isThereWolf_f()
{
    for(Animal* i : this->content){
        if(dynamic_cast<Wolf_f*>(i) != nullptr) return true;
    }
    return false;
}

void GenericCell::moveAll()
{
    for(Animal* oneAnimal : content){
       oneAnimal->move();
    }
}

void GenericCell::clear()
{
    for(Animal* oneAnimal : content){
        delete oneAnimal;
        oneAnimal = nullptr;
    }
    content.clear();
    this->males = 0;
    this->females = 0;
    this->rabbits = 0;
}
