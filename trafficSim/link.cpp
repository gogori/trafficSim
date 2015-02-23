//
//  link.cpp
//  trafficSim
//
//  Created by Jinqi Fang on 1/30/15.
//  Copyright (c) 2015 Jinqi Fang. All rights reserved.
//

#include "link.h"
Link::Link(int _id, int _exit_phase, TrafficLight *_light, double _speed, int _cnt, double _len, bool _entrance, bool _exit){
    link_id = _id;
    exit_phase = _exit_phase;
    light = _light;
    vehicle_count = _cnt;
    speed = _speed;
    this->_length = _len;
    this->_entrance = _entrance;
    this->_exit=_exit;
}

Link::Link(){
    
}