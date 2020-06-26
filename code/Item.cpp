//
// Created by BeastBox on 19/06/2020.
//

using namespace std;

#include <cstring>
#include <iostream>
#include "Item.h"

Item::Item() {
    code_num = 0;
    name_num = 0;
    movable_num = 0;

    code = NULL;
    name = NULL;
    movable = NULL;
//    cout << code;
    code = new char[code_num+1];
    name = new char[name_num+1];
    movable = new char[movable_num+1];

    memset(code,0,code_num+1);
    memset(name,0,name_num+1);
    memset(movable,0,movable_num+1);
}

Item::Item(const char *code, const char *name, const char *movable){

    this->code_num = strlen(code);
    this->name_num = strlen(name);
    this->movable_num = strlen(movable);

    this->code = new char[code_num+1];
    strcpy(this->code,code);
    this->code[code_num]='\0';
    this->name = new char[name_num+1];
    strcpy(this->name,name);
    this->name[name_num]='\0';
    this->movable = new char[movable_num+1];
    strcpy(this->movable,movable);
    this->movable[movable_num]='\0';
}

void Item::clear() {
    delete[]code;
    delete[]name;
    delete[]movable;

    code = NULL;
    name = NULL;
    movable = NULL;

    code_num = 0;
    name_num = 0;
    movable_num = 0;

    code = new char[code_num+1];
    name = new char[name_num+1];
    movable = new char[movable_num+1];

    memset(code,0,code_num+1);
    memset(name,0,name_num+1);
    memset(movable,0,movable_num+1);

}

void Item::operator=(Item it) {

    if((this->code != NULL)&&(this->name!= NULL)&&(this->movable!= NULL)){
        delete[] this->code;
        delete[] this->name;
        delete[] this->movable;
        this->code = NULL;
        this->name = NULL;
        this->movable = NULL;
    }

    this->code_num = strlen(it.getCode());
    this->name_num = strlen(it.getName());
    this->movable_num = strlen(it.getMovable());

    this->code = new char[this->code_num];
    this->name = new char[this->name_num];
    this->movable = new char[this->movable_num];

    strcpy(this->code,it.getCode());
    strcpy(this->name,it.getName());
    strcpy(this->movable,it.getMovable());


}

char *Item::getCode() const {
    return code;
}

void Item::setCode(char *code) {
    Item::code = code;
}

char *Item::getName() const {
    return name;
}

void Item::setName(char *name) {
    Item::name = name;
}

char *Item::getMovable() const {
    return movable;
}

void Item::setMovable(char *movable) {
    Item::movable = movable;
}

void Item::print_item() {
    cout << "Code " << this->getCode() << " Name " << this->getName() <<" Movable "<< this->getMovable() << endl;

}

bool Item::is_movable() {
    if(strcmp(movable,"1\r") == 0){
        return true;
    } else{
        return false;
    }
}

Item::~Item() {

}