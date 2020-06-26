//
// Created by BeastBox on 16/06/2020.
//

#ifndef ASK_4_MYEXC_H
#define ASK_4_MYEXC_H

#include <string>
#include <string.h>

using namespace std;
class MyExc {
public:
    int exc_code;
    string exc_message;

    MyExc(int exc_code, string exc_message);
};


#endif //ASK_4_MYEXC_H
