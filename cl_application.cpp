#include "cl_base.h"
#include "child2.h"
#include "child3.h"
#include "child4.h"
#include "child5.h"
#include "child6.h"
#include "child7.h"
#include "cl_application.h"
#include <iostream>
#include <string>
using namespace std;

#define SIGNAL_D( signal_f ) ( TYPE_SIGNAL ) ( & signal_f )
#define HENDLER_D( hendler_f ) ( TYPE_HENDLER ) ( & hendler_f )

typedef void ( cl_base :: * TYPE_SIGNAL ) ( string & );
typedef void ( cl_base :: * TYPE_HENDLER ) ( string );

cl_application::cl_application(cl_base* b, string n):cl_base(b,n) { n_class = 1;}


int cl_application::bild_tree_objects() {

    string arr_names[6] = {"aquatory","ship","locator","pult","inp","out"};
    child2* aquatory = new child2(this,"aquatory");
    child3* ship = new child3(this->get_object_by_name("aquatory"),"ship");
    child4* locator = new child4(this->get_object_by_name("ship"),"locator");
    child5* pult = new child5(this->get_object_by_name("ship"),"pult");
    child6* inp = new child6(this,"inp");
    child7* out = new child7(this,"out");



    TYPE_SIGNAL sigs[] = {SIGNAL_D(cl_application::signal),SIGNAL_D(child2::signal),SIGNAL_D(child3::signal),
                          SIGNAL_D(child4::signal),SIGNAL_D(child5::signal),SIGNAL_D(child6::signal),SIGNAL_D(child7::signal)};
    TYPE_HENDLER hans[] = {HENDLER_D(cl_application::handler), HENDLER_D(child2::handler),
                           HENDLER_D(child3::handler), HENDLER_D(child4::handler),
                           HENDLER_D(child5::handler), HENDLER_D(child6::handler), HENDLER_D(child7::handler)};

    /*for(int i=0;i<6;i++){ //sender
        for(int j=0;j<6;j++){ //reciever
            if(j!=i){
                cl_base* ob_sender = this->get_object_by_name(arr_names[i]);
                cl_base* ob_reciever = this->get_object_by_name(arr_names[j]);
                ob_sender -> set_connect(sigs[ob_sender->n_class-1],ob_reciever, hans[ob_reciever->n_class-1]);
            }
        }
    }*/
    cl_base* ob_sender = this;
    cl_base* ob_reciever = this->get_object_by_name("inp");


    ob_sender -> set_connect(sigs[ob_sender->n_class-1],ob_reciever, hans[ob_reciever->n_class-1]);
    ob_reciever -> set_connect(sigs[ob_reciever->n_class-1],ob_sender, hans[ob_sender->n_class-1]);

    int n,m,min_depth;
    string mes = "";
    this->emit_signal(sigs[this->n_class -1],mes);

    n = stoi(read_buffer);
    this->emit_signal(sigs[this->n_class -1],mes);
    m = stoi(read_buffer);
    this->emit_signal(sigs[this->n_class -1],mes);
    pult->min_depth = stoi(read_buffer);

    aquatory->n = n;
    aquatory->m = m;
    pult->n = n;
    pult->m=m;
    aquatory->construct_aquatory();
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            this->emit_signal(sigs[this->n_class -1],mes);
            aquatory->aquatory[i][j] = stoi(read_buffer);
            //cout<<aquatory->aquatory[i][j]<<" ";
        }
        //cout<<endl;
    }

    /*vector<string> sv = split_command("PRINT a b");
    for(int i=0;i<sv.size();i++){
        cout<<"\n"<<sv[i];
    }*/


    return 0;
}

void cl_application::signal(string& mes){
    if(readiness){
        //cout<<endl<<"Signal from "<<get_abs_path();
        read_buffer = mes;
    }
    //mes+= " (class: 1)";
}
void cl_application::handler(string& mes){
    if(readiness){
        //cout<<endl<<"Signal to "<<get_abs_path()<<" Text: "<<mes;
        vector<string> mes_com = split_command(mes);
        read_buffer = mes_com[1];
    }
}

int cl_application::exec_app() {




    TYPE_SIGNAL sigs[] = {SIGNAL_D(cl_application::signal),SIGNAL_D(child2::signal),SIGNAL_D(child3::signal),
                          SIGNAL_D(child4::signal),SIGNAL_D(child5::signal),SIGNAL_D(child6::signal),SIGNAL_D(child7::signal)};
    TYPE_HENDLER hans[] = {HENDLER_D(cl_application::handler), HENDLER_D(child2::handler),
                           HENDLER_D(child3::handler), HENDLER_D(child4::handler),
                           HENDLER_D(child5::handler), HENDLER_D(child6::handler),HENDLER_D(child7::handler)};

    //cout<<"Object tree\n";
    //this->print_tree();
    //cout<<endl;



    cl_base* aquatory = this->get_object_by_name("aquatory");
    cl_base* locator = this->get_object_by_name("locator");
    cl_base* ship = this->get_object_by_name("ship");
    cl_base* pult = this->get_object_by_name("pult");
    cl_base* inp = this->get_object_by_name("inp");
    cl_base* out = this->get_object_by_name("out");


    //this to inp - DONE
    this-> set_connect(sigs[this->n_class-1],pult,hans[pult->n_class-1]); // this to pult

    aquatory -> set_connect(sigs[aquatory->n_class-1],locator,hans[locator->n_class-1]); //aq to locator
    locator -> set_connect(sigs[locator->n_class-1],aquatory,hans[aquatory->n_class-1]); 	//locator to aq

    locator -> set_connect(sigs[locator->n_class-1],pult,hans[pult->n_class-1]); //locator to pult
    pult -> set_connect(sigs[pult->n_class-1],locator,hans[locator->n_class-1]); //pult to locator

    ship-> set_connect(sigs[ship->n_class-1],pult,hans[pult->n_class-1]); //ship to pult
    pult -> set_connect(sigs[pult->n_class-1],ship,hans[ship->n_class-1]); //pult to ship

    pult -> set_connect(sigs[pult->n_class-1],out,hans[out->n_class-1]); //pult to out


    //START
    string msg = "FIND_PATH";
    this->emit_signal(sigs[this->n_class-1],msg);

    string mes = "END";
    pult->emit_signal(sigs[pult->n_class-1],mes);

    //TEST OUTPUT
    /*cl_base* ob_sender_print = this->get_object_by_name("pult");
    cl_base* ob_reciever_print = this->get_object_by_name("out");
    ob_sender_print -> set_connect(sigs[ob_sender_print->n_class-1],ob_reciever_print, hans[ob_reciever_print->n_class-1]);

    string mes = "PRINT 0 0";
    ob_sender_print->emit_signal(sigs[ob_sender_print->n_class-1],mes);



    mes = "END";
    ob_sender_print->emit_signal(sigs[ob_sender_print->n_class-1],mes);*/




    return 0;
}
