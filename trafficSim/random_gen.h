//
//  random_gen.h
//  trafficSim
//
//  Created by Jinqi Fang on 2/12/15.
//  Copyright (c) 2015 Jinqi Fang. All rights reserved.
//

#ifndef __trafficSim__random_gen__
#define __trafficSim__random_gen__

#include <stdio.h>
/**
 *  generate random numbers following a exponential distribution idenfified by mean M
 *  using the inverse function method
 *
 *  @param M mean of the exponential distribution
 *
 *  @return double random number
 */
double RandomExp(double M);

/**
 *  generate a uniform random number between 0 and 1
 *
 *  @return double random number
 */
double uniRand();
#endif /* defined(__trafficSim__random_gen__) */
