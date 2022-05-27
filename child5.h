#ifndef INC_4_1_1_BUT_BETTER_CHILD5_H
#define INC_4_1_1_BUT_BETTER_CHILD5_H
#include "cl_base.h"


//пульт управления
class child5: public cl_base {

public:
    struct position{
        int x;
        int y;
        string dir;
    };
    int posi = 0;
    int posj = 0;
    int n;
    int m;
    string direction = "E";
    int cur_depth = 0;
    int min_depth =0;

    child5(cl_base*, string = "Default");
    void decidion();
    void signal(string&);
    void handler(string&);
    int get_depth_by_pos(int x,int y);
    position get_pos();
    void move_by_pos(int x,int y);
    void print_pos(int x,int y);

};

#endif