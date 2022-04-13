#include "cl_application.h"
/*
o1
o1 o2
o1 o3
o2 o4
o5 o5
 */
int main()
{
    setlocale(LC_ALL, "ru");
    cl_application ob_cl_application(nullptr);
    ob_cl_application.bild_tree_objects();
    return ob_cl_application.exec_app();
}