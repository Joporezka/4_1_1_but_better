#include "child4.h"
#include <iostream>
#include <string>
using namespace std;

child4::child4(cl_base* b, string n):cl_base(b,n) { n_class = 4;}

void child4::signal(string& mes){
    if(readiness){
        cout<<endl<<"Signal from "<<get_abs_path();
    }
    mes+= " (class: 4)";
}
void child4::handler(string& mes){
    if(readiness){
        cout<<endl<<"Signal to "<<get_abs_path()<<" Text: "<<mes;
    }
}