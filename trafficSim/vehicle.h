//
//  vehicle.h
//  trafficSim
//
//  Created by Jinqi Fang on 1/30/15.
//  Copyright (c) 2015 Jinqi Fang. All rights reserved.
//

#ifndef __trafficSim__vehicle__
#define __trafficSim__vehicle__

#include <stdio.h>
#include <vector>

class Vehicle{
public:
    int origin;
    int destination;
    double length;
    std::vector<int>route;
    double start_time;
    double clear_time;
    
    Vehicle(int o, int d, double len, std::vector<int> rt, double t, double clt);
    Vehicle();
};

#endif /* defined(__trafficSim__vehicle__) */
