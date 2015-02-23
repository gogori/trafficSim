//
//  main.cpp
//  trafficSim
//
//  Created by Jinqi Fang on 1/21/15.
//  Copyright (c) 2015 Jinqi Fang. All rights reserved.
//

#include <iostream>
#include "system.h"
int main(int argc, const char * argv[]) {

    int num_of_run;//number of runs to run
    char sync_char;//get sync status
    bool sync;
    double simu_period;//simulation period for each run
    
    std::cout<<"How many runs do you want to simulate?"<<std::endl;
    std::cin>>num_of_run;
    
    std::cout<<"Do you want synchronized signal? Y/N"<<std::endl;
    std::cin>>sync_char;
    
    if (sync_char=='Y') {
        sync = true;
    }else{
        sync = false;
    }
    
    std::cout<<"How long do you want to simulate for each run in seconds?"<<std::endl;
    std::cin>>simu_period;
    
    for (int i=0; i<num_of_run;i++)
    {
        SystemRun(sync, simu_period);
    }
    return 0;
}
