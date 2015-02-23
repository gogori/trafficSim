//
//  event.h
//  trafficSim
//
//  Created by Jinqi Fang on 2/12/15.
//  Copyright (c) 2015 Jinqi Fang. All rights reserved.
//

#ifndef __trafficSim__event__
#define __trafficSim__event__

#include <stdio.h>
#include <string>
#include "trafficlight.h"

/////////////////////////////////////////////////////////
//
//Type of events
//
/////////////////////////////////////////////////////////

typedef enum {ENTER, EXIT, STOP, ChangeLight} typeofevents;
std::string printEvent( typeofevents enumVal );

struct EnterEventStr{
    int veh_id;
    double lambda;
};

struct StopEventStr{
    int veh_id;
};

struct ExitEventStr{
    int veh_id;
};

struct ChangeLightStr{
    TrafficLight *light;
};

struct EventParamsStr{
    EnterEventStr EnterEvent;
    StopEventStr StopEvent;
    ExitEventStr ExitEvent;
    ChangeLightStr ChangeLight;
};

struct EventData{
    typeofevents EventType;
    EventParamsStr EventParams;
};

struct Event{
    double EventTime;
    struct EventData data;
    void (*EventHandler)(struct EventData&);
};
#endif /* defined(__trafficSim__event__) */
