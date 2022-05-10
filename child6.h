#ifndef INC_4_1_1_BUT_BETTER_CHILD6_H
#define INC_4_1_1_BUT_BETTER_CHILD6_H
#include "cl_base.h"

class child6: public cl_base {
public:
    child6(cl_base*, string);
    void signal(string&);
    void handler(string&);
};

#endif