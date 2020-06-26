//
// Created by BeastBox on 19/06/2020.
//

#ifndef TELIKI_ERGASIA_ENVIRONMENT_H
#define TELIKI_ERGASIA_ENVIRONMENT_H


#include "Item.h"
#include "Space.h"

using namespace std;

class Environment : public Space{

private:
    int room_id;
    char * room_message;
    int room_message_num;
public:
    Environment();

    Environment(Item *item_list);

    virtual ~Environment();

    char *getRoom_message() const;

    void setRoom_message( const char *room_message);

    Item *getItem_list() const;

    void setItem_list(Item *item_list);

    int getSize() const;

    void setSize(int size);

    int getAllocated_space() const;

    void setAllocated_space(int allocated_space);

    void print_room_message() const;

    void print_environment() const;

    bool drop_item(Item &);

    Item * pick_item(string);

    void print_room_message_file(ostream &) const;

    void print_environment_file(ostream &) const;

    int getRoom_id() const;

    void setRoom_id(int room_id);

    void room_clear();

};


#endif //TELIKI_ERGASIA_ENVIRONMENT_H
