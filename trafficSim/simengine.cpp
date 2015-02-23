//
//  simengine.cpp
//  trafficSim
//
//  Created by Jinqi Fang on 2/12/15.
//  Copyright (c) 2015 Jinqi Fang. All rights reserved.
//

#include "simengine.h"

//global variable indicating simulation time
double _current_time = 0;


/////////////////////////////////////////////
//
// Define Future Event List
//
/////////////////////////////////////////////

/**
 *  compare function for constructing the priority queue
 *
 *  @param lhs left param
 *  @param rhs right param
 *
 *  @return return true if left event happens later than right event
 */
bool compare (const struct Event lhs, const struct Event rhs)
{
    return (lhs.EventTime >rhs.EventTime);
}
std::priority_queue<struct Event, std::vector<Event>, decltype(&compare)> FEL(&compare);




/////////////////////////////////////////////
//
// Simulation engine
//
/////////////////////////////////////////////


/////////////schedule a event////////////////

void ScheduleEvent (double ts, EventData &data, void (*cb)(EventData&))
{
    struct Event newEvent;
    newEvent.data = data;
    newEvent.EventHandler = cb;
    newEvent.EventTime = ts;
    FEL.push(newEvent);
}


/////////////begin simulation////////////////
void Sim(double duration){
    struct Event current_event;
    while (current_time()<duration){
        current_event = FEL.top();
        FEL.pop();
        _current_time = current_event.EventTime;
        current_event.EventHandler(current_event.data);
    }
}

//get current simulation time
double current_time(){
    return _current_time;
}

