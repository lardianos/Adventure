#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <new>
#include <typeinfo>
#include <list>
#include <iterator>
#include <vector>
#include "Item.h"
#include "Backpack.h"
#include "Environment.h"
#include "Character.h"

#ifdef _WIN32
#include <windows.h>
#pragma execution_character_set( "utf-8" )
#endif //_WIN64

#ifdef _WIN64
#include <windows.h>
    #pragma execution_character_set( "utf-8" )
#endif //_WIN64


using namespace std;

void test_func();
char * sub_string(char *, int, int);
Item make_item(Item *,int ,const char *);
void print_existing_items(Item *, int);

ostream & operator << (ostream &,const Environment &);
ostream & operator << (ostream &,const Character &);

char * sub_string(char * str ,int left, int right){
    if (right > left){
        int len = right - left;
        char * new_str = NULL;
//        cout << "len "<< len <<endl;
//        cout << "left "<< left <<endl;
//        cout << "right "<< right <<endl;
        new_str = new char[len+1];
//        cout << "strlen "<< strlen(new_str) <<endl;
        memset(new_str,0,len);
//        cout << len <<endl;
//        cout << left << ","<< right<<endl;
        for (int i = left, j = 0; i <right+1; i++, j++) {
            new_str[j]=str[i];
//            cout << new_str[j] << ",";
        }
//        cout << endl;
//        cout <<"["<< new_str <<"]" <<endl;
        return new_str;
    } else{
        return NULL;
    }
}

Item make_item(Item * item_list,int item_list_num,const char * item_code){
    Item new_item;
    for (int i = 0; i < item_list_num ; ++i) {
        if(strcmp(item_list[i].getCode(),item_code) == 0){
            new_item = item_list[i];
            break;
        }
    }
    return new_item;
}

ostream & operator << (ostream & os,const Environment & room){
    room.print_environment();
    return os;
}
ostream & operator << (ostream & os,const Character & player){
    player.print_backpack();
    return os;
}

int main(int argc, char **argv) {
#ifdef _WIN32
    SetConsoleOutputCP( 65001 );
#endif //_WIN32
#ifdef _WIN64
    SetConsoleOutputCP( 65001 );
#endif //_WIN64


    fstream f;
    string file_name;
    Character player;
    string selection ="\0";
    string selection2;
    int litle_buffer_num;
    // room dynamic array, filled from the file
    int room_list_num = 0;
    Environment * room_list = new Environment[room_list_num];

    // 2 Dimension dynamic array for item concatenation, filled from the file
    int concatenate_lines = 0, concatenate_colums = 3;
    string **concatenate = new string*[concatenate_lines];

    // 2 Dimension dynamic array for player moves and direction, filled from the file
    int moves_lines = 0, moves_colums = 4;
    int **moves = new int*[moves_lines];

    // Dynamic array for all existing items in game, filled from the file
    int existing_items_size=0;
    Item * existing_items = new Item[existing_items_size];

    // Wining items
    int wining_items_num =0 ;
    string * winig_items = new string[wining_items_num];

    // temporary buffers
    char * litle_buffer = new char[0], * code,* name, * movable;
    char * buffer = new char[256];
    char * moves_buf[4],* desc_buf[2], * room_item_buf[2],*concatenate_buf[3],* wining_item_buf;

    char * copy_buffer;
//    int copy_buffer_size;

    char * copy_buffer_litle;
    int copy_buffer_litle_size;
    cout << "Πληκτρολογήστε Αρχείο Εισόδου." << endl << "> ";

    cin >> file_name;
//    file_name = file_name+".txt";

    // open file
    while (1){
        f.open(file_name,ios::in);
//        f.open("rooms.txt",ios::in);
        if (!f.good()){
            cout << "Δεν υπάρχει αυτό το όνομα αρχείου" << endl;
        }

        if(selection.compare("7") == 0){
            cout << "delete all" << endl;
            if(room_list != NULL){
                delete[] room_list;
                room_list = NULL;
                room_list_num = 0;
                room_list = new Environment[room_list_num];
            }
            if(concatenate != NULL){
                for (int i = 0; i <concatenate_lines ; i++) {
                    delete[] concatenate[i];
                }
                delete [] concatenate;
                concatenate = NULL;
                concatenate_lines = 0;
                concatenate_colums = 3;
                room_list = new Environment[room_list_num];
                concatenate = new string*[concatenate_lines];
            }
            if(moves != NULL){
                for (int i = 0; i < moves_lines ; i++) {
                    delete[] moves[i];
                }
                delete[] moves;
                moves = NULL;
                moves_lines = 0;
                moves_colums = 4;
                moves = new int*[moves_lines];
            }
            if(existing_items != NULL){//existing items renew
                delete[] existing_items;
                existing_items = NULL;
                existing_items_size = 0;
                existing_items = new Item[existing_items_size];
            }
            if(winig_items != NULL){
                delete[] winig_items;
                winig_items = NULL;
                wining_items_num = 0;
                winig_items = new string[wining_items_num];
            }
        }

//================================ START File Reading ====================================
        f.getline(buffer,256);
        f.seekg(0,f.beg);

//        cout << "aaa" <<endl;
        copy_buffer = new char[strlen(buffer)];
        strcpy(copy_buffer,buffer);
        copy_buffer_litle_size = 5;
        copy_buffer_litle = new char[copy_buffer_litle_size];
        copy_buffer_litle = strtok(copy_buffer,"\r\0");

        if(strcmp(copy_buffer_litle,"items") == 0) {
//        cout <<"aaa" << endl;
            while (f.getline(buffer,256) && !f.eof()){
                if(litle_buffer != NULL){
                    memset(litle_buffer,0,strlen(litle_buffer));
                    delete[] litle_buffer;
                    litle_buffer = NULL;
                }
                litle_buffer_num =5;
                litle_buffer = new char[litle_buffer_num];
                litle_buffer = sub_string(buffer,0,4);
                if (litle_buffer == NULL) {
                    cout << "lathos orismata stin substring";
                    return 0;
                }

                if (strcmp(litle_buffer,"moves") == 0){
                    break;
                } else{
//                litle_buffer = NULL;
                    //create new array for dinamic allocation
                    Item * new_existing_items = new Item[existing_items_size+1];
                    for (int i = 0; i < existing_items_size; i++) {
                        new_existing_items[i] = existing_items[i];
                    }
                    code = strtok(buffer,";");
                    name = strtok(NULL,";");
                    movable = strtok(NULL,";");

                    if ((code!= NULL) && (name!=NULL) && (movable!=NULL)) {
                        Item it1(code, name, movable);
                        new_existing_items[existing_items_size] = it1;
                        existing_items_size++;
                        delete[]existing_items;
                        existing_items = new_existing_items;
                    }
                }
            }
        }
        //Moves
        if (strcmp(litle_buffer,"moves") == 0){
            while (f.getline(buffer,256) && !f.eof()){
                if(litle_buffer != NULL){
                    memset(litle_buffer,0,strlen(litle_buffer));
                    delete[] litle_buffer;
                    litle_buffer = NULL;
                }
                litle_buffer_num =8;
                litle_buffer = new char[litle_buffer_num];
                litle_buffer = sub_string(buffer,0,7);
                if (litle_buffer == NULL) {
                    cout << "lathos orismata stin substring";
                    return 0;
                }
                if (strcmp(litle_buffer,"buckpuck") == 0){
                    break;
                } else{

                    moves_buf[0] =  strtok(buffer,";");
                    moves_buf[1] =  strtok(NULL,";");
                    moves_buf[2] =  strtok(NULL,";");
                    moves_buf[3] =  strtok(NULL,";");

//                    cout <<"char "<< moves_buf[0]<<","<< moves_buf[1]<<","<< moves_buf[2]<<","<< moves_buf[3] << endl;
//                    cout <<"atoi "<< atoi(moves_buf[0])<<","<< atoi(moves_buf[1])<<","<< atoi(moves_buf[2])<<","<< atoi(moves_buf[3]) << endl;
                    if ((moves_buf[0]!= NULL) && (moves_buf[1]!=NULL) && (moves_buf[2]!=NULL) && (moves_buf[3]!=NULL)) {
                        //create new array for dinamic allocation
                        int **new_moves = new int*[moves_lines+1];
                        for (int i = 0; i <moves_lines+1 ; i++) {
                            new_moves[i] = new int[moves_colums];
                        }
                        //copy old array to new array
                        for (int i = 0; i < moves_lines ; i++) {
                            for (int j = 0; j < moves_colums ; j++) {
                                new_moves[i][j]=moves[i][j];
                            }
                        }
                        // set the new values;
                        new_moves[moves_lines][0] = atoi(moves_buf[0]);
                        new_moves[moves_lines][1] = atoi(moves_buf[1]);
                        new_moves[moves_lines][2] = atoi(moves_buf[2]);
                        new_moves[moves_lines][3] = atoi(moves_buf[3]);

                        // delete old array
                        for (int i = 0; i < moves_lines ; i++) {
                            delete[] moves[i];
                        }
                        delete[] moves;
                        // increse lines
                        moves_lines++;
                        // set old new array to new array
                        moves = new_moves;
                    }
                }
            }
        }
        //Backpack Items
        if(strcmp(litle_buffer,"buckpuck") == 0) {
//        cout << "youhou" << endl;
            player.backpack_clear();
            while (f.getline(buffer,256) && !f.eof()){
                if(litle_buffer != NULL){
//        delete[] litle_buffer;
//        litle_buffer = NULL;
//                memset(litle_buffer,0,strlen(litle_buffer));
                    if(litle_buffer != NULL){
                        memset(litle_buffer,0,strlen(litle_buffer));
                        delete[] litle_buffer;
                        litle_buffer = NULL;
                    }
                    litle_buffer_num =8;
                    litle_buffer = new char[litle_buffer_num];
                    litle_buffer = sub_string(buffer,0,7);
                }
                if (litle_buffer == NULL) {
                    cout << "lathos orismata stin substring";
                    return 0;
                }
                if (strcmp(litle_buffer,"roomdesc") == 0){
                    break;
                } else{
                    Item it1 = make_item(existing_items,existing_items_size,strtok(buffer,"\r"));
                    player.add_to_backpack(it1);
                }
            }
        }
        //Room Description

        if(strcmp(litle_buffer,"roomdesc") == 0) {
//        cout << "xaxa";
            for (int i = 0; i < room_list_num ; i++) {
                room_list[i].room_clear();
            }
            while (f.getline(buffer,256) && !f.eof()){
                if(litle_buffer != NULL){
                    memset(litle_buffer,0,strlen(litle_buffer));
                    delete[] litle_buffer;
                    litle_buffer = NULL;
                }
                litle_buffer_num =9;
                litle_buffer = new char[litle_buffer_num];
                litle_buffer = sub_string(buffer,0,8);
                if (litle_buffer== NULL) {
                    cout << "lathos orismata stin substring";
                    return 0;
                }
                if (strcmp(litle_buffer,"roomitems") == 0){
                    break;
                } else{
                    desc_buf[0] = strtok(buffer,";");
                    desc_buf[1] = strtok(NULL,";");
                    desc_buf[1][strlen(desc_buf[1])-1]='\0';
                    if ((desc_buf[0]!= NULL) && (desc_buf[1]!=NULL)){
                        //create new array for dinamic allocation
                        Environment * new_room_list = new Environment[room_list_num+1];
                        for (int i = 0; i < room_list_num; i++) {
                            new_room_list[i] = room_list[i];
                        }
                        Environment room;
                        room.setRoom_id(atoi(desc_buf[0]));
                        room.setRoom_message(desc_buf[1]);
                        new_room_list[room_list_num] = room;
                        room_list_num++;
                        delete[] room_list;
                        room_list = new_room_list;
                    }
                }
            }
        }
        //Room Items
        if(strcmp(litle_buffer,"roomitems") == 0) {
            while (f.getline(buffer,256) && !f.eof()){
                if(litle_buffer != NULL){
                    memset(litle_buffer,0,strlen(litle_buffer));
                    delete[] litle_buffer;
                    litle_buffer = NULL;
                }
                litle_buffer_num =11;
                litle_buffer = new char[litle_buffer_num];
                litle_buffer = sub_string(buffer,0,10);
                if (litle_buffer== NULL) {
                    cout << "lathos orismata stin substring";
                    return 0;
                }
                if (strcmp(litle_buffer,"concatenate") == 0){
                    break;
                } else{
                    room_item_buf[0] = strtok(buffer,";");
                    room_item_buf[1] = strtok(NULL,";");
                    room_item_buf[1][strlen(room_item_buf[1])-1] = '\0';
                    if((room_item_buf[0] != NULL) && (room_item_buf[1] != NULL)){
                        Item it1 = make_item(existing_items,existing_items_size,room_item_buf[1]);
                        room_list[atoi(room_item_buf[0])].drop_item(it1);
                    }
                }
            }
        }
        //Concatenation Items
        if(strcmp(litle_buffer,"concatenate") == 0) {
            while (f.getline(buffer,256) && !f.eof()){
                if(litle_buffer != NULL){
                    memset(litle_buffer,0,strlen(litle_buffer));
                    delete[] litle_buffer;
                    litle_buffer = NULL;
                }
                litle_buffer_num =8;
                litle_buffer = new char[litle_buffer_num];
                litle_buffer = sub_string(buffer,0,7);
                if (litle_buffer == NULL) {
                    cout << "lathos orismata stin substring";
                    return 0;
                }
                if (strcmp(litle_buffer,"winItems") == 0){
                    break;
                } else{
                    concatenate_buf[0] = strtok(buffer,";");
                    concatenate_buf[1] = strtok(NULL,";");
                    concatenate_buf[2] = strtok(NULL,";");
                    concatenate_buf[2][strlen(concatenate_buf[2])-1] = '\0';
//                cout <<"["<< concatenate_buf[0]<<"]" <<"["<< concatenate_buf[1]<<"]" <<"["<< concatenate_buf[2]<<"]" << endl;
                    if((concatenate_buf[0]!=NULL)&&(concatenate_buf[1]!=NULL)&&(concatenate_buf[2]!=NULL)){
                        //create new array for dinamic allocation
                        string **new_concatenate = new string*[concatenate_lines+1];
                        for (int i = 0; i <concatenate_lines+1 ; i++) {
                            new_concatenate[i] = new string[concatenate_colums];
                        }

                        //copy old array to new array
                        for (int i = 0; i < concatenate_lines; i++) {
                            for (int j = 0; j < concatenate_colums ; j++) {
                                new_concatenate[i][j] = concatenate[i][j];
                            }
                        }
                        // set the new values
                        new_concatenate[concatenate_lines][0] = concatenate_buf[0];
                        new_concatenate[concatenate_lines][1] = concatenate_buf[1];
                        new_concatenate[concatenate_lines][2] = concatenate_buf[2];
                        // delete old array
                        for (int i = 0; i <concatenate_lines ; i++) {
                            delete[] concatenate[i];
                        }
                        delete[] concatenate;
                        // increse lines
                        concatenate_lines++;
                        // set old new array to new array
                        concatenate = new_concatenate;
                    }
                }
            }
        }
        //Wining Items
        if(strcmp(litle_buffer,"winItems") == 0) {
            while (f.getline(buffer,256)){
                wining_item_buf= buffer;
                if((winig_items != NULL)){
                    string * new_wining_items = new string[wining_items_num+1];
                    for (int i = 0; i < wining_items_num; i++) {
                        new_wining_items[i] = winig_items[i];
                    }
                    new_wining_items[wining_items_num] = wining_item_buf;
                    delete[] winig_items;
                    wining_items_num++;
                    winig_items = new_wining_items;
                    if(f.eof()){
                        break;
                    }
                }
            }
        }
        f.clear();
        f.close();
//================================ END File Reading ====================================


//=========================== START SETUP  ============================================

//=========================== END SETUP  ==============================================

        int instant_room = 0; // starting from room 0

        const char * directions[] = {"Βοράς","Νότος","Ανατολή","Δύση"};
        int directions_num = 4;

        player.setExisting_items(existing_items);
        player.setExisting_item_num(existing_items_size);
        player.setConcatenate(concatenate);
        player.setConcatenate_colums(concatenate_colums);
        player.setConcatenate_lines(concatenate_lines);
        player.setWining_items(winig_items);
        player.setWining_item_num(wining_items_num);

//    player.print_existing_items();
//    player.print_concatenations_list();
//    player.print_wining_items();

//================================ Start Game LOOP ====================================
        while (1){
            if(player.win()){
                cout << "Congratulations!!! you win!" << endl;
                return 0;
            }
            cout << "----------------------------------------" << endl;
            room_list[instant_room].print_room_message();
            cout << "[Διαθέσιμες κατεύθυνσης]" << endl;
            for (int i = 0; i <directions_num ; ++i) {
                if(moves[instant_room][i] != -1){
                    cout << directions[i] << " = [" << i <<"] ";
                }
            }
            cout << endl;
            cout << "[Άλλες Επιλογές]" <<endl;
            cout << "[4] = Αναζιτιση Περιβαλοντος"<< endl<< "[5] = Εμφάνιση Σακιδίου"<< endl<< "[6] = Έξοδος" <<endl << "[7] = Restart" <<endl<< "> ";
            cout << "Δώσε Αριθμό Επιλογή:" <<endl << "> ";
            cin >> selection;
            if( (selection.compare("0") >= 0) && (selection.compare("7") <= 0)){
                if( (selection.compare("0") >= 0) && (selection.compare("3") <= 0)){
                    if (moves[instant_room][atoi(selection.c_str())] == -1){
                        cout << "Μη Διαθέσιμη Κατεύθυνση" << endl;
                    } else{
                        instant_room = moves[instant_room][atoi(selection.c_str())];
                    }
                } else if(selection.compare("4") == 0){
                    while (1) {
                        cout << room_list[instant_room];
                        cout << "[Διαθέσιμες Επιλογές]" <<endl;
                        cout << "[1] = Συλλογή Αντικειμένου"<< endl<< "[2] = Έξοδος" <<endl<< "> ";
                        cin >> selection;
                        if( (selection.compare("1") >= 0) && (selection.compare("2") <= 0)){
                            if(selection.compare("1") == 0){
                                while (1){
                                    cout << "Επέλεξε Αντικείμενο:" <<endl<< "> ";
                                    cin >> selection;
                                    if( (selection.compare("0") >= 0) && (selection.compare("9") <= 0)){
                                        player.add_to_backpack(*room_list[instant_room].pick_item(room_list[instant_room].getItem_list()[atoi(selection.c_str())].getCode()));
                                        break;
                                    } else{
                                        cout << "Λάθος επιλογή" << endl;
                                    }
                                }
                            } else if (selection.compare("2") == 0){
                                break;
                            }
                        } else{
                            cout << "Λάθος επιλογή" << endl;
                        }
                    }
                } else if(selection.compare("5") == 0){
//                player.print_backpack();
                    while (1) {
                        cout << player;
                        cout << "[Διαθέσιμες Επιλογές]" <<endl;
                        cout << "[1] = Πέταγμα Αντικειμένου"<< endl<< "[2] = Καταστροφή Αντικειμένου"<< endl<< endl<< "[3] = Συνδυασμός Αντικείμενων"<< endl<< "[4] = Έξοδος" <<endl<< "> ";
                        cin >> selection;
                        if( (selection.compare("1") >= 0) && (selection.compare("4") <= 0)){
                            if(selection.compare("1") == 0){
                                while (1){
                                    cout << "Επέλεξε Αντικείμενο:" <<endl<< "> ";
                                    cin >> selection;
                                    if( (selection.compare("0") >= 0) && (selection.compare("9") <= 0)){
                                        room_list[instant_room].drop_item(*player.drop_from_backpack(player.getItem_list()[atoi(selection.c_str())].getCode()));
                                        break;
                                    } else{
                                        cout << "Λάθος επιλογή" << endl;
                                    }
                                }
                            } else if (selection.compare("2") == 0){//
                                while (1){
                                    cout << "Επέλεξε Αντικείμενο:" <<endl<< "> ";
                                    cin >> selection;
                                    if( (selection.compare("0") >= 0) && (selection.compare("9") <= 0)){
                                        player.drop_from_backpack(player.getItem_list()[atoi(selection.c_str())].getCode());
                                        break;
                                    } else{
                                        cout << "Λάθος επιλογή" << endl;
                                    }
                                }
                            } else if (selection.compare("3") == 0){
                                cout << "Sindiasmos Antikimenon" << endl;
                                while (1){
                                    cout << "Επέλεξε Αντικείμενο 1:" <<endl<< "> ";
                                    cin >> selection;
                                    if( (selection.compare("0") >= 0) && (selection.compare("9") <= 0)){
                                        break;
                                    } else{
                                        cout << "Λάθος επιλογή" << endl;
                                    }
                                }
                                while (1){
                                    cout << "Επέλεξε Αντικείμενο 2:" <<endl<< "> ";
                                    cin >> selection2;
                                    if( (selection2.compare("0") >= 0) && (selection2.compare("9") <= 0)){
                                        break;
                                    } else{
                                        cout << "Λάθος επιλογή" << endl;
                                    }
                                }
                                if(player.add_two_items(player.getItem_list()[atoi(selection.c_str())].getCode(),player.getItem_list()[atoi(selection2.c_str())].getCode())){
                                    cout << "Δημιουργήθηκε Επιτυχώς" <<endl;
                                } else{
                                    cout << "Μη διαθέσιμος συνδυασμός" <<endl;
                                }
                            } else if (selection.compare("4") == 0){
                                break;
                            }
                        } else{
                            cout << "Λάθος επιλογή" << endl;
                        }
                    }
                } else if(selection.compare("6") == 0){
                    while (1){
                        cout << "Αποθήκευσή;" <<endl <<"Yes or No" << endl << "> ";
                        cin >> selection;
                        if((selection.compare("no")==0)||(selection.compare("No")==0)||(selection.compare("NO")==0)||(selection.compare("N")==0)||(selection.compare("n")==0)){
                            cout << "Καλή Συνείχα!" << endl;
                            return 0;
                        } else if((selection.compare("yes")==0)||(selection.compare("Yes")==0)||(selection.compare("YES")==0)||(selection.compare("Y")==0)||(selection.compare("y")==0)){
                            cout << "Δώσε όνομα αρχείου" <<endl << "> ";
                            cin >> selection;
                            cout << "Τύπωμα στο αρχείο " << selection << endl;

                            fstream f2;
                            f2.open(selection, ios::out);
                            if(!f.good()){
                                cout << "file not open "<<endl;
                            }

                            player.print_existing_items_file(f2);
                            f2 << "moves\r" << endl;
                            for (int i = 0; i < moves_lines ; i++) {
                                for (int j = 0; j <moves_colums ; j++) {
                                    if(j==(moves_colums-1)){
                                        f2 << moves[i][j];
                                    } else{
                                        f2 << moves[i][j] << ";";
                                    }
                                }
                                f2 << '\r' << endl;
                            }
                            player.print_backpack_file(f2);

                            f2 << "roomdesc" <<'\r'<< endl;
                            for (int i = 0; i <room_list_num ; i++) {
                                room_list[i].print_room_message_file(f2);
                            }
                            f2 << "roomitems" <<'\r'<< endl;
                            for (int i = 0; i <room_list_num ; i++) {
                                room_list[i].print_environment_file(f2);
                            }
                            player.print_concatenations_list_file(f2);
                            player.print_wining_items_file(f2);
                            f2.close();
                            cout << "Καλή Συνείχα!" << endl;
                            return 0;
                        }
                    }
                } else if (selection.compare("7") == 0){
                    break;
                }
            } else{
                cout << "Λάθος επιλογή" << endl;
                continue;
            }
        }
    }
    return 0;
}
