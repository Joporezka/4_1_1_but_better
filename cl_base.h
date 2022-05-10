#ifndef INC_4_1_1_BUT_BETTER_CL_BASE_H
#define INC_4_1_1_BUT_BETTER_CL_BASE_H
#include <string>
#include <vector>

#define SIGNAL_D( signal_f ) ( TYPE_SIGNAL ) ( & signal_f )
#define HENDLER_D( hendler_f ) ( TYPE_HENDLER ) ( & hendler_f )
#define DEBUG_MOD 1


using namespace std;

class cl_base{
    string name;
    cl_base* parent;

public:
    int readiness=DEBUG_MOD;


    typedef void ( cl_base :: * TYPE_SIGNAL ) ( string & );
    typedef void ( cl_base :: * TYPE_HENDLER ) ( string );

    cl_base* current = this;

    vector <cl_base*> children;
    cl_base(cl_base* parent, string name="application");
    void set_name(string name);
    string get_name();
    void set_parent(cl_base* parent);
    cl_base* get_parent();
    void print_tree(int depth=0);
    //void print_tree_ready(int depth=0);
    cl_base* get_object_by_name(string name,int condition=0);
    cl_base* get_ptr_from_path(string arg);
    void set_readiness(int data);



    // ========== signal ==========

    int n_class=1;

    struct o_sh{
        TYPE_SIGNAL p_signal;
        cl_base* p_cl_base;
        TYPE_HENDLER p_hendler;
    };

    vector <o_sh *> connects;

    string get_abs_path();

    void set_connect (TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HENDLER p_ob_hendler);
    void delete_connect (TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HENDLER p_ob_hendler);
    void emit_signal (TYPE_SIGNAL p_signal, string& s_command);

    /*void signal(string&);
    void handler(string&);*/

    // ========== /signal ==========
};

#endif