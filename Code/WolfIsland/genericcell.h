#ifndef GENERICCELL_H
#define GENERICCELL_H
#include <vector>
#pragma once
#include "animal.h"


class GenericCell
{
    friend class GenericBoard;
    friend class Wolf_m;
    friend class Wolf_f;
public:
    GenericCell();
    bool isThereWolf_f();
    bool isThereBunny();
    void add(Animal* newAnimal);
    void moveAll();
    void clear();
private:
    std::vector<Animal*> content;
    int females = 0;
    int males = 0;
    int rabbits = 0;
};

#endif // GENERICCELL_H
