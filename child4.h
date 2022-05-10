#ifndef INC_4_1_1_BUT_BETTER_CHILD4_H
#define INC_4_1_1_BUT_BETTER_CHILD4_H
#include "cl_base.h"

class child4: public cl_base {
public:
    child4(cl_base*, string);
    void signal(string&);
    void handler(string&);
};

#endif