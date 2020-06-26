//
// Created by BeastBox on 19/06/2020.
//

#ifndef TELIKI_ERGASIA_BACKPACK_H
#define TELIKI_ERGASIA_BACKPACK_H


#include "Item.h"
#include "Space.h"

using namespace std;

class Backpack : public Space{
public:
    Backpack();

    Backpack(Item *item_list);

    virtual ~Backpack();

    Item * getItem_list() const;

    void setItem_list(Item *item_list);

    int getSize() const;

    void setSize(int size);

    int getAllocated_space() const;

    void setAllocated_space(int allocated_space);

    void print_backpack() const;

    bool add_item(Item &);

    Item * drop_item(string);

    void backpack_clear();

    void print_backpack_file(ostream &) const;
};

#endif //TELIKI_ERGASIA_BACKPACK_H