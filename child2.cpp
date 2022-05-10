#include "child2.h"
#include <iostream>
#include <string>
using namespace std;

child2::child2(cl_base* b, string n):cl_base(b,n) { n_class = 2;}

void child2::signal(string& mes){
    if(readiness){
        cout<<endl<<"Signal from "<<get_abs_path();
    }
    mes+= " (class: 2)";
}
void child2::handler(string& mes){
    if(readiness){
        cout<<endl<<"Signal to "<<get_abs_path()<<" Text: "<<mes;
    }
}