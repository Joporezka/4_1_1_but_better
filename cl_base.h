#ifndef INC_4_1_1_BUT_BETTER_CL_BASE_H
#define INC_4_1_1_BUT_BETTER_CL_BASE_H
#include <string>
#include <vector>
using namespace std;

class cl_base{
    string name;
    cl_base* parent;
public:
    cl_base* current = this; //указатель на текущий объект при работе с готовым деревом

    vector <cl_base*> children;
    cl_base(cl_base* parent, string name="application");
    void set_name(string name);
    string get_name();
    void set_parent(cl_base* parent);
    cl_base* get_parent();
    void print_tree(int depth=0);
    //void print_tree_ready(int depth=0);
    cl_base* get_object_by_name(string name,int condition=0);//izmeneno
    //void set_readiness(int data);
};

#endif