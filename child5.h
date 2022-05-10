#ifndef INC_4_1_1_BUT_BETTER_CHILD5_H
#define INC_4_1_1_BUT_BETTER_CHILD5_H
#include "cl_base.h"

class child5: public cl_base {
public:
    child5(cl_base*, string);
    void signal(string&);
    void handler(string&);
};

#endif