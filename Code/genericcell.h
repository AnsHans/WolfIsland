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
    virtual ~GenericCell();
    bool isThereWolf_f();
    bool isThereBunny();
    void add(Animal* newAnimal);
    void moveAll();
    void clear();
    void setSafety(bool safe);
    bool getSafety() const;
private:
    std::vector<Animal*> content;
    int females = 0;
    int males = 0;
    int rabbits = 0;
    bool safe_for_wolves = true;
};

#endif // GENERICCELL_H
