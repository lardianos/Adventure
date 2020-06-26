//
// Created by BeastBox on 19/06/2020.
//

using namespace std;

#include <iostream>
#include <cstring>
#include "Character.h"


Character::Character() {

}

Character::Character(const Backpack &backpack) : backpack(backpack) {

}


Character::~Character() {

}

bool Character::add_to_backpack(Item &it) {
//    cout << it.getName();
    if(backpack.add_item(it) == true)
        return true;
    else
        return false;
}

Item * Character::drop_from_backpack(const char * code) {
    Item *it = backpack.drop_item(code);
    return it;
}

void Character::remove_item(const char * code) {
    backpack.drop_item(code);
}

void Character::print_backpack() const {
    backpack.print_backpack();
}

Item *Character::getItem_list()  {
    return backpack.getItem_list();
}

const Backpack &Character::getBackpack() const {
    return backpack;
}

void Character::setBackpack(const Backpack &backpack) {
    Character::backpack = backpack;
}

Item *Character::getExisting_items() const {
    return existing_items;
}

void Character::setExisting_items(Item *existing_items) {
    Character::existing_items = existing_items;
}

int Character::getExisting_item_num() const {
    return existing_item_num;
}

void Character::setExisting_item_num(int existing_item_num) {
    Character::existing_item_num = existing_item_num;
}

void Character::print_existing_items() const {
    for (int i = 0; i <existing_item_num ; i++) {
        this->existing_items[i].print_item();
    }
}

int Character::getConcatenate_lines() const {
    return concatenate_lines;
}

void Character::setConcatenate_lines(int concatenate_lines) {
    Character::concatenate_lines = concatenate_lines;
}

int Character::getConcatenate_colums() const {
    return concatenate_colums;
}

void Character::setConcatenate_colums(int concatenate_colums) {
    Character::concatenate_colums = concatenate_colums;
}

string **Character::getConcatenate() const {
    return concatenate;
}

void Character::setConcatenate(string **concatenate) {
    Character::concatenate = concatenate;
}

int Character::getWining_item_num() const {
    return wining_item_num;
}

void Character::setWining_item_num(int wining_item_num) {
    Character::wining_item_num = wining_item_num;
}

string *Character::getWining_items() const {
    return wining_items;
}

void Character::setWining_items(string *wining_items) {
    Character::wining_items = wining_items;
}

void Character::print_wining_items() const {
        for (int i = 0; i < wining_item_num ; i++) {
        cout << "Wining item " << wining_items[i] << endl;
    }
}

void Character::print_concatenations_list() const {
    for (int i = 0; i <concatenate_lines ; i++) {
        cout <<"["<< concatenate[i][0] << "]"<<"["<< concatenate[i][1] << "]"<<"["<< concatenate[i][2] << "]" << endl;
    }
}

void Character::backpack_clear() {
    backpack.backpack_clear();
}

void Character::print_backpack_file(ostream & os) const {
    backpack.print_backpack_file(os);
}

void Character::print_existing_items_file(ostream & os) const {
    os << "items" << '\r' << endl;
    for (int i = 0; i <existing_item_num; i++) {
        os << existing_items[i].getCode() << ";";
        os << existing_items[i].getName() << ";";
        os << existing_items[i].getMovable() << endl; //<< //'\r';//<<endl;
    }
}

void Character::print_wining_items_file(ostream & os) const {
    os << "winItems" << '\r' << endl;
    for (int i = 0; i < wining_item_num ; i++) {
        os << wining_items[i] << '\r' << endl;
    }
}

void Character::print_concatenations_list_file(ostream & os) const {
    os << "concatenate" << '\r' << endl;
    for (int i = 0; i <concatenate_lines ; i++) {
        os << concatenate[i][0] << ";" << concatenate[i][1] << ";"<< concatenate[i][2] << '\r' << endl;
    }
}

bool Character::win() const{
    for (int i = 0; i <backpack.getSize(); i++) {
        if(is_in_win_list(backpack.getItem_list()[i].getCode())){
            return true;
        }
    }
    return false;
}

bool Character::is_in_win_list(char * code) const {
    for (int i = 0; i <wining_item_num ; i++) {
        if(strcmp(wining_items[i].c_str(),code)==0 ){
            return true;
        }
    }
    return false;
}

Item Character::make_item(string code) {
    Item new_item;
    for (int i = 0; i <existing_item_num ; i++) {
        if( strcmp( existing_items[i].getCode(), code.c_str() ) == 0 ){
            new_item = existing_items[i];
        }
    }
    return new_item;
}

bool Character::add_two_items(string code1, string code2) {
    for (int i = 0; i < concatenate_lines; i++) {
        cout << concatenate[i][0] << ";" << concatenate[i][1] << ";"<< concatenate[i][2] << ";"<<endl;
        if((concatenate[i][0].compare(code1)==0 && concatenate[i][1].compare(code2)==0)||(concatenate[i][1].compare(code1)==0 && concatenate[i][0].compare(code2)==0)){
            Item it = make_item(concatenate[i][2].c_str());
            it.print_item();
            backpack.add_item(it);
            backpack.drop_item(code1.c_str());
            backpack.drop_item(code2.c_str());
            return true;
        }
    }
    return false;
}

