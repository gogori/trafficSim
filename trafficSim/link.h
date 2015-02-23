//
//  link.h
//  trafficSim
//
//  Created by Jinqi Fang on 1/30/15.
//  Copyright (c) 2015 Jinqi Fang. All rights reserved.
//

#ifndef __trafficSim__link__
#define __trafficSim__link__

#include <stdio.h>
#include <queue>
#include "trafficlight.h"
class TrafficLight;
class Link{
public:
    int link_id;
    int exit_phase;
    double speed;
    
    TrafficLight *light;
    
    int vehicle_count;//num of veh on the link
    std::queue<int> vehicle_q;
    
    bool is_exit(){
        return _exit;
    }
    
    bool is_entrance(){
        return _entrance;
    }
    double get_length(){
        return this->_length;
    }
    double get_travel_time(){
        return _length/speed;
    }
    Link(int _id, int _exit_phase, TrafficLight *_light, double _speed, int _cnt, double _len, bool _entrance, bool _exit);
    Link();
    
private:
    double _length;
    bool _entrance;
    bool _exit;
    
};
#endif /* defined(__trafficSim__link__) */
