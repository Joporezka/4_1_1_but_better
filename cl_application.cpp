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

        string temp_obj = "";
        if(parent_path == "/"){
            parent = this;
        }else if(parent_path[0]=='/' and parent_path[1]=='/'){
            for(int i=2;i<parent_path.length();i++)
                temp_obj+=parent_path[i];
            parent = this->get_object_by_name(temp_obj);
            if(parent == nullptr){
                cout<<"The head object "<<parent_path<<" is not found";
                return -1;
            }
        }else{ // /01/02/..../0n
            int cnt_objects=0;
            for(int i=1;i<parent_path.length();i++){
                if(parent_path[i]=='/'){
                    if(cnt_objects==0){
                        parent = this->get_object_by_name(temp_obj,1);
                    }else{
                        parent = parent->get_object_by_name(temp_obj,1);
                    }
                    cnt_objects++;
                    if(parent==nullptr){
                        cout<<"The head object "<<temp_obj<<" is not found";
                        return -1;
                    }
                    if(i!= parent_path.length()-1) temp_obj="";
                }else{
                    //get substr
                    temp_obj+=parent_path[i];
                }
            }
            if(cnt_objects==0)
                parent = this->get_object_by_name(temp_obj,1);
            else
                parent = parent->get_object_by_name(temp_obj,1);
            if(parent==nullptr){
                cout<<"The head object "<<temp_obj<<" is not found";
                return -1;
            }

        }
        cin >> child;
        cin >> cl_num;
        if(cl_num==2) child2* ch = new child2(parent,child);
        else if(cl_num==3) child3* ch = new child3(parent,child);
        else if(cl_num==4) child4* ch = new child4(parent,child);
        else if(cl_num==5) child5* ch = new child5(parent,child);
        else if(cl_num==6) child6* ch = new child6(parent,child);
    }
    return 0;
}



int cl_application::exec_app() {
    cout<<"Object tree\n";
    this->print_tree();

    while(true){
        string command, arg;
        cin>>command;
        if(command=="END") return 0;
        cout<<endl;
        cin>>arg;
        //ввели arg и command -> обработка

        //process comma
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
                if(arg[i] == '/' or i==arg.length()-1){
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

        //process output
        if(command == "SET"){
            if(obj_search!=nullptr){
                cout<<"Object is set: "<<obj_search->get_name();
                this->current = obj_search;
            }else{
                cout<<"Object is not found: "<<this->current->get_name()<<" "<<arg;
            }
        }else{//FIND
            if(obj_search!=nullptr){
                cout<<arg<<"     Object name: "<<obj_search->get_name();
            }else{
                cout<<arg<<"     Object is not found";
            }
        }

    }
    return 0;
}
