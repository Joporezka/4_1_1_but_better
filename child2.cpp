#include "child2.h"
#include <iostream>
#include <string>
using namespace std;

//акватория
//SCAN_AQUATORY i j depth(on emit)
child2::child2(cl_base* b, string n):cl_base(b,n) {
    n_class = 2;

}

void child2::signal(string& mes){
    if(readiness){
        //cout<<endl<<"Signal from "<<get_abs_path();
    }
    //mes+= " (class: 2)";
}
void child2::handler(string& mes){
    if(readiness){
        vector<string> command = split_command(mes);
        if(command.size()>0 && command[0]=="SCAN_AQUATORY"){ //RX -> TX
            int i = stoi(command[1]);
            int j = stoi(command[2]);
            mes="SCAN_AQUATORY "+to_string(i)+" "+to_string(j)+" "+to_string(aquatory[i][j]);//TX
            this->emit_signal(SIGNAL_D(child2::signal),mes);
        }

    }
}
void child2::construct_aquatory(){
    aquatory = new int*[n];
    for(int i=0;i<n;i++){
        aquatory[i] = new int[m];
    }
}

child2::~child2(){
    delete[] aquatory;
}