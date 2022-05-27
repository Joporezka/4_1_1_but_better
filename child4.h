#ifndef INC_4_1_1_BUT_BETTER_CHILD4_H
#define INC_4_1_1_BUT_BETTER_CHILD4_H
#include "cl_base.h"


//локатор глубины
class child4: public cl_base {
public:
    int buffer_i=0,buffer_j=0,buffer_depth = -1;
    child4(cl_base*, string = "Default");
    void signal(string&);
    void handler(string&);
};

#endif