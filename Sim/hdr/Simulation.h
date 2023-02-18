#pragma once

#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <vector>
#include <queue>

#include "SimTypes.h"
#include "SimParams.h"
#include "Statistics.h"
#include "Vehicle.h"

class Simulation
{
public:
    Simulation(SimParams& params);
    ~Simulation();

    //
    //Name: InitSim
    //Brief:  Initializes simulation objects such as the vehicle list, charger queues, and total vehicle statistics
    //
    //Param: None
    //
    //Retval: true if the sim initialized without error, false if an error occurred.
    bool_t InitSim();

    //
    //Name: CreateVehicles
    //Brief:  Creates the vehicles to be used in the sim, utilizes the SimParams object.
    //
    //Param: None
    //
    //Retval: true if vehicles created, false if an error occurred.
    bool_t CreateVehicles();

    //
    //Name: RunSim
    //Brief: Determines the number of iterations to run and calls update at each iteration
    //
    //Param: None
    //
    //Retval: None
    void RunSim();

    //
    //Name: ComputeStatistics
    //Brief: Computes the total statistics per vehicle type for the entire simulation. 
    //       Can be called anytime, but is expected to be called once at simulation conclusion.
    //
    //Param: None
    //
    //Retval: None
    void ComputeStatistics();

    //
    //Name: PrintStatistics
    //Brief:  Outputs the statistics to a file
    //
    //Param: None
    //
    //Retval: true if statistics have been printed, false if an error occurred.
    bool_t PrintStatistics();


private:

    //
    //Name: UpdateSim
    //Brief:  Updates the simulation for the current time step.
    //
    //Param: None
    //
    //Retval: None
    void UpdateSim();

    //
    //Name: TypeToString
    //Brief: Outputs the string equivalent of a vehicle type name.
    //
    //Param: None
    //
    //Retval: String conversion of the vehicle type name
    string TypeToString(Vehicle::VehicleType t);

    vector<Vehicle> vehicleList;                //! List of vehicles in the simulation
    vector<Statistics> vehicleStats;            //! Statistics of each vehicle type in the simulation.

    vector<queue<uint32_t>> chargerList;        //! List of Queues for the chargers in the simulation (the number corresponds to the vehicle index in the list)

    SimParams& simParams;                       //! Simulation parameters

    uint32_t typeCount[NUM_VEHICLE_TYPES];      //! Count of each type of vehicle.

};


#endif