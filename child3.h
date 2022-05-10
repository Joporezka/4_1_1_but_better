#ifndef INC_4_1_1_BUT_BETTER_CHILD3_H
#define INC_4_1_1_BUT_BETTER_CHILD3_H
#include "cl_base.h"

class child3: public cl_base {
public:
    child3(cl_base*, string);
    void signal(string&);
    void handler(string&);
};

#endif