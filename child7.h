#ifndef INC_4_1_1_BUT_BETTER_CHILD7_H
#define INC_4_1_1_BUT_BETTER_CHILD7_H
#include "cl_base.h"


//output
class child7: public cl_base {
public:
    child7(cl_base*, string = "Default");
    void signal(string&);
    void handler(string&);
};

#endif