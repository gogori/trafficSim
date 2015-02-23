//
//  trafficlight.h
//  trafficSim
//
//  Created by Jinqi Fang on 1/30/15.
//  Copyright (c) 2015 Jinqi Fang. All rights reserved.
//

#ifndef __trafficSim__trafficlight__
#define __trafficSim__trafficlight__

#include <stdio.h>
#include <iostream>
#include "link.h"
#include <vector>
class TrafficLight{
public:
    int light_id;
    int cur_phase;
    int phase_num;//number of phases
    double phase_len[4];
    
    TrafficLight(int key, int phase, int num, double phase_l[]);
    TrafficLight(){};
    
    double cycle_len();
    
    std::vector<int> exit_link_id;
};
#endif /* defined(__trafficSim__trafficlight__) */
