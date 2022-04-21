//
// Created by Алексей on 12.03.2022.
//
#include "cl_base.h"
#include <string>
#include <iostream>
using namespace std;
cl_base::cl_base(cl_base *parent, string name){
    this->parent = parent;
    this->name = name;
    if(parent!= nullptr) parent->children.push_back(this);
    else this->children.push_back(this);
}

void cl_base::set_name(string name) {
    this->name = name;
}

string cl_base::get_name() {
    return this->name;
}

/*
app_root
app_root object_01 3
app_root object_02 2
object_02 object_04 3
object_02 object_05 5
object_01 object_07 2
endtree
app_root 1
object_07 3
object_01 1
object_02 -2
object_04 1
 */
void cl_base::print_tree(int depth)
{
    int i;
    if(depth==0){
        i=1;
        cout<< this->get_name();
    }
    for(i<this->children.size(); i++)
    {
        cout<<endl;
        for(int j=0; j<=depth; j++) cout<<"    ";
        cout<<this->children[i]->get_name();
        if(children[i]->children.size()!=0)
            children[i]->print_tree(depth+1);
    }
}

void cl_base::print_tree_ready(int depth)
{
    int i=0;
    if(depth==0){
        i=1;
        cout<< this->get_name()<<" "<<this->readiness;
    }
    for (; i < children.size(); i++)
    {
        cout<<endl;
        for(int j=0;j<=depth;j++) cout<<"    ";
        cout<<this->children[i]->get_name()<<" "<<this->children[i]->readiness;
        if(!children[i]->children.empty())
            children[i]->print_tree_ready(depth+1);
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
void cl_base::set_readiness(int data){
    cl_base* ptr= this->parent;
    if(ptr == nullptr) this->readiness=data;
    while(ptr!=nullptr){
        if(ptr->readiness==0){
            this->readiness=0;
            return;
        }
        ptr=ptr->parent;
    }
    this->readiness=data;
}




