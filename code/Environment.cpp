//
// Created by BeastBox on 19/06/2020.
//

using namespace std;

#include <cstring>
#include <iostream>
#include "Environment.h"

Environment::Environment(): Space() {
    room_message_num = 0;
    room_message = NULL;
    room_message = new char[room_message_num];
}

Environment::Environment(Item *item_list) : Space(item_list) {

}

char *Environment::getRoom_message() const {
    return room_message;
}

void Environment::setRoom_message(const char *room_message) {
    this->room_message_num = strlen(room_message);
    this->room_message = NULL;
    this->room_message = new char[room_message_num+1];
    memset(this->room_message,0,room_message_num+1);
    strcpy(this->room_message,room_message);
//    this->room_message[room_message_num]='\0';
}

Item *Environment::getItem_list() const {
    return item_list;
}

void Environment::setItem_list(Item *item_list) {
    Environment::item_list = item_list;
}

int Environment::getSize() const {
    return size;
}

void Environment::setSize(int size) {
    Environment::size = size;
}

int Environment::getAllocated_space() const {
    return allocated_space;
}

void Environment::setAllocated_space(int allocated_space) {
    Environment::allocated_space = allocated_space;
}


void Environment::print_room_message() const{
    cout <<"\""<< getRoom_message() << "\""<< endl;
}

void Environment::print_environment() const {
    cout << "[Περιβάλλον]"<< endl;
    for (int i = 0; i < size; i++) {
        cout << "["<< i <<"]_" << item_list[i].getName() << " ";
        if (i == 4){
            cout << endl;
        }
    }
    cout << endl<< endl;
}

bool Environment::drop_item(Item & item) {
    if(allocated_space != size-1){
        for (int i = 0; i <size ; i++) {
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

Item * Environment::pick_item(string code) {
    Item *it = new Item("","","");
    for (int i = 0; i < size ; i++) {
        if (strcmp(item_list[i].getCode(),code.c_str()) == 0){
            *it = item_list[i];
            item_list[i].clear();
            break;
        }
    }
    return it;
}

Environment::~Environment() {

}

void Environment::print_room_message_file(ostream & os) const {
    os << room_id <<";"<<room_message << '\r' << endl;
}

void Environment::print_environment_file(ostream & os) const {
    for (int i = 0; i <size ; ++i) {
        if(strlen(item_list[i].getCode())!=0){
            os << room_id <<";"<<item_list[i].getCode() << '\r' << endl;
        }
    }
}

int Environment::getRoom_id() const {
    return room_id;
}

void Environment::setRoom_id(int room_id) {
    Environment::room_id = room_id;
}

void Environment::room_clear() {
    for (int i = 0; i <size ; i++) {
        item_list[i].clear();
    }
}