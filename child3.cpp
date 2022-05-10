#include "child3.h"
#include <iostream>
#include <string>
using namespace std;

child3::child3(cl_base* b, string n):cl_base(b,n) { n_class = 3;}

void child3::signal(string& mes){
    if(readiness){
        cout<<endl<<"Signal from "<<get_abs_path();
    }
    mes+= " (class: 3)";
}
void child3::handler(string& mes){
    if(readiness){
        cout<<endl<<"Signal to "<<get_abs_path()<<" Text: "<<mes;
    }
}