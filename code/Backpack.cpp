//
// Created by BeastBox on 19/06/2020.
//

using namespace std;

#include <iostream>
#include <cstring>
#include "Backpack.h"


Backpack::Backpack(): Space(){

}

Backpack::Backpack(Item *item_list) :
Space(item_list) {

}

Item * Backpack::getItem_list() const {
    return item_list;
}

void Backpack::setItem_list(Item *item_list) {
    Backpack::item_list = item_list;
}

int Backpack::getSize() const {
    return size;
}

void Backpack::setSize(int size) {
    Backpack::size = size;
}

int Backpack::getAllocated_space() const {
    return allocated_space;
}

void Backpack::setAllocated_space(int allocated_space) {
    Backpack::allocated_space = allocated_space;
}


void Backpack::print_backpack() const {
    cout << "[Σακίδιο]"<< endl;
    for (int i = 0; i < size ; i++) {
        cout << "["<< i <<"]_" << item_list[i].getName() << " ";
        if (i == 4){
            cout << endl;
        }
    }
    cout << endl;
}

bool Backpack::add_item(Item & item) {
//    cout <<"aloc space"<< allocated_space <<" size " <<size << " size-1 " <<size-1 << endl;
    if(allocated_space < size){
        for (int i = 0; i <size; i++) {
            if(strlen(item_list[i].getName()) == 0){
                item_list[i]=item;
                allocated_space++;
                break;
            }
        }
        return true;
    } else{
        return false;
    }
}

Item * Backpack::drop_item(string code) {
    Item *it = new Item("","","");
    for (int i = 0; i < size ; i++) {
        if (strcmp(item_list[i].getCode(),code.c_str())==0){
            *it = item_list[i];
            item_list[i].clear();
            allocated_space--;
            break;
        }
    }
    return it;
}

Backpack::~Backpack() {

}

void Backpack::backpack_clear() {
    for (int i = 0; i <size ; i++) {
        item_list[i].clear();
    }
}

void Backpack::print_backpack_file(ostream & os) const {
    os << "buckpuck" << '\r' << endl;
    for (int i = 0; i <size ; ++i) {
        if(strlen(item_list[i].getCode())!=0){
            os << item_list[i].getCode()<< '\r' << endl;
        }
    }
}

