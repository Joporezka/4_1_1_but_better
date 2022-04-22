#include "cl_base.h"
#include <string>
#include <iostream>
using namespace std;
cl_base::cl_base(cl_base *parent, string name) {
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
        if (children[i]->parent!=nullptr)
        {
            cl_base* temp = (children[i]->get_object_by_name(name));
            if(temp!=nullptr){
                if(temp->get_name() ==name)return temp;
            }
        }
    }
    return nullptr;
}

void cl_base::set_parent(cl_base* parent) {
    this->parent = parent;
}

cl_base *cl_base::get_parent() {
    return this->parent;
}

//создано

void cl_base::set_readiness(int data){
    if(data==0){
        for(int i=0;i<children.size();i++){
            children[i]->set_readiness(0);
        }
    }else{
        cl_base* ptr = this->parent;
        if(ptr==nullptr){
            this->readiness=data;
            return;
        }

        while(ptr!=nullptr){

            if(ptr->readiness==0){
                this->readiness=0;
                return;
            }
            ptr=ptr->parent;

        }
        this->readiness=data;
    }
}
//обновлено
void cl_base::print_tree(int depth)
{
    int i=0;
    if(depth==0){
        i=1;
        cout<< this->get_name();
    }
    for (; i < children.size(); i++)
    {
        cout<<endl;
        for(int j=0;j<=depth;j++) cout<<"    ";
        cout<<this->children[i]->get_name();
        if(children[i]->children.size()!=0) children[i]->print_tree(depth+1);
    }
}

void cl_base::print_tree_ready(int depth)
{
    int i=0;
    if(depth==0){
        i=1;
        cout<< this->get_name();
        if(this->readiness==0)
            cout<<" is not ready";
        else
            cout<<" is ready";
    }
    for (; i < children.size(); i++)
    {
        cout<<endl;
        for(int j=0;j<=depth;j++) cout<<"    ";
        cout<<this->children[i]->get_name();
        if(this->children[i]->readiness==0)
            cout<<" is not ready";
        else
            cout<<" is ready";
        if(children[i]->children.size()!=0) children[i]->print_tree_ready(depth+1);
    }
}
