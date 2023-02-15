
#include <stdlib.h>
#include <ctime>

#include "Simulation.h"

Simulation::Simulation(SimParams& params) :
    simParams(params)
{

}

Simulation::~Simulation()
{

}


bool_t Simulation::InitSim()
{
    bool_t status = false;
    if (simParams.GetSimPreset() != SimParams::SimPreset::INVALID)
    {
        //TODO: Write utility function to handle all random number generation. Can be simple c-style rand, or C++ random library
        srand((uint32_t)time(NULL));
        (void)rand();


    }
    return status;
}

bool_t Simulation::CreateVehicles()
{
    bool_t status = false;
    //create and Initialize Vehicles

    //First create 5 vehicles, 1 of each type to match simulation requirements.
    uint16_t vehicle_count = 0;
    Vehicle sim_vehicle(simParams);
    do
    {
        vehicle_count++;
        sim_vehicle.InitializeVehicle(Vehicle::VehicleType(vehicle_count));
        vehicleList.push_back(sim_vehicle);
        
    } while (vehicleList.size() < 5);   

    switch (simParams.GetSimPreset())
    {
    case SimParams::SimPreset::DEFAULT:
    {
        for (uint16_t i = vehicleList.size(); i < simParams.GetNumVehicles(); ++i)
        {
            uint16_t vehicle_type = (uint16_t)((rand() % 5) + 1);   //Generates a random number between 1 and 5 inclusive (correspondes to Vehicle::VehicleType enum)
            sim_vehicle.InitializeVehicle(Vehicle::VehicleType(vehicle_type));
            vehicleList.push_back(sim_vehicle);
        }
        break;
    }
    case SimParams::SimPreset::EQUAL_NUMBER:
    case SimParams::SimPreset::MAX_ALPHA:
    case SimParams::SimPreset::MAX_BRAVO:
    case SimParams::SimPreset::MAX_CHARLIE:
    case SimParams::SimPreset::MAX_DELTA:
    case SimParams::SimPreset::MAX_ECHO:
    case SimParams::SimPreset::DOUBLE_CHARGERS:
    case SimParams::SimPreset::ONE_CHARGER:
    case SimParams::SimPreset::CHARGE_AT_75:
    case SimParams::SimPreset::CHARGE_AT_90:
    case SimParams::SimPreset::INVALID:
    default:
    {
        break;
    }
    }

    return status;
}

void Simulation::RunSim()
{

}


//Private Methods

void Simulation::UpdateSim()
{

}

void Simulation::UpdateStatistics()
{

}
