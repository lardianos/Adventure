//
// Created by BeastBox on 23/06/2020.
//

#ifndef TELIKI_ERGASIA_SPACE_H
#define TELIKI_ERGASIA_SPACE_H


#include "Item.h"

using namespace std;

class Space {
protected:
    Item * item_list;
    int size;
    int allocated_space;
public:
    Space();

    Space(Item *item_list);

    virtual ~Space();
};


#endif //TELIKI_ERGASIA_SPACE_H
