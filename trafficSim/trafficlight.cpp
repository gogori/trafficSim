//
//  trafficlight.cpp
//  trafficSim
//
//  Created by Jinqi Fang on 1/30/15.
//  Copyright (c) 2015 Jinqi Fang. All rights reserved.
//

#include "trafficlight.h"

TrafficLight::TrafficLight(int key, int phase, int num, double phase_l[]){
    
    this->light_id = key;
    this->cur_phase = phase;
    this->phase_num = num;
    
    if (key==2 ||key==3) {
        for (int i= 0;i<2;i++)
        {
            this->phase_len[i] = phase_l[i];
        }
    }else{
        for (int i= 0;i<4;i++)
        {
            this->phase_len[i] = phase_l[i];
        }
    }
}

double TrafficLight::cycle_len(){
    return this->phase_len[0]+this->phase_len[1]+this->phase_len[2]+this->phase_len[3];
}