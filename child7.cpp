#include "child7.h"
#include <iostream>
#include <string>
using namespace std;

//output

//PRINT i j
child7::child7(cl_base* b, string n):cl_base(b,n) {
    n_class = 7;
    cout<<"Ready to work\nFairway";
}

void child7::signal(string& mes){
    if(readiness){
        //cout<<endl<<"Signal from "<<get_abs_path();
    }
    //mes+= " (class: 6)";
}
void child7::handler(string& mes){
    if(readiness){
        vector<string> command = split_command(mes);
        if(command.size()>0 && command[0] == "PRINT"){
            cout<<" ("+command[1]+", "+command[2]+")";
        }else if(command.size()>0 && command[0] == "END"){
            cout<<"\nTurn off the ATM";
        }
    }
}