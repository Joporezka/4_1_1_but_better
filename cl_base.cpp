#include "cl_base.h"
#include <string>
#include <iostream>
using namespace std;
#define SIGNAL_D( signal_f ) ( TYPE_SIGNAL ) ( & signal_f )
#define HENDLER_D( hendler_f ) ( TYPE_HENDLER ) ( & hendler_f )

typedef void ( cl_base :: * TYPE_SIGNAL ) ( string & );
typedef void ( cl_base :: * TYPE_HENDLER ) ( string );

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


cl_base* cl_base::get_object_by_name(string name, int condition) //получение объекта по имении в дереве иерархии
{
    for (size_t i = 0; i < children.size(); i++) //поиск в векторе прямых наследников
    {
        if (children[i]->get_name() == name)
        {
            //cout<<"Найден объект "<<children[i]->get_name()<<endl;
            return children[i];
        }
    }

    if(condition==1) return nullptr;

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


void cl_base::set_readiness(int data){
    if(data==0){
        this->readiness=0;
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

cl_base* cl_base::get_ptr_from_path(string arg){

    cl_base* obj_search = nullptr;
    string temp_name="";

    if(arg.length()==1 && arg[0] == '/'){ // /-root
        obj_search=this;
    }else if(arg.length()==1 && arg[0]=='.'){ // .-cur
        obj_search = this->current;
    }else if(arg[0]=='/' && arg[1]=='/'){ // // find from root

        for(int i=2;i<arg.length();i++)
            temp_name+=arg[i];
        obj_search = this->get_object_by_name(temp_name);

    }else if(arg.length()>1 && arg[0]=='/'){ // /j1/j2/j3..../jn - abs path from root

        int cnt_objects=0;
        for(int i=1;i<arg.length();i++){
            if(arg[i] == '/' || i==arg.length()-1){
                if(i==arg.length()-1) temp_name+=arg[i];
                if(cnt_objects==0){
                    obj_search = this->get_object_by_name(temp_name,1);
                }else{
                    obj_search = obj_search->get_object_by_name(temp_name,1);
                }
                cnt_objects++;
                temp_name = "";
                if(obj_search == nullptr){
                    break;
                }

            }else{
                temp_name+=arg[i];
            }
        }
    }else{ // j1/j2/j3..... - относительный путь от cur

        int cnt_objects = 0;
        for(int i=0;i<arg.length();i++){
            if(arg[i]=='/' or i==arg.length()-1){
                if(i==arg.length()-1) temp_name+=arg[i];
                if(cnt_objects==0){
                    obj_search = current->get_object_by_name(temp_name,1);
                }
                else{
                    obj_search = obj_search->get_object_by_name(temp_name,1);
                }
                cnt_objects++;
                temp_name = "";
                if(obj_search==nullptr){
                    //cout<<"broke"<<endl;
                    break;
                }
            }else
                temp_name+=arg[i];
        }

    }

    return obj_search;
}

string cl_base::get_abs_path(){
    string buf = "";
    cl_base* obj = this;
    while(obj->get_parent()!=nullptr){
        buf = '/' + obj->get_name() + buf;
        obj = obj->get_parent();
    }
    if(buf.length()==0) buf = "/";
    return buf;
}



void cl_base::set_connect (TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HENDLER p_ob_hendler){
    o_sh* p_value;


    for(int i=0; i< connects.size();i++){
        if(connects[i] -> p_signal == p_signal && connects[i] -> p_cl_base == p_object && connects[i] -> p_hendler == p_ob_hendler) return;
    }

    p_value = new o_sh;

    p_value -> p_cl_base = p_object;
    p_value -> p_signal = p_signal;
    p_value -> p_hendler = p_ob_hendler;

    connects.push_back(p_value);
}

void cl_base::delete_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HENDLER p_ob_hendler){
    for(int i=0;i<connects.size();i++){
        if(connects[i]->p_signal == p_signal && connects[i] -> p_cl_base == p_object && connects[i] -> p_hendler == p_ob_hendler){
            connects.erase(connects.begin()+i);
            return;
        }
    }
}

void cl_base::emit_signal(TYPE_SIGNAL p_signal, string& s_command){
    if(this->readiness!=0){
        (this->*(p_signal))(s_command);
        for(int i=0;i<connects.size();i++){
            if(connects[i]->p_signal == p_signal && connects[i] -> p_cl_base->readiness!=0){
                (connects[i]->p_cl_base->*(connects[i]->p_hendler))(s_command);
            }
        }
    }
}



/*
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
}*/
