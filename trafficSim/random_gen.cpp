//
//  random_gen.cpp
//  trafficSim
//
//  Created by Jinqi Fang on 2/12/15.
//  Copyright (c) 2015 Jinqi Fang. All rights reserved.
//

#include <random>
#include "random_gen.h"
//exponential random variable generator

double RandomExp(double M){
    double urand;   // uniformly distributed random number [0,1)
    urand = ((double) rand ()) / (((double) RAND_MAX)+1.0); // avoid value 1.0
    double time = -M * log(1.0-urand);
    return time;
}

double uniRand(){
    double urand = ((double) rand ()) / (((double) RAND_MAX)+1.0);
    return urand;
}