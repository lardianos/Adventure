//
// Created by BeastBox on 19/06/2020.
//

#ifndef TELIKI_ERGASIA_ITEM_H
#define TELIKI_ERGASIA_ITEM_H


#include <string>

using namespace std;

class Item {
private:
    char * code;
    char * name;
    char * movable;
    int code_num;
    int name_num;
    int movable_num;
public:
    Item();

    Item(const char *code,const char *name,const char *movable);

    virtual ~Item();

    char *getCode() const;

    void setCode(char *code);

    char *getName() const;

    void setName(char *name);

    char *getMovable() const;

    void setMovable(char *movable);

    void  clear();

    void operator=(Item);

    void print_item();

    bool is_movable();

};


#endif //TELIKI_ERGASIA_ITEM_H
