#include "child5.h"
#include <iostream>
#include <string>
using namespace std;

child5::child5(cl_base* b, string n):cl_base(b,n) { n_class = 5;}

void child5::signal(string& mes){
    if(readiness){
        cout<<endl<<"Signal from "<<get_abs_path();
    }
    mes+= " (class: 5)";
}
void child5::handler(string& mes){
    if(readiness){
        cout<<endl<<"Signal to "<<get_abs_path()<<" Text: "<<mes;
    }
}