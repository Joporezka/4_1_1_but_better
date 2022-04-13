//
// Created by Алексей on 12.03.2022.
//
#include "cl_base.h"
#include <string>
#include <iostream>
using namespace std;
cl_base::cl_base(cl_base *parent, string name) {
    this->parent = parent;
    this->name = name;
    if(parent!= nullptr) parent->children.push_back(this);
}

void cl_base::set_name(string name) {
    this->name = name;
}

string cl_base::get_name() {
    return this->name;
}

void cl_base::print_tree()
{
    cout<< this->get_name()<<" ";
    for (int i = 0; i < children.size(); i++)
    {
        cout<<children[i]->get_name();
        if(i!=children.size()-1) cout<<" ";
    }
    //cout<<endl;
    for(int i = 0; i < children.size(); i++)
    {
        if(children[i]->children.size()!=0)
        {
            cout<<endl;
            children[i]->print_tree();
        }

    }

}

cl_base* cl_base::get_object_by_name(string name) //получение объекта по имении в дереве иерархии
{
    for (size_t i = 0; i < children.size(); i++) //поиск в векторе прямых наследников
    {
        if (children[i]->get_name() == name)
        {
            //cout<<"Найден объект "<<children[i]->get_name()<<endl;
            return children[i];
        }
    }
    for (size_t i = 0; i <children.size(); i++) //поиск рекурсивно в наследниках наследников
    {
        if ((children[i]->get_object_by_name(name))->get_name() ==
            name)
        {
            //cout<<"Найден объект "<<(children[i]->get_object_by_name(name))->get_name()<<endl;
            return (children[i]->get_object_by_name(name));
        }
    }
    return new cl_base(nullptr, "temp");
}

void cl_base::set_parent(cl_base* parent) {
    this->parent = parent;
}

cl_base *cl_base::get_parent() {
    return this->parent;
}




