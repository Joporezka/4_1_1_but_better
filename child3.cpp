#include "child3.h"
#include <iostream>
#include <string>
using namespace std;

//корабль
child3::child3(cl_base* b, string n):cl_base(b,n) { n_class = 3;}

void child3::signal(string& mes){
    if(readiness){
        //cout<<endl<<"Signal from "<<get_abs_path();
        //cout<<"signal: "<<mes<<endl;
    }
    //mes+= " (class: 3)";
}
void child3::handler(string& mes){
    if(readiness){
        vector<string> command  = split_command(mes);
        if(command.size()>0 && command[0] == "GET_POSITION"){ //RX -> TX
            string mes = "GET_POSITION "+to_string(i)+" "+to_string(j)+" "+direction;
            this->emit_signal(SIGNAL_D(child3::signal),mes);

        }else if(command.size()>0 && command[0] == "SET_POSITION"){//RX
            i = stoi(command[1]);
            j= stoi(command[2]);
            direction = command[3];

        }

    }
}