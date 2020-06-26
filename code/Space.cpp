//
// Created by BeastBox on 23/06/2020.
//

using namespace std;

#include "Space.h"

Space::Space() {
    size = 10;
    allocated_space=0;
    item_list = NULL;
    item_list = new Item[size];
    for (int i = 0; i < size; i++) {
        item_list[i].clear();
    }
}

Space::Space(Item *item_list) : item_list(item_list) {}

Space::~Space() {

}

