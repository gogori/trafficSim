//
//  system.h
//  trafficSim
//
//  Created by Jinqi Fang on 2/12/15.
//  Copyright (c) 2015 Jinqi Fang. All rights reserved.
//

#ifndef __trafficSim__system__
#define __trafficSim__system__

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "trafficlight.h"
#include "simengine.h"
#include "event.h"
#include "link.h"
#include "vehicle.h"
#include "random_gen.h"
#include "trafficlight.h"

/**
 *  initialize the simulation system and run the simulation
 *
 *  @param b_sync      bool indicates synchronized or unsynchronized
 *  @param simu_period time period of simulation
 */

void SystemRun(bool b_sync, double simu_period);


/////////////////////////////////////////////////////////
//
//  event handlers
//
////////////////////////////////////////////////////////

/**
 *  Deals with vehicle enter link event invoked when a vehicle
 *  enters a road section. First check if the vehicle will stop, if will stop
 *  schedule a stop in link event, else schedule a exit link event; Finally, 
 *  if current link is an entrance of the system, schedule another enter link event
 *  following a poisson process
 *
 *  @param event event data
 */
void EnterLinkHandler(struct EventData &event);


/**
 *  Invoked when vehicle stops in the halfway of current section, put the vehicle
 *  in the queue associated with current link
 *
 *  @param event event data
 */
void StopInLinkHandler(struct EventData &event);
    
/**
 *  Invoked when a vehicle exits current section, if current vehicle 
 *  has achieved destination, check its origin and destination, 
 *  if from 10th to 14th output the travel time. If not, schedule entering
 *  next link following the route of the vehicle
 *
 *  @param event event data
 */
void ExitLinkHandler(struct EventData &event);


/**
 *  changes the phase of current lights following a fixed pattern
 *
 *  @param event event data
 */
void ChangeLightHandler(struct EventData &event);//change event



///////////////////////////////////////////////////////
//
// Event handler helper functions
//
///////////////////////////////////////////////////////

/**
 *  Generate a destination code based on origin 
 *  following the OD distribution derived from data
 *
 *  @param Origin integer code indicates origin
 *
 *  @return integer code indicates destination
 */
int GetDestination(int Origin);

/**
 *  check whether a vehicle will stop in current link and compute the stop time
 *
 *  @param current_link pointer to current link
 *  @param stoptime     double indicates time taken for a vehicle to stop
 *
 *  @return bool indicates whether a vehicle will stop in current link
 */
bool CheckStop(Link *current_link, double &stoptime);

/**
 *  get a route based on orign and destination and the SUI map
 *
 *  @param ori     int origin
 *  @param des     int destination
 *  @param od_pair road map connecting origins and destinations
 *
 *  @return a vector of integer indicating route of a vehicle
 */
std::vector<int> GetRoute(int ori, int des, const std::vector<int> od_pair[11][11]);

/**
 *  get the length of the queue in the link
 *
 *  @param link pointer to a link
 *
 *  @return double indicating queue length in foot
 */
double get_queue_len(Link *link);

/**
 *  check if queue will be cleared in time t
 *
 *  @param q_len double left queue length in foot
 *  @param t     double time
 *  @param link  pointer to a link
 *
 *  @return bool indicates whether the queue in link will be clear
 */
bool isLinkClear(double &q_len, double t, Link *link);

/**
 *  geerate vehicle length and vehicle clearance time based on fleet composition distribution
 *
 *  @param len <#len description#>
 *  @param clt <#clt description#>
 */
void gen_veh_len_clt(double &len, double &clt);

/**
 *  synchronize the signal lights by adjusting off-sets
 *
 *  @param light_list list of pointers to traffic lights
 *  @param left_over  double time leftover for first phase
 *  @param b_sync     bool indicates whether to synchronzie the lights
 */
void Sync_Lights(std::vector<TrafficLight*> light_list, std::vector<double> &left_over, bool b_sync);

#endif /* defined(__trafficSim__system__) */
