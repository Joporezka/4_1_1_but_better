#include "child4.h"
#include <iostream>
#include <string>
using namespace std;

//локатор глубины
//SCAN_AQUATORY i j
//GET_DEPTH i j
child4::child4(cl_base* b, string n):cl_base(b,n) { n_class = 4;}

void child4::signal(string& mes){
    if(readiness){

    }

}
void child4::handler(string& mes){
    if(readiness){
        vector<string>command = split_command(mes);
        if(command.size()>0 && command[0] == "GET_DEPTH"){ //RX -> TX
            string mes1 = "SCAN_AQUATORY "+command[1]+" "+command[2];
            this->emit_signal(SIGNAL_D(child4::signal),mes1);

            mes = "GET_DEPTH "+to_string(buffer_i)+" "+to_string(buffer_j)+" "+to_string(buffer_depth);
            this->emit_signal(SIGNAL_D(child4::signal),mes);


        }else if(command.size()>0 && command[0] == "SCAN_AQUATORY"){ //TX -> RX
            buffer_i = stoi(command[1]);
            buffer_j = stoi(command[2]);
            buffer_depth = stoi(command[3]);
        }

    }
}