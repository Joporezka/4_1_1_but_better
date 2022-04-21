#include "cl_base.h"
#include "child2.h"
#include "child3.h"
#include "child4.h"
#include "child5.h"
#include "child6.h"
#include "cl_application.h"
#include <iostream>
#include <string>
using namespace std;


void cl_application::bild_tree_objects() {
    string parentI;
    string childI;
    int cl_num,readiness;
    cin >> parentI;
    //создание головного объекта
    this->set_name(parentI);

    while (true)
    {
        cin >> parentI;
        if(parentI=="endtree") break;
        cin >> childI;
        cin >> cl_num;
        child2* ch2 = new child2(this->get_object_by_name(parentI),childI);
        /*if(cl_num==2)
            child2* ch2 = new child2(this->get_object_by_name(parentI),childI);
        else if(cl_num==3)
            child3* ch3 = new child3(this->get_object_by_name(parentI),childI);
        else if(cl_num==4)
            child4* ch4 = new child4(this->get_object_by_name(parentI),childI);
        else if(cl_num==5)
            child5* ch5 = new child5(this->get_object_by_name(parentI),childI);
        else
            child6* ch6 = new child6(this->get_object_by_name(parentI),childI);*/
    }

   /* while(cin>>child>>readiness){
    	this->get_object_by_name(child)->set_readiness(readiness);
    }*/
}

int cl_application::exec_app() {
    this->print_tree_ready();
    return 0;
}
