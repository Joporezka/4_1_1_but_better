#include "child5.h"
#include <iostream>
#include <string>
using namespace std;

//пульт управления
child5::child5(cl_base* b, string n):cl_base(b,n) { n_class = 5;}



void child5::signal(string& mes){
    if(readiness){
        //cout<<endl<<"Signal from child5";
    }
}
void child5::handler(string& mes){
    if(readiness){
        vector<string> command = split_command(mes);
        if(command.size()>0 && command[0] == "GET_POSITION"){ //RX
            posi = stoi(command[1]);
            posj = stoi(command[2]);
            direction = command[3];
        }else if(command.size()>0 && command[0] == "GET_DEPTH"){ //RX
            cur_depth = stoi(command[3]);
        }else if(command.size()>0 && command[0] == "FIND_PATH"){//TX
            //main logic

            //find enter
            int max_depth=0;
            int max_index=0;
            while(true){
                position cur = get_pos();

                int now_depth = get_depth_by_pos(cur.x+1,cur.y);
                if(now_depth>max_depth){
                    max_depth = now_depth;
                    max_index = cur.y;
                }
                if(cur.y!=m-1){
                    int next_depth = get_depth_by_pos(cur.x,cur.y+1);
                    if(next_depth>=min_depth) move_by_pos(cur.x,cur.y+1);
                }else{
                    //cout<<"MAX DEPTH: "<<max_depth;
                    break;
                }
            }
            position cur = get_pos();
            while(cur.y!=max_index){
                move_by_pos(cur.x,cur.y-1);
                cur = get_pos();
            }
            print_pos(cur.x,cur.y);
            move_by_pos(cur.x+1,cur.y);
            cur = get_pos();
            print_pos(cur.x,cur.y);

            //enter found

            //search bottom
            while(true){
                position cur = get_pos();
                int max_depth=min_depth;
                int gotox=cur.x+1,gotoy=cur.y;
                if(cur.x+1<n){
                    if(cur.y+1<m){
                        int depthSE = get_depth_by_pos(cur.x+1,cur.y+1);
                        int depthE = get_depth_by_pos(cur.x,cur.y+1);
                        if(depthE>max_depth){
                            max_depth=depthE;
                            gotox = cur.x;
                            gotoy = cur.y+1;
                        }
                        if(depthSE>max_depth){
                            max_depth=depthSE;
                            gotox = cur.x+1;
                            gotoy = cur.y+1;
                        }
                    }
                    if(cur.y-1>=0){
                        int depthSW = get_depth_by_pos(cur.x+1,cur.y-1);
                        int depthW = get_depth_by_pos(cur.x,cur.y-1);
                        if(depthW>max_depth){
                            max_depth=depthW;
                            gotox = cur.x;
                            gotoy = cur.y-1;
                        }
                        if(depthSW>max_depth){
                            max_depth=depthSW;
                            gotox = cur.x+1;
                            gotoy = cur.y-1;
                        }
                    }
                    int depthS = get_depth_by_pos(cur.x+1,cur.y);
                    if(depthS>=max_depth){
                        max_depth=depthS;
                        gotox = cur.x+1;
                        gotoy = cur.y;
                    }
                    move_by_pos(gotox,gotoy);
                    cur=get_pos();
                    print_pos(cur.x,cur.y);
                }else{
                    position cur=get_pos();
                    //print_pos(cur.x,cur.y);
                    break;
                }

            }
        }
    }
}

int child5::get_depth_by_pos(int x,int y){
    string msg = "GET_DEPTH "+to_string(x)+" "+to_string(y);
    this->emit_signal(SIGNAL_D(child5::signal),msg);
    return cur_depth;
}
child5::position child5::get_pos(){
    position pos;
    string msg = "GET_POSITION";
    this->emit_signal(SIGNAL_D(child5::signal),msg);
    pos.x = posi;
    pos.y = posj;
    pos.dir = direction;
    return pos;
}
void child5::move_by_pos(int x,int y){
    string msg = "SET_POSITION "+to_string(x)+" "+to_string(y);
    this->emit_signal(SIGNAL_D(child5::signal),msg);
}

void child5::print_pos(int x,int y){
    string msg = "PRINT "+to_string(x+1)+" "+to_string(y+1);
    this->emit_signal(SIGNAL_D(child5::signal),msg);
}