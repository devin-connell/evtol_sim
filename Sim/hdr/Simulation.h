#pragma once

#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <vector>

#include "SimTypes.h"
#include "SimParams.h"
#include "Statistics.h"
#include "Vehicle.h"

class Simulation
{
public:
    Simulation();
    ~Simulation();



    void InitSim(SimParams& params);

    void RunSim();

private:

    void UpdateSim();
    void UpdateStatistics();

    vector<Vehicle> vehicleList;
    vector<Statistics> simStats;
    SimParams simParams;

};


#endif