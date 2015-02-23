//
//  system.cpp
//  trafficSim
//
//  Created by Jinqi Fang on 2/12/15.
//  Copyright (c) 2015 Jinqi Fang. All rights reserved.
//

#include "system.h"

//global variables defined else where
bool compare (const struct Event lhs, const struct Event rhs);
extern std::priority_queue<struct Event, std::vector<Event>, decltype(&compare)> FEL;
extern double _current_time;

////////////////////////////////////////////////////////////////////////////////
//
// Signal configuration
//
////////////////////////////////////////////////////////////////////////////////

//lights with 80s cycle length
double phase_length1[] = {10,30,10,30};
TrafficLight lt1(1, 0, 4, phase_length1);
double phase_length2[] = {50,30};
TrafficLight lt2(2, 0, 2, phase_length2);
double phase_length3[] = {50,30};
TrafficLight lt3(3, 0, 2, phase_length3);
double phase_length4[] = {0,0,0,0};
TrafficLight lt4(4, 0, 0, phase_length4);//stop sign
double phase_length5[] = {10,30,10,30};
TrafficLight lt5(5, 0, 4, phase_length5);

//offsets of signals for synchronization
double *off_set = new double[4];



////////////////////////////////////////////////////////////////////////////////
//
//  Roadway topology and geometric features
//
////////////////////////////////////////////////////////////////////////////////

//entrances
Link lk1011(1011, 0, &lt1, 29.06, 0, 135, true, false);
Link lk1012(1012, 1, &lt1, 29.06, 0, 135, true, false);
Link lk1013(1013, 1, &lt1, 29.06, 0, 135, true, false);
Link lk1021(1021, 2, &lt1, 29.06, 0, 135, true, false);
Link lk1022(1022, 3, &lt1, 29.06, 0, 135, true, false);
Link lk1023(1023, 3, &lt1, 29.06, 0, 135, true, false);
Link lk1031(1031, 1, &lt2, 37.38, 0, 135, true, false);
Link lk1061(1061, 1, &lt3, 37.38, 0, 135, true, false);
Link lk1121(1021, -1, &lt4, 37.38, 0, 135, true, false); //stop sign
Link lk1131(1131, 2, &lt5, 37.38, 0, 135, true, false);
Link lk1132(1132, 3, &lt5, 37.38, 0, 135, true, false);
Link lk1133(1133, 3, &lt5, 37.38, 0, 135, true, false);
Link lk1141(1141, 0, &lt5, 30.25, 0, 135, true, false);
Link lk1142(1142, 1, &lt5, 30.25, 0, 135, true, false);
Link lk1143(1143, 1, &lt5, 30.25, 0, 135, true, false);
Link lk1151(1151, 2, &lt5, 30.25, 0, 135, true, false);
Link lk1152(1152, 3, &lt5, 30.25, 0, 135, true, false);
Link lk1211(1211, 1, &lt3, 28.31, 0, 135, true, false);
Link lk1212(1212, 1, &lt3, 28.31, 0, 135, true, false);
Link lk1221(1221, 1, &lt2, 34.44, 0, 135, true, false);
Link lk1222(1222, 1, &lt2, 34.44, 0, 135, true, false);
Link lk1231(1231, 2, &lt1, 34.44, 0, 135, true, false);
Link lk1232(1232, 3, &lt1, 34.44, 0, 135, true, false);
Link lk1233(1233, 3, &lt1, 34.44, 0, 135, true, false);
Link lk1234(1234, 3, &lt1, 34.44, 0, 135, true, false);

//exits
Link lk2011(2011, -1, NULL, 34.44, 0, 135, false, true);
Link lk2012(2012, -1, NULL, 34.44, 0, 135, false, true);
Link lk2021(2021, -1, NULL, 29.06, 0, 135, false, true);
Link lk2022(2022, -1, NULL, 29.06, 0, 135, false, true);
Link lk2023(2023, -1, NULL, 29.06, 0, 135, false, true);
Link lk2031(2031, -1, NULL, 31.84, 0, 135, false, true);
Link lk2061(2061, -1, NULL, 37.38, 0, 135, false, true);
Link lk2121(2121, -1, NULL, 37.38, 0, 135, false, true);
Link lk2131(2131, -1, NULL, 37.38, 0, 135, false, true);
Link lk2132(2132, -1, NULL, 37.38, 0, 135, false, true);
Link lk2141(2141, -1, NULL, 37.38, 0, 135, false, true);
Link lk2142(2142, -1, NULL, 37.38, 0, 135, false, true);
Link lk2151(2151, -1, NULL, 30.25, 0, 135, false, true);
Link lk2152(2152, -1, NULL, 30.25, 0, 135, false, true);
Link lk2211(2211, -1, NULL, 30.25, 0, 135, false, true);
Link lk2212(2212, -1, NULL, 30.25, 0, 135, false, true);
Link lk2221(2221, -1, NULL, 28.31, 0, 135, false, true);
Link lk2231(2231, -1, NULL, 34.44, 0, 135, false, true);
Link lk2232(2232, -1, NULL, 34.44, 0, 135, false, true);

//connections
Link lk3012(3012, 0, &lt2, 29.06, 0, 440, false, false);
Link lk3013(3013, 0, &lt2, 29.06, 0, 440, false, false);
Link lk3021(3021, 0, &lt1, 34.44, 0, 440, false, false);
Link lk3022(3022, 1, &lt1, 34.44, 0, 440, false, false);
Link lk3023(3023, 1, &lt1, 34.44, 0, 440, false, false);
Link lk4011(4011, 0, &lt3, 31.84, 0, 415, false, false);
Link lk4012(4012, 0, &lt3, 31.84, 0, 415, false, false);
Link lk4013(4013, 0, &lt3, 31.84, 0, 415, false, false);
Link lk4021(4021, 0, &lt2, 28.31, 0, 415, false, false);
Link lk4022(4022, 0, &lt2, 28.31, 0, 415, false, false);
Link lk4023(4023, 0, &lt2, 28.31, 0, 415, false, false);
Link lk5011(5011, -1, &lt4, 37.38, 0, 350, false, false);
Link lk5012(5012, -1, &lt4, 37.38, 0, 350, false, false);
Link lk5013(5013, -1, &lt4, 37.38, 0, 350, false, false);
Link lk5021(5021, 0, &lt3, 30.25, 0, 350, false, false);
Link lk5022(5022, 0, &lt3, 30.25, 0, 350, false, false);
Link lk5023(5023, 0, &lt3, 30.25, 0, 345, false, false);
Link lk6011(6011, 0, &lt5, 37.38, 0, 345, false, false);
Link lk6012(6012, 1, &lt5, 37.38, 0, 345, false, false);
Link lk6013(6013, 1, &lt5, 37.38, 0, 345, false, false);
Link lk6022(6022, -1, &lt4, 30.25, 0, 345, false, false);
Link lk6023(6023, -1, &lt4, 30.25, 0, 345, false, false);


/**
 *  associates the lights to the links it controls
 */
void Initialize_light(){
    //south
    lt1.exit_link_id.push_back(1011);
    lt1.exit_link_id.push_back(1012);
    lt1.exit_link_id.push_back(1013);
    //east
    lt1.exit_link_id.push_back(1021);
    lt1.exit_link_id.push_back(1022);
    lt1.exit_link_id.push_back(1023);
    //west
    lt1.exit_link_id.push_back(1231);
    lt1.exit_link_id.push_back(1232);
    lt1.exit_link_id.push_back(1233);
    lt1.exit_link_id.push_back(1234);
    //north
    lt1.exit_link_id.push_back(3021);
    lt1.exit_link_id.push_back(3022);
    lt1.exit_link_id.push_back(3023);
    
    //south
    lt2.exit_link_id.push_back(3012);
    lt2.exit_link_id.push_back(3013);
    //east
    lt2.exit_link_id.push_back(1031);
    //west
    lt2.exit_link_id.push_back(1221);
    lt2.exit_link_id.push_back(1222);
    //north
    lt2.exit_link_id.push_back(4021);
    lt2.exit_link_id.push_back(4022);
    lt2.exit_link_id.push_back(4023);
    
    //south
    lt3.exit_link_id.push_back(4011);
    lt3.exit_link_id.push_back(4012);
    lt3.exit_link_id.push_back(4013);
    //east
    lt3.exit_link_id.push_back(1061);
    //west
    lt3.exit_link_id.push_back(1211);
    lt3.exit_link_id.push_back(1212);
    //north
    lt3.exit_link_id.push_back(5021);
    lt3.exit_link_id.push_back(5022);
    lt3.exit_link_id.push_back(5023);
    
    //south
    lt4.exit_link_id.push_back(5011);
    lt4.exit_link_id.push_back(5012);
    lt4.exit_link_id.push_back(5013);
    //east
    //west
    lt4.exit_link_id.push_back(1121);
    //north
    lt4.exit_link_id.push_back(6022);
    lt4.exit_link_id.push_back(6023);
    
    //south
    lt5.exit_link_id.push_back(6011);
    lt5.exit_link_id.push_back(6012);
    lt5.exit_link_id.push_back(6013);
    //east
    lt5.exit_link_id.push_back(1131);
    lt5.exit_link_id.push_back(1132);
    lt5.exit_link_id.push_back(1133);
    //west
    lt5.exit_link_id.push_back(1151);
    lt5.exit_link_id.push_back(1152);
    //north
    lt5.exit_link_id.push_back(1141);
    lt5.exit_link_id.push_back(1142);
    lt5.exit_link_id.push_back(1143);
}


////////////////////////////////////////////////////////////////////////////////
//
//road maps that serves each orign and destination pair
//
////////////////////////////////////////////////////////////////////////////////

std::vector<int> od_map[11][11];
void initialize_od_map(){
    od_map[0][0]={1011,2012};
    od_map[0][1]={1013,2023};
    od_map[0][3]={101,301,4013,2061};
    od_map[0][4]={101,301,401,5013,2121};
    od_map[0][5]={101,301,401,501,6013,2132};
    od_map[0][6]={101,301,401,501,601,2141};
    od_map[0][7]={101,301,401,501,6011,2151};
    od_map[0][8]={101,301,4011,2211};
    od_map[0][10]={1011,2231};
    
    od_map[1][0] = {1021,2011};
    od_map[1][2] = {1023,3013,2031};
    od_map[1][6] = {1023,301,401,501,601,2141};
    od_map[1][7] = {1023,301,401,501,6011,2151};
    od_map[1][8] = {1023,301,4011,2211};
    od_map[1][10] = {1022,2231};
    
    od_map[2][6] = {1031,401,501,601,2141};
    od_map[2][9] = {1031,2221};
    od_map[2][10] = {1031,3022,2232};
    
    od_map[3][6] = {1061,501,601,2141};
    od_map[3][7] = {1061,501,6011,2151};
    od_map[3][8] = {1061,2211};
    
    od_map[4][0] = {1121,502,402,302,2011};
    od_map[4][6] = {1121,601,2141};
    od_map[4][7] = {1121,6011,2151};
    od_map[4][8] = {1121,5023,2212};
    
    od_map[5][0] = {1131,602,502,402,302,2011};
    od_map[5][6] = {1133,2142};
    od_map[5][7] = {1132,2151};
    
    od_map[6][0] = {114,602,502,402,302,2011};
    od_map[6][1] = {1142,602,502,402,3021,2021};
    od_map[6][2] = {1142,602,502,4021,2031};
    od_map[6][3] = {1142,602,5021,2061};
    od_map[6][4] = {1142,6022,2121};
    od_map[6][5] = {1141,2131};
    od_map[6][6] = {1141,2142};
    od_map[6][7] = {1142,2152};
    od_map[6][8] = {1143,602,5022,2212};
    od_map[6][9] = {1143,602,502,4023,2221};
    od_map[6][10] = {1143,602,502,402,3022,2232};
    
    od_map[7][0] = {1152,602,502,402,302,2011};
    od_map[7][1] = {1152,602,502,402,3021,2021};
    od_map[7][2] = {1152,602,502,4021,2031};
    od_map[7][3] = {1152,602,5021,2061};
    od_map[7][4] = {1152,6022,2121};
    od_map[7][5] = {1151,2131};
    od_map[7][6] = {1151,2141};
    od_map[7][8] = {1152,602,5023,2212};
    od_map[7][9] = {1152,602,502,4023,2221};
    od_map[7][10] = {1152,602,502,402,3023,2232};
    
    od_map[8][0] = {1212,402,302,2011};
    od_map[8][1] = {1212,402,3021,2021};
    od_map[8][2] = {1212,4021,2031};
    od_map[8][6] = {1211,501,601,2141};
    od_map[8][7] = {1211,501,6011,2151};
    od_map[8][10] = {1212,402,3023,2232};
    
    od_map[9][0] = {1222,3022,2012};
    od_map[9][1] = {1222,3021,2021};
    od_map[9][2] = {1221,2031};
    od_map[9][5] = {1221,401,501,6013,2132};
    od_map[9][6] = {1221,401,501,601,2141};
    od_map[9][7] = {1221,401,501,6011,2151};
    od_map[9][10] = {1222,3023,2232};
    od_map[10][0] = {1234,2012};
}

//simulation params
int veh_rank;
int num_run;
double lamda_list[11];


//stats
int total_num_veh;
double total_trvl_time;


void initialize_lamda(){
    lamda_list[0] = 6.2;
    lamda_list[1] = 7.4;
    lamda_list[2] = 100;
    lamda_list[3] = 47.4;
    lamda_list[4] = 69.2;
    lamda_list[5] = 13.0;
    lamda_list[6] = 3.0;
    lamda_list[7] = 4.5;
    lamda_list[8] = 16;
    lamda_list[9] = 3.7;
    lamda_list[10] = 900;
}


std::unordered_map<int, Vehicle> veh_set;
std::unordered_map<int, Link*> link_set;

void initialize_link_set(){
    link_set[1011]=	&lk1011;
    link_set[1012]=	&lk1012;
    link_set[1013]=	&lk1013;
    link_set[1021]=	&lk1021;
    link_set[1022]=	&lk1022;
    link_set[1023]=	&lk1023;
    link_set[1031]=	&lk1031;
    link_set[1061]=	&lk1061;
    link_set[1121]=	&lk1121;
    link_set[1131]=	&lk1131;
    link_set[1132]=	&lk1132;
    link_set[1133]=	&lk1133;
    link_set[1141]=	&lk1141;
    link_set[1142]= &lk1142;
    link_set[1143]= &lk1143;
    link_set[1151]= &lk1151;
    link_set[1152]= &lk1152;
    link_set[1211]= &lk1211;
    link_set[1212]= &lk1212;
    link_set[1221]= &lk1221;
    link_set[1222]= &lk1222;
    link_set[1231]= &lk1231;
    link_set[1232]= &lk1232;
    link_set[1233]= &lk1233;
    link_set[1234]= &lk1234;
    link_set[2011]= &lk2011;
    link_set[2012]= &lk2012;
    link_set[2021]= &lk2021;
    link_set[2022]= &lk2022;
    link_set[2023]= &lk2023;
    link_set[2031]= &lk2031;
    link_set[2061]= &lk2061;
    link_set[2121]= &lk2121;
    link_set[2131]= &lk2131;
    link_set[2132]= &lk2132;
    link_set[2141]= &lk2141;
    link_set[2142]= &lk2142;
    link_set[2151]= &lk2151;
    link_set[2152]= &lk2152;
    link_set[2211]= &lk2211;
    link_set[2212]= &lk2212;
    link_set[2221]= &lk2221;
    link_set[2231]= &lk2231;
    link_set[2232]= &lk2232;
    link_set[3012]= &lk3012;
    link_set[3013]= &lk3013;
    link_set[3021]= &lk3021;
    link_set[3022]= &lk3022;
    link_set[3023]= &lk3023;
    link_set[4011]= &lk4011;
    link_set[4012]= &lk4012;
    link_set[4013]= &lk4013;
    link_set[4021]= &lk4021;
    link_set[4022]= &lk4022;
    link_set[4023]= &lk4023;
    link_set[5011]= &lk5011;
    link_set[5012]= &lk5012;
    link_set[5013]= &lk5013;
    link_set[5021]= &lk5021;
    link_set[5022]= &lk5022;
    link_set[5023]= &lk5023;
    link_set[6011]= &lk6011;
    link_set[6012]= &lk6012;
    link_set[6013]= &lk6013;
    link_set[6022]= &lk6022;
    link_set[6023]= &lk6023;
    for (auto it = link_set.begin(); it!= link_set.end(); ++it) {
        it->second->vehicle_q = std::queue<int>();
        it->second->vehicle_count = 0;
    }
}

void Initialize(){
    
    _current_time = 0;
    veh_rank = 0;
    total_num_veh = 0;
    total_trvl_time = 0;
    
    //clear FEL
    while (!FEL.empty()) {
        FEL.pop();
    }
    
    veh_set.clear();
    link_set.clear();
    Initialize_light();
    initialize_od_map();
    initialize_lamda();
    initialize_link_set();
}




/////////////////helper functions/////////

//get the route for a vehicle based on the vehicle origin and destination
std::vector<int> GetRoute(int ori, int des, const std::vector<int> od_pair[11][11])
{
    return od_pair[ori][des];
}


bool isLinkClear(double &q_len, double t, Link *link){
    auto veh_q = link->vehicle_q;
    double acc_t = 0;
    q_len = 0;
    while(!veh_q.empty()){
        int veh_id = veh_q.front();
        acc_t = acc_t + veh_set[veh_id].clear_time;
        veh_q.pop();
        if (acc_t>t)
        {
            while (!veh_q.empty()) {
                veh_id = veh_q.front();
                q_len += veh_set[veh_id].length;
                veh_q.pop();
            }
            return false;
        }
    }
    return true;
}

double get_queue_len(Link *link){
    auto veh_q = link->vehicle_q;
    double q_len = 0;
    while(!veh_q.empty()){
        int veh_id = veh_q.front();
        q_len += veh_set[veh_id].length;
        veh_q.pop();
    }
    return q_len;
}

void gen_veh_len_clt(double &len, double &clt){
    if (uniRand()<0.98) {
        len = 18;
        clt = 2.0;
    }else{
        len = 25;
        clt = 3.0;
    }
}

//check if a vehicle would stop afer entering a section
bool CheckStop(Link *current_link, double &stoptime){
    
    TrafficLight *current_light = current_link->light;
    
    /////////////////stop sign//////////////
    //through traffic at the T intersection with stop sign
    if (current_light->light_id==4) {
        if (current_link->link_id>3000) {
            return false;
        }else{///non through traffic
            double q_len = get_queue_len(current_link);
            stoptime = (current_link->get_length()-q_len)/current_link->speed;
            return true;
        }
    }
    
    
    ////////normal traffic lights////////////
    
    //get current time
    double t = current_time();
    //get the exit phase of the current link
    int exit_phase = current_link->exit_phase;
    
    if (current_light->light_id==1||current_light->light_id==5) {
        
        int k = current_light->light_id>4?4:current_light->light_id;
        
        if (exit_phase==2){
            t = t - off_set[k-1]-current_light->phase_len[1]
            + current_light->cycle_len();
        }
        else if (exit_phase==3){
            t = t - off_set[k-1]-current_light->phase_len[1]
            - current_light->phase_len[2]+current_light->cycle_len();
        }
        else if (exit_phase==0){//if next movement
            t = t - off_set[k-1]-current_light->phase_len[1]
            - current_light->phase_len[2]-current_light->phase_len[3]
            + 2*current_light->cycle_len();
        }else{
            t = t-off_set[k-1]+current_light->cycle_len();
        }
    }else{
        int k = current_light->light_id;
        if (exit_phase == 1) {
            t = t-off_set[k-1]-current_light->phase_len[0]
            +current_light->cycle_len();
        }else{
            t = t-off_set[k-1]+current_light->cycle_len();
        }
    }
    
    
    //all traffic
    if (current_light->cur_phase==exit_phase){
        
        double left_green = current_light->phase_len[exit_phase] - fmod(t, current_light->cycle_len());
        double q_len = 0;
        
        if (isLinkClear(q_len, left_green, current_link)){
            if (current_link->get_travel_time()>left_green){
                stoptime = current_link->get_travel_time();
                return true;
            }else{
                return false;
            }
            
        }else{
            stoptime = (current_link->get_length()-q_len)/current_link->speed;
            return true;
        }
        
    }else{
        double left_red = current_light->cycle_len() - fmod(t, current_light->cycle_len());
        double q_len = get_queue_len(current_link);
        
        if (left_red*current_link->speed>current_link->get_length()-q_len) {
            
            double travel_dist = current_link->get_length()-q_len;
            double vlty = current_link->speed;
            stoptime = travel_dist/vlty;
            
            return true;
        }else{
            double rem_q =0;
            if (isLinkClear(rem_q, current_light->phase_len[exit_phase], current_link)) {
                return false;
            }else{
                stoptime = (current_link->get_length()-rem_q)/current_link->speed;
                return true;
            }
        }
    }
}


int GetDestination(int Origin)
{
    ///randomly get destination
    double temp = ((double) rand ()) / (((double) RAND_MAX)+1.0);
    
    if (Origin==0){
        if (temp<=0.1)return 0;
        else if(temp<=0.19) return 1;
        else if(temp<=0.2) return 3;
        else if (temp<=0.21) return 4;
        else if (temp<=0.22) return 5;
        else if (temp<=0.73) return 6;
        else if (temp<=0.79) return 7;
        else if (temp<=0.82) return 8;
        else return 10;
    }else if (Origin==1){
        if (temp<=0.07)return 0;
        else if(temp<=0.22) return 6;
        else if (temp<=0.25) return 7;
        else if (temp<=0.26) return 8;
        else return 10;
    }else if (Origin==2){
        if (temp<=0.11)return 6;
        else if (temp<=0.89) return 9;
        else return 10;
    }else if (Origin==3){
        if (temp<=0.21)return 6;
        else if (temp<=0.37) return 7;
        else return 8;
    }else if (Origin==4){
        if (temp<=0.08)return 0;
        else if(temp<=77) return 6;
        else if (temp<=0.92) return 7;
        else return 8;
    }else if (Origin==5){
        if (temp<=0.01)return 0;
        else if(temp<=0.46) return 6;
        else if(temp<=0.2) return 3;
        else return 7;
    }else if (Origin==6){
        if (temp<=0.25)return 0;
        else if(temp<=0.3) return 1;
        else if(temp<=0.32) return 3;
        else if (temp<=0.41) return 4;
        else if (temp<=0.65) return 5;
        else if (temp<=0.68) return 6;
        else if (temp<=0.94) return 7;
        else if (temp<=0.95) return 8;
        else if (temp<=0.96) return 9;
        else return 10;
    }else if (Origin==7){
        if (temp<=0.14)return 0;
        else if(temp<=0.16) return 1;
        else if(temp<=0.17) return 2;
        else if (temp<=0.18) return 3;
        else if (temp<=0.21) return 4;
        else if (temp<=0.69) return 5;
        else if (temp<=0.93) return 6;
        else if (temp<=0.94) return 8;
        else if (temp<=0.96) return 9;
        else return 10;
    }else if (Origin==8){
        if (temp<=0.23)return 0;
        else if(temp<=0.63) return 1;
        else if(temp<=0.82) return 2;
        else if (temp<=0.84) return 6;
        else if (temp<=0.86) return 7;
        else return 10;
    }else if (Origin==9){
        if (temp<=0.09)return 0;
        else if(temp<=0.73) return 1;
        else if(temp<=0.74) return 2;
        else if (temp<=0.75) return 5;
        else if (temp<=0.82) return 6;
        else return 10;
        
    }else{
        return 0;
    }
}

void Sync_Lights(std::vector<TrafficLight*> light_list, std::vector<double> &left_over, bool b_sync){
    
    light_list[0]->cur_phase = 1;
    off_set[0] = 0;
    
    if (!b_sync) {
        //unsynchronized off-set
        for (int i=0; i<3; i++) {
            off_set[i] = off_set[i] + rand()%100;;
        }
        
    }else{
        //synchronized off-set
        off_set[1] = 15.14;
        off_set[2] = 28.17;
        off_set[3] = 48.75;
    }
    
    //initialize the phase of all lights based on offset
    //light 2
    
    left_over.push_back(0);
    
    double offset = off_set[1];
    
    if (offset <=light_list[1]->phase_len[1]) {
        light_list[1]->cur_phase = 1;
        left_over.push_back(offset);
    }else{
        light_list[1]->cur_phase = 0;
        left_over.push_back(offset-light_list[1]->phase_len[1]);
    }
    
    //light 3
    offset = fmod(off_set[2],100);
    
    if (offset <=light_list[2]->phase_len[1]) {
        light_list[2]->cur_phase = 1;
        left_over.push_back(offset);
    }else{
        light_list[2]->cur_phase = 0;
        left_over.push_back(offset-light_list[2]->phase_len[1]);
    }

    //light 5
    offset = fmod(off_set[3],100);
    int i_phase = 3;
    double phase_acum = light_list[3]->phase_len[0];
    while (phase_acum<offset) {
        phase_acum += light_list[3]->phase_len[i_phase];
        --i_phase;
    }
    light_list[3]->cur_phase = i_phase+1;
    left_over.push_back(light_list[3]->phase_len[i_phase+1]-phase_acum+offset);
}


//////////////////////////////////////////
//event handlers
//////////////////////////////////////////

void EnterLinkHandler(struct EventData &e){
    
    if (e.EventType!=ENTER){
        std::cout<<"Error. Wrong event type";
        return;
    }
    
    //check if STOP or EXIT
    int veh_id = e.EventParams.EnterEvent.veh_id;
    Vehicle *veh = &veh_set[veh_id];
    
    int cur_link_id = veh->route[0];
    if (cur_link_id<1000) {
        if (uniRand()<0.5) {
            cur_link_id = cur_link_id*10 + 2;
        }else{
            cur_link_id = cur_link_id*10 + 3;
        }
        veh->route[0] = cur_link_id;
    }
    
    std::cout<<" Vehicle "<<veh_id<<" Enters Link "
    <<cur_link_id<<" at "<<current_time()<<std::endl;
    
    Link *cur_link = link_set[cur_link_id];
    TrafficLight *cur_light = cur_link->light;
    
    if (cur_light){ //if there is a traffic light
        double stop_time = 0;
        if (CheckStop(cur_link, stop_time)){
            if (stop_time<0) {
                stop_time=0;
            }
            double ts = current_time()+stop_time;
            EventData event_data;
            event_data.EventType = STOP;
            event_data.EventParams.StopEvent.veh_id = e.EventParams.EnterEvent.veh_id;
            ScheduleEvent(ts, event_data, StopInLinkHandler);
        }else{
            double ts = current_time() + cur_link->get_travel_time();
            EventData data;
            data.EventType = EXIT;
            data.EventParams.ExitEvent.veh_id = e.EventParams.EnterEvent.veh_id;
            ScheduleEvent(ts, data, ExitLinkHandler);
        }
        
    }else{
        double ts = current_time() + cur_link->get_length()/cur_link->speed;
        EventData data;
        data.EventType = EXIT;
        data.EventParams.ExitEvent.veh_id = e.EventParams.EnterEvent.veh_id;
        ScheduleEvent(ts, data, ExitLinkHandler);
    }
    if (cur_link->is_entrance()){
        double ts = current_time() + RandomExp(e.EventParams.EnterEvent.lambda);
        EventData data;
        data.EventType = ENTER;
        data.EventParams.EnterEvent.lambda = e.EventParams.EnterEvent.lambda;
        int origin = veh->origin;
        int destination = GetDestination(origin);
        std::vector<int> route = GetRoute(origin, destination, od_map);
        double start_time = ts;
        double length=0;
        double clr_time = 0;
        gen_veh_len_clt(length, clr_time);
        Vehicle veh(origin,destination, length, route, start_time, clr_time);
        veh_set[veh_rank] = veh;
        data.EventParams.EnterEvent.veh_id = veh_rank;
        veh_rank++;
        ScheduleEvent(ts, data, EnterLinkHandler);
    }
    
    cur_link->vehicle_count++;
}


void StopInLinkHandler(struct EventData &e){
    //will put the vehicle in the queue
    int cur_veh_id = e.EventParams.StopEvent.veh_id;
    int cur_link_id = veh_set[cur_veh_id].route[0];
    Link * cur_link = link_set[cur_link_id];
    std::cout<<" Vehicle "<<cur_veh_id<<" Stops in Link "
    <<cur_link_id<<" at "<<current_time()<<std::endl;
    cur_link->vehicle_q.push(cur_veh_id);
    
    if (cur_link->light->light_id==4) {
        double ts = current_time() + 5;//stop sign delay 5s
        EventData data;
        data.EventType = EXIT;
        data.EventParams.ExitEvent.veh_id = cur_veh_id;
        ScheduleEvent(ts, data, ExitLinkHandler);
    }
}

void ExitLinkHandler(struct EventData &e){
    int cur_veh_id = e.EventParams.ExitEvent.veh_id;
    Vehicle * cur_veh = &veh_set[cur_veh_id];
    int cur_link_id = veh_set[cur_veh_id].route[0];
    std::cout<<" Vehicle "<<cur_veh_id<<" Exits Link "
    <<cur_link_id<<" At "<<current_time()<<std::endl;
    Link * cur_link = link_set[cur_link_id];
    cur_link->vehicle_count--;
    
    //update the route for current vehicle
    cur_veh->route.erase(cur_veh->route.begin());
    
    if (cur_veh->route.empty())
    {
        //no next link, will exit the simulation and will check if
        //the vehicle should be considered for travel time evaluation
        if ((cur_veh->origin == 0||cur_veh->origin==1||cur_veh->origin==10) &&
            (cur_veh->destination == 5||cur_veh->destination == 6
             ||cur_veh->destination == 7)) {
            total_num_veh ++;
            total_trvl_time += current_time() - cur_veh->start_time;
            std::string file_name ="output";
            std::ostringstream ostr;
            ostr<<num_run;
            file_name = file_name+ostr.str()+".txt";
            std::fstream results(file_name,std::fstream::out|std::fstream::app);
            results<<" Vehicle "<<cur_veh_id<<" Begins at "<<cur_veh->start_time
            <<" Exits Link"<<cur_link_id<<" At "<<current_time()
            <<" takes "<<current_time()-cur_veh->start_time<<std::endl;
        }
        
    }else{
        //schedule entering next link in CLEAR_TIME
        double ts = current_time() + cur_veh->clear_time;
        EventData data;
        data.EventType = ENTER;
        data.EventParams.EnterEvent.veh_id = cur_veh_id;
        ScheduleEvent(ts, data, EnterLinkHandler);
    }
}

void ChangeLightHandler(struct EventData &e){
    //check event type ...
    //change phase
    TrafficLight *lt = e.EventParams.ChangeLight.light;
    
    int cur_phase = lt->cur_phase;
    int phase_num = lt->phase_num;
    int next_phase = (++cur_phase)%phase_num;
    std::cout<<" Traffic Light "<<lt->light_id<<" Changes to Phase "
    <<next_phase<<" at "<<current_time()<<std::endl;
    lt->cur_phase=next_phase;
    
    //schedule vehicle in the queue to exit links
    std::vector<int>::size_type num_link = lt->exit_link_id.size();
    for (int i=0; i<num_link; i++)
    {
        int cur_lk_id = lt->exit_link_id[i];
        Link * cur_link = link_set[cur_lk_id];
        
        if (cur_link->exit_phase==lt->cur_phase){
            //schedule the link to clear its queue
            double green_time = lt->phase_len[lt->cur_phase];
            double pt = 0;
            while ((!cur_link->vehicle_q.empty())&&green_time>pt) {
                int front_veh_id = cur_link->vehicle_q.front();
                EventData data;
                data.EventType = EXIT;
                data.EventParams.ExitEvent.veh_id = front_veh_id;
                double ts = current_time() + pt;
                pt+=veh_set[front_veh_id].clear_time;
                cur_link->vehicle_q.pop();
                ScheduleEvent(ts, data, ExitLinkHandler);
            }
        }
    }
    //schedule next light change
    double ts = current_time() + lt->phase_len[next_phase];
    EventData data;
    data.EventType = ChangeLight;
    data.EventParams.ChangeLight.light = lt;
    ScheduleEvent(ts, data, ChangeLightHandler);
}



////////////////////////////////////////////////////////////////////////////////
//
//      Initialize System and Run simulation
//
////////////////////////////////////////////////////////////////////////////////

void SystemRun(bool b_sync, double simu_period)
{
    Initialize();
    
    srand((int)time(NULL));
    
    for (int ientr = 0; ientr<11; ientr++){
        EventData data;
        data.EventType = ENTER;
        double start_time = current_time();
        int origin = ientr;
        int destination = GetDestination(origin);
        auto route = GetRoute(origin, destination, od_map);
        double veh_len =0;
        double clt = 0;
        gen_veh_len_clt(veh_len, clt);
        Vehicle veh(origin, destination, veh_len, route, start_time, clt);
        data.EventParams.EnterEvent.veh_id = veh_rank;
        veh_set[veh_rank] = veh;
        veh_rank++;
        data.EventParams.EnterEvent.lambda = lamda_list[ientr];
        ScheduleEvent(current_time(), data, EnterLinkHandler);
    }
    
    std::vector<TrafficLight*> light_list={&lt1, &lt2, &lt3, &lt5};
    std::vector<double> left_over;
    Sync_Lights(light_list, left_over, b_sync);
    
    left_over[0] =lt1.phase_len[1];
    for (int ilight = 0; ilight<4; ilight ++) {
        EventData data;
        data.EventType = ChangeLight;
        data.EventParams.ChangeLight.light = light_list[ilight];
        double t= current_time();
        ScheduleEvent(t+left_over[ilight], data, ChangeLightHandler);
    }
    
    Sim(simu_period);
    std::cout<<"-----------------Report Stats--------------"<<std::endl
    << "The NO."<<num_run<<" simulation has completed."<<std::endl
    <<"Total number of vehicles from 10th to 14th: "<<total_num_veh<<std::endl
    <<"Average travel time from 10th to 14th: "
    <<total_trvl_time/total_num_veh<<std::endl;
    num_run++;
}

