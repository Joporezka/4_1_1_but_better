#include "cl_base.h"
#include "child.h"
#include "cl_application.h"
#include <iostream>
#include <string>
using namespace std;


cl_application::cl_application(cl_base *parent):
    cl_base(parent,"application")
{
    //static cl_base* application_pointer = this;
}

void cl_application::bild_tree_objects() {
    string name2;
    string name1;
    cin >> name1;
    child* child1 = new child(this, name1); //создание головного объекта
    while (true)
    {
        cin >> name1 >> name2; //ввод наследуемого класса и наследующего
        if (name1 == name2) //условие выхода
        {
            return;
        }
        child* child2 = new child(this->get_object_by_name(name1),name2); //создание дочернего класса
    }
}

int cl_application::exec_app() {
    cout<<this->children[0]->get_name()<<endl;
    this->children[0]->print_tree();
    return 0;
}
