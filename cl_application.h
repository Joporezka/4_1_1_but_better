#ifndef INC_4_1_1_BUT_BETTER_CL_APPLICATION_H
#define INC_4_1_1_BUT_BETTER_CL_APPLICATION_H

#define SIGNAL_D( signal_f ) ( TYPE_SIGNAL ) ( & signal_f )
#define HENDLER_D( hendler_f ) ( TYPE_HENDLER ) ( & hendler_f )

#include "cl_base.h"
#include <string>

class cl_application: public cl_base{
public:
    cl_application(cl_base*, string = "Default");

    int n_class=1;
    string read_buffer;

    int bild_tree_objects();
    int exec_app();

    void signal(string&);
    void handler(string&);

};
#endif 