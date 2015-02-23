//
//  vehicle.cpp
//  trafficSim
//
//  Created by Jinqi Fang on 1/30/15.
//  Copyright (c) 2015 Jinqi Fang. All rights reserved.
//

#include "vehicle.h"
Vehicle::Vehicle(int o, int d, double len, std::vector<int> rt, double t, double clt){
    origin =o;
    destination =d;
    route = rt;
    start_time = t;
    length = len;
    clear_time = clt;
}
Vehicle::Vehicle(){};