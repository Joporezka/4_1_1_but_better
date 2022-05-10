#ifndef INC_4_1_1_BUT_BETTER_CHILD2_H
#define INC_4_1_1_BUT_BETTER_CHILD2_H
#include "cl_base.h"

class child2: public cl_base {
public:
    child2(cl_base*, string);
    void signal(string&);
    void handler(string&);
};

#endif