//
//  simengine.h
//  trafficSim
//
//  Created by Jinqi Fang on 2/12/15.
//  Copyright (c) 2015 Jinqi Fang. All rights reserved.
//

#ifndef __trafficSim__simengine__
#define __trafficSim__simengine__

#include <stdio.h>
#include <vector>
#include <math.h>
#include <time.h>
#include <queue>
#include "event.h"

/**
 *  schedule a event by push the event to the FEL
 *
 *  @param ts   event time
 *  @param data event data
 *  @param cb   pointer to the event handler
 */
void ScheduleEvent (double ts, EventData &data, void (*cb)(EventData &));

/**
 *  returns current simulation time
 *
 *  @return double indicates current simulation time
 */
double current_time();

/**
 *  runs simulation
 *
 *  @param du simulatio duration
 */
void Sim(double du);

#endif /* defined(__trafficSim__simengine__) */
