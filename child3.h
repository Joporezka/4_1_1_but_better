#ifndef INC_4_1_1_BUT_BETTER_CHILD3_H
#define INC_4_1_1_BUT_BETTER_CHILD3_H
#include "cl_base.h"

//корабль
class child3: public cl_base {
    string direction = "E";
    int i=0;
    int j=0;
public:
    child3(cl_base*, string = "Default");
    void signal(string&);
    void handler(string&);
};

#endif