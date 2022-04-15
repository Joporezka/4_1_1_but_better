//
// Created by Алексей on 12.03.2022.
//

#ifndef INC_4_1_1_BUT_BETTER_CL_BASE_H
#define INC_4_1_1_BUT_BETTER_CL_BASE_H
#include <string>
#include <vector>
using namespace std;

class cl_base{
    string name;
    cl_base* parent;
public:
    vector <cl_base*> children;
    cl_base(cl_base* parent, string name="application");
    void set_name(string name);
    string get_name();
    void print_tree();
    void set_parent(cl_base* parent);
    cl_base* get_object_by_name(string name);
    cl_base* get_parent();
};

#endif //INC_4_1_1_BUT_BETTER_CL_BASE_H
