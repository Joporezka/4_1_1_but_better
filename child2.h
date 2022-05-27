#ifndef INC_4_1_1_BUT_BETTER_CHILD2_H
#define INC_4_1_1_BUT_BETTER_CHILD2_H
#include "cl_base.h"


//акватория
class child2: public cl_base {
public:
    int** aquatory;
    child2(cl_base*, string = "Default");
    void construct_aquatory();
    void signal(string&);
    void handler(string&);
    ~child2();
};

#endif