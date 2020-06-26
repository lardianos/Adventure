//
// Created by BeastBox on 19/06/2020.
//

#ifndef TELIKI_ERGASIA_CHARACTER_H
#define TELIKI_ERGASIA_CHARACTER_H


#include "Backpack.h"

using namespace std;

class Character {
private:
    Backpack backpack;

    Item * existing_items;
    int existing_item_num;

    int concatenate_lines;
    int concatenate_colums;
    string ** concatenate;

    int wining_item_num;
    string * wining_items;


public:
    Character();

    Character(const Backpack &backpack);

    virtual ~Character();

    Item *getItem_list();

    const Backpack &getBackpack() const;

    void setBackpack(const Backpack &backpack);

    Item *getExisting_items() const;

    void setExisting_items(Item *existing_items);

    int getExisting_item_num() const;

    void setExisting_item_num(int existing_item_num);

    int getConcatenate_lines() const;

    void setConcatenate_lines(int concatenate_lines);

    int getConcatenate_colums() const;

    void setConcatenate_colums(int concatenate_colums);

    string **getConcatenate() const;

    void setConcatenate(string **concatenate);

    int getWining_item_num() const;

    void setWining_item_num(int wining_item_num);

    string *getWining_items() const;

    void setWining_items(string *wining_items);

    bool add_to_backpack(Item &);

    Item * drop_from_backpack(const char *);

    void remove_item(const char *);

    void backpack_clear();

    void print_backpack() const;

    void print_existing_items() const;

    void print_wining_items() const;

    void print_concatenations_list() const;

    void print_backpack_file(ostream &) const;

    void print_existing_items_file(ostream &) const;

    void print_wining_items_file(ostream &) const;

    void print_concatenations_list_file(ostream &) const;

    bool win() const;

    bool is_in_win_list(char *) const;

    Item make_item(string code);

    bool add_two_items(string, string);


};

#endif //TELIKI_ERGASIA_CHARACTER_H
