#ifndef INC_4_1_1_BUT_BETTER_CL_APPLICATION_H
#define INC_4_1_1_BUT_BETTER_CL_APPLICATION_H
#include "cl_base.h"
#include <string>

class cl_application: public cl_base{
    using cl_base::cl_base;
public:
    void bild_tree_objects();
    int exec_app();
};
#endif 