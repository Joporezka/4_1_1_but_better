#include "child6.h"
#include <iostream>
#include <string>
using namespace std;

child6::child6(cl_base* b, string n):cl_base(b,n) { n_class = 6;}

void child6::signal(string& mes){
    if(readiness){
        cout<<endl<<"Signal from "<<get_abs_path();
    }
    mes+= " (class: 6)";
}
void child6::handler(string& mes){
    if(readiness){
        cout<<endl<<"Signal to "<<get_abs_path()<<" Text: "<<mes;
    }
}