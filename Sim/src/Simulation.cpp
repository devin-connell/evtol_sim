
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

        status = CreateVehicles();

    }
    return status;
}

bool_t Simulation::CreateVehicles()
{
    bool_t status = true;
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
        for (uint64_t i = vehicleList.size(); i < simParams.GetNumVehicles(); ++i)
        {
            uint16_t vehicle_type = (uint16_t)((rand() % 5) + 1);   //Generates a random number between 1 and 5 inclusive (correspondes to Vehicle::VehicleType enum)
            sim_vehicle.InitializeVehicle(Vehicle::VehicleType(vehicle_type));
            vehicleList.push_back(sim_vehicle);
        }
        queue<uint32_t> q;
        chargerList.push_back(q);
        chargerList.push_back(q);
        chargerList.push_back(q);
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
        status = false;
        break;
    }
    }

    return status;
}

void Simulation::RunSim()
{
    //Use sim parameters to determine how many iterations should happen in the sim
    float64_t num_iterations = 0;

    num_iterations = 3600.0 / simParams.GetTimeStep() * simParams.GetSimDuration();

    for (float64_t i = 0.0; i < num_iterations + 1; ++i)
    {
        UpdateSim();
    }

}


//Private Methods

void Simulation::UpdateSim()
{
    //Loop over the vehicles and do the following:
    //Update vehicles
    //If a vehicle needs a charger add it to a queue
    //If a vehicle is done charging, remove it from the queue.
    for (uint16_t i = 0; i < vehicleList.size(); ++i)
    {
        vehicleList[i].Update();

        if (vehicleList[i].GetChargerNeeded())
        {
            //Method works for default number of chargers, and variable chargers.
            pair<uint64_t, uint64_t> charger_pair(10000, 10000); //index, value pair
            for (uint16_t j = 0; j < chargerList.size(); ++j)
            {
                uint64_t val = min(charger_pair.second, chargerList[j].size());
                if (val != charger_pair.second)
                {
                    charger_pair.first = j;
                    charger_pair.second = val;
                }
            }
            chargerList[charger_pair.first].push(i);
            vehicleList[i].SetChargerNeeded(false);
        }
    }

    for (uint16_t i = 0; i < chargerList.size(); ++i)
    {
        if (!chargerList[i].empty())
        {
            //Check if any vehicles are done charging.
            if (vehicleList[chargerList[i].front()].GetChargingComplete())
            {
                vehicleList[chargerList[i].front()].SetChargingComplete(false);
                vehicleList[chargerList[i].front()].SetChargingStatus(false);
                chargerList[i].pop();
            }
            if (vehicleList[chargerList[i].front()].GetChargingStatus() == false)
            {
                vehicleList[chargerList[i].front()].SetChargingStatus(true);
                vehicleList[chargerList[i].front()].SetWaitingForCharger(false);
            }
        }
    }
}

void Simulation::ComputeStatistics()
{

}
