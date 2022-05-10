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

#define SIGNAL_D( signal_f ) ( TYPE_SIGNAL ) ( & signal_f )
#define HENDLER_D( hendler_f ) ( TYPE_HENDLER ) ( & hendler_f )

typedef void ( cl_base :: * TYPE_SIGNAL ) ( string & );
typedef void ( cl_base :: * TYPE_HENDLER ) ( string );

cl_application::cl_application(cl_base* b, string n):cl_base(b,n) { n_class = 1;}


int cl_application::bild_tree_objects() {
    string parent_path;
    string child;
    cl_base* parent=nullptr;

    int cl_num,readiness1;
    cin >> parent_path;
    //создание головного объекта
    this->set_name(parent_path);

    while (true)
    {
        parent = nullptr;
        cin >> parent_path;
        if(parent_path=="endtree") break;

        cl_base* parent = this->get_ptr_from_path(parent_path);

        if(parent==nullptr){
            cout<<"Object tree\n";
            this->print_tree();
            cout<<"\nThe head object "<<parent_path<<" is not found";
            return -1;
        }


        cin >> child;
        cin >> cl_num;
        if(cl_num==2) child2* ch = new child2(parent,child);
        else if(cl_num==3) child3* ch = new child3(parent,child);
        else if(cl_num==4) child4* ch = new child4(parent,child);
        else if(cl_num==5) child5* ch = new child5(parent,child);
        else if(cl_num==6) child6* ch = new child6(parent,child);
    }

    TYPE_SIGNAL sigs[] = {SIGNAL_D(cl_application::signal),SIGNAL_D(child2::signal),SIGNAL_D(child3::signal),
                          SIGNAL_D(child4::signal),SIGNAL_D(child5::signal),SIGNAL_D(child6::signal)};
    TYPE_HENDLER hans[] = {HENDLER_D(cl_application::handler), HENDLER_D(child2::handler),
                           HENDLER_D(child3::handler), HENDLER_D(child4::handler),
                           HENDLER_D(child5::handler), HENDLER_D(child6::handler)};

    while(true){
        string sender_path, reciever_path,message;
        cin>>sender_path;
        if(sender_path == "end_of_connections") break;

        cin>>reciever_path;

        cl_base* ob_sender = this -> get_ptr_from_path(sender_path);
        cl_base* ob_reciever = this -> get_ptr_from_path(reciever_path);

        ob_sender -> set_connect (sigs[ob_sender->n_class-1],ob_reciever, hans[ob_reciever->n_class-1]);
    }
    return 0;
}

void cl_application::signal(string& mes){
    if(readiness){
        cout<<endl<<"Signal from "<<get_abs_path();
    }
    mes+= " (class: 1)";
}
void cl_application::handler(string& mes){
    if(readiness){
        cout<<endl<<"Signal to "<<get_abs_path()<<" Text:"<<mes;
    }
}

int cl_application::exec_app() {

    TYPE_SIGNAL sigs[] = {SIGNAL_D(cl_application::signal),SIGNAL_D(child2::signal),SIGNAL_D(child3::signal),
                          SIGNAL_D(child4::signal),SIGNAL_D(child5::signal),SIGNAL_D(child6::signal)};
    TYPE_HENDLER hans[] = {HENDLER_D(cl_application::handler), HENDLER_D(child2::handler),
                           HENDLER_D(child3::handler), HENDLER_D(child4::handler),
                           HENDLER_D(child5::handler), HENDLER_D(child6::handler)};

    cout<<"Object tree\n";
    this->print_tree();

    string command,arg,message;

    cl_base* temp = this;
    cl_base* temp2 = this;

    int ready;

    while(true){

        cin>>command;
        if(command=="END") return 0;
        //cout<<endl;

        cin>>arg;


        if(command == "EMIT"){
            getline(cin,message);
            temp = this->get_ptr_from_path(arg);
            if(temp!=nullptr){
                temp->emit_signal(sigs[temp->n_class -1],message);
            }else{
                cout<<endl<<"Object "<<arg<<" not found";
            }

        }else if(command == "SET_CONNECT"){
            cin>>message;
            temp = this->get_ptr_from_path(arg);
            temp2 = this->get_ptr_from_path(message);
            if(temp==nullptr)
                cout<<endl<<"Object "<<arg<<" not found";
            else if(temp2==nullptr)
                cout<<endl<<"Handler object "<<message<<" not found";
            else{
                temp->set_connect(sigs[temp->n_class-1], temp2,hans[temp2->n_class-1]);
            }

        }else if(command == "DELETE_CONNECT"){
            cin>>message;
            temp = this->get_ptr_from_path(arg);
            temp2 = this->get_ptr_from_path(message);
            if(temp==nullptr)
                cout<<endl<<"Object "<<arg<<" not found";
            else if(temp2==nullptr)
                cout<<endl<<"Handler object "<<message<<" not found";
            else{
                temp->delete_connect(sigs[temp->n_class-1], temp2,hans[temp2->n_class-1]);
            }

        }else if(command == "SET_CONDITION"){
            cin>>ready;
            temp = this->get_ptr_from_path(arg);
            if(temp!=nullptr){
                temp->set_readiness(ready);
            }else{
                cout<<endl<<"Object "<<arg<<" not found";
            }
        }

    }
    return 0;
}
