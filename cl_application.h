//
// Created by Алексей on 12.03.2022.
//

#ifndef INC_4_1_1_BUT_BETTER_CL_APPLICATION_H
#define INC_4_1_1_BUT_BETTER_CL_APPLICATION_H
#include "cl_base.h"
#include <string>

class cl_application: public cl_base{
    using cl_base::cl_base;
public:
    //explicit cl_application(cl_base* parent);
    void bild_tree_objects();
    int exec_app();
};
#endif //INC_4_1_1_BUT_BETTER_CL_APPLICATION_H
