//
//  event.cpp
//  trafficSim
//
//  Created by Jinqi Fang on 2/12/15.
//  Copyright (c) 2015 Jinqi Fang. All rights reserved.
//

#include <string>
#include "event.h"

////type of events
std::string printEvent( typeofevents enumVal )
{
    std::string eventName[]={"Enter Section","Exit Section",
        "Stop in Section","Change Traffic Light" };
    return eventName[enumVal];
}