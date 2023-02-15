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
    Simulation(SimParams& params);
    ~Simulation();



    bool_t InitSim();

    bool_t CreateVehicles();

    void RunSim();

private:

    void UpdateSim();
    void UpdateStatistics();

    vector<Vehicle> vehicleList;
    vector<Statistics> simStats;
    SimParams& simParams;

};


#endif