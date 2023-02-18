
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <fstream>

#include "Simulation.h"

Simulation::Simulation(SimParams& params) :
    simParams(params)
{
    for (uint16_t i = 0; i < NUM_VEHICLE_TYPES; ++i)
    {
        Statistics s;
        vehicleStats.push_back(s);
    }
}

Simulation::~Simulation()
{

}


bool_t Simulation::InitSim()
{
    bool_t status = false;
    if (simParams.GetSimPreset() != SimParams::SimPreset::INVALID)
    {
        //TODO: Write utility functions to handle all random number generation. Can be simple c-style rand, or C++ random library
        srand((uint32_t)time(NULL));
        (void)rand();

        status = CreateVehicles();

    }
    return status;
}

bool_t Simulation::CreateVehicles()
{
    bool_t status = true;

    //First create 5 vehicles, 1 of each type to match simulation requirements.
    Vehicle sim_vehicle(simParams);
    for (uint16_t i = 0; i<NUM_VEHICLE_TYPES; ++i)
    {
        sim_vehicle.InitializeVehicle(Vehicle::VehicleType(i));
        vehicleList.push_back(sim_vehicle);
        typeCount[Vehicle::VehicleType(i)]++;
    }

    //Determine vehicle and charger numbers and behaviors and add them based on the SimPreset indicated.
    switch (simParams.GetSimPreset())
    {
    case SimParams::SimPreset::DEFAULT:
    {
        for (uint64_t i = vehicleList.size(); i < simParams.GetNumVehicles(); ++i)
        {
            uint16_t vehicle_type = (uint16_t)(rand() % 5);   //Generates a random number between 1 and 5 inclusive (correspondes to Vehicle::VehicleType enum)
            sim_vehicle.InitializeVehicle(Vehicle::VehicleType(vehicle_type));
            typeCount[vehicle_type]++;
            vehicleList.push_back(sim_vehicle);
        }

        //create the charger queues
        for (uint16_t i = 0; i < simParams.GetNumChargers(); ++i)
        {
            queue<uint32_t> q;
            chargerList.push_back(q);
        }
        break;
    }
    case SimParams::SimPreset::DOUBLE_CHARGERS:
    {
        for (uint64_t i = vehicleList.size(); i < simParams.GetNumVehicles(); ++i)
        {
            uint16_t vehicle_type = (uint16_t)(rand() % 5);   //Generates a random number between 1 and 5 inclusive (correspondes to Vehicle::VehicleType enum)
            sim_vehicle.InitializeVehicle(Vehicle::VehicleType(vehicle_type));
            typeCount[vehicle_type]++;
            vehicleList.push_back(sim_vehicle);
        }

        for (uint16_t i = 0; i<simParams.GetNumChargers() * 2; ++i)
        {
            queue<uint32_t> q;
            chargerList.push_back(q);
        }
        break;
    }

    case SimParams::SimPreset::EQUAL_NUMBER:
    case SimParams::SimPreset::MAX_ALPHA:
    case SimParams::SimPreset::MAX_BRAVO:
    case SimParams::SimPreset::MAX_CHARLIE:
    case SimParams::SimPreset::MAX_DELTA:
    case SimParams::SimPreset::MAX_ECHO:
    case SimParams::SimPreset::ONE_CHARGER:
    case SimParams::SimPreset::CHARGE_AT_25:
    case SimParams::SimPreset::CHARGE_AT_10:
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

bool_t Simulation::PrintStatistics()
{
    fstream stat_file;
    bool_t status = true;

    stat_file.open("..\\stat_file.txt", ios::out);

    if (stat_file.is_open())
    {
        for (uint16_t i = 0; i < NUM_VEHICLE_TYPES; ++i)
        {
            stat_file << "Vehicle Type: " << TypeToString((Vehicle::VehicleType)i) << endl;
            stat_file << "Num Vehicles: " << typeCount[i] << endl;
            stat_file << "Flight Distance: " << vehicleStats[i].GetFlightDistance() << " miles" << endl;
            stat_file << "Passenger Miles: " << vehicleStats[i].GetPassengerMiles() << " miles" << endl;
            stat_file << "Flight Time: " << vehicleStats[i].GetFlightTime() << " hours" << endl;
            stat_file << "Charge Time: " << vehicleStats[i].GetChargeTime() << " hours" << endl;
            stat_file << "Num Faults: " << vehicleStats[i].GetNumFaults() << endl;
            stat_file << endl;
        }
    }
    else
    {
        cout << "ERROR: Unable to open statistics file" << endl;
        status = false;
    }
    return status;
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
            if (!chargerList[i].empty() && vehicleList[chargerList[i].front()].GetChargingStatus() == false)
            {
                vehicleList[chargerList[i].front()].SetChargingStatus(true);
                vehicleList[chargerList[i].front()].SetWaitingForCharger(false);
            }
        }
    }
}

void Simulation::ComputeStatistics()
{
    //Loop through each vehicle and add up all the statistics
    for (uint16_t i = 0; i < simParams.GetNumVehicles(); ++i)
    {
        switch (vehicleList[i].GetVehicleType())
        {
        case Vehicle::VehicleType::ALPHA:
        {
            vehicleStats[Vehicle::VehicleType::ALPHA].SetChargeTime(vehicleStats[Vehicle::VehicleType::ALPHA].GetChargeTime() + vehicleList[i].GetChargeTime());
            vehicleStats[Vehicle::VehicleType::ALPHA].SetFlightDistance(vehicleStats[Vehicle::VehicleType::ALPHA].GetFlightDistance() + vehicleList[i].GetVehicleStats().GetFlightDistance());
            vehicleStats[Vehicle::VehicleType::ALPHA].SetFlightTime(vehicleStats[Vehicle::VehicleType::ALPHA].GetFlightTime() + vehicleList[i].GetVehicleStats().GetFlightTime());
            vehicleStats[Vehicle::VehicleType::ALPHA].SetPassengerMiles(vehicleStats[Vehicle::VehicleType::ALPHA].GetPassengerMiles() + vehicleList[i].GetVehicleStats().GetPassengerMiles());
            vehicleStats[Vehicle::VehicleType::ALPHA].SetNumFaults(vehicleStats[Vehicle::VehicleType::ALPHA].GetNumFaults() + vehicleList[i].GetVehicleStats().GetNumFaults());

            break;
        }
        case Vehicle::VehicleType::BRAVO:
        {
            vehicleStats[Vehicle::VehicleType::BRAVO].SetChargeTime(vehicleStats[Vehicle::VehicleType::BRAVO].GetChargeTime() + vehicleList[i].GetChargeTime());
            vehicleStats[Vehicle::VehicleType::BRAVO].SetFlightDistance(vehicleStats[Vehicle::VehicleType::BRAVO].GetFlightDistance() + vehicleList[i].GetVehicleStats().GetFlightDistance());
            vehicleStats[Vehicle::VehicleType::BRAVO].SetFlightTime(vehicleStats[Vehicle::VehicleType::BRAVO].GetFlightTime() + vehicleList[i].GetVehicleStats().GetFlightTime());
            vehicleStats[Vehicle::VehicleType::BRAVO].SetPassengerMiles(vehicleStats[Vehicle::VehicleType::BRAVO].GetPassengerMiles() + vehicleList[i].GetVehicleStats().GetPassengerMiles());
            vehicleStats[Vehicle::VehicleType::BRAVO].SetNumFaults(vehicleStats[Vehicle::VehicleType::BRAVO].GetNumFaults() + vehicleList[i].GetVehicleStats().GetNumFaults());

            break;
        }
        case Vehicle::VehicleType::CHARLIE:
        {
            vehicleStats[Vehicle::VehicleType::CHARLIE].SetChargeTime(vehicleStats[Vehicle::VehicleType::CHARLIE].GetChargeTime() + vehicleList[i].GetChargeTime());
            vehicleStats[Vehicle::VehicleType::CHARLIE].SetFlightDistance(vehicleStats[Vehicle::VehicleType::CHARLIE].GetFlightDistance() + vehicleList[i].GetVehicleStats().GetFlightDistance());
            vehicleStats[Vehicle::VehicleType::CHARLIE].SetFlightTime(vehicleStats[Vehicle::VehicleType::CHARLIE].GetFlightTime() + vehicleList[i].GetVehicleStats().GetFlightTime());
            vehicleStats[Vehicle::VehicleType::CHARLIE].SetPassengerMiles(vehicleStats[Vehicle::VehicleType::CHARLIE].GetPassengerMiles() + vehicleList[i].GetVehicleStats().GetPassengerMiles());
            vehicleStats[Vehicle::VehicleType::CHARLIE].SetNumFaults(vehicleStats[Vehicle::VehicleType::CHARLIE].GetNumFaults() + vehicleList[i].GetVehicleStats().GetNumFaults());

            break;
        }
        case Vehicle::VehicleType::DELTA:
        {
            vehicleStats[Vehicle::VehicleType::DELTA].SetChargeTime(vehicleStats[Vehicle::VehicleType::DELTA].GetChargeTime() + vehicleList[i].GetChargeTime());
            vehicleStats[Vehicle::VehicleType::DELTA].SetFlightDistance(vehicleStats[Vehicle::VehicleType::DELTA].GetFlightDistance() + vehicleList[i].GetVehicleStats().GetFlightDistance());
            vehicleStats[Vehicle::VehicleType::DELTA].SetFlightTime(vehicleStats[Vehicle::VehicleType::DELTA].GetFlightTime() + vehicleList[i].GetVehicleStats().GetFlightTime());
            vehicleStats[Vehicle::VehicleType::DELTA].SetPassengerMiles(vehicleStats[Vehicle::VehicleType::DELTA].GetPassengerMiles() + vehicleList[i].GetVehicleStats().GetPassengerMiles());
            vehicleStats[Vehicle::VehicleType::DELTA].SetNumFaults(vehicleStats[Vehicle::VehicleType::DELTA].GetNumFaults() + vehicleList[i].GetVehicleStats().GetNumFaults());

            break;
        }
        case Vehicle::VehicleType::ECHO:
        {
            vehicleStats[Vehicle::VehicleType::ECHO].SetChargeTime(vehicleStats[Vehicle::VehicleType::ECHO].GetChargeTime() + vehicleList[i].GetChargeTime());
            vehicleStats[Vehicle::VehicleType::ECHO].SetFlightDistance(vehicleStats[Vehicle::VehicleType::ECHO].GetFlightDistance() + vehicleList[i].GetVehicleStats().GetFlightDistance());
            vehicleStats[Vehicle::VehicleType::ECHO].SetFlightTime(vehicleStats[Vehicle::VehicleType::ECHO].GetFlightTime() + vehicleList[i].GetVehicleStats().GetFlightTime());
            vehicleStats[Vehicle::VehicleType::ECHO].SetPassengerMiles(vehicleStats[Vehicle::VehicleType::ECHO].GetPassengerMiles() + vehicleList[i].GetVehicleStats().GetPassengerMiles());
            vehicleStats[Vehicle::VehicleType::ECHO].SetNumFaults(vehicleStats[Vehicle::VehicleType::ECHO].GetNumFaults() + vehicleList[i].GetVehicleStats().GetNumFaults());

            break;
        }
        case Vehicle::VehicleType::INVALID:
        default:
        {
            break;
        }
        } //! End Switch
    }    
}

string Simulation::TypeToString(Vehicle::VehicleType type)
{
    switch (type)
    {
    case Vehicle::VehicleType::ALPHA:
        return "ALPHA";
    case Vehicle::VehicleType::BRAVO:
        return "BRAVO";
    case Vehicle::VehicleType::CHARLIE:
        return "CHARLIE";
    case Vehicle::VehicleType::DELTA:
        return "DELTA";
    case Vehicle::VehicleType::ECHO:
        return "ECHO";
    case Vehicle::VehicleType::INVALID:
    default:
        return "INVALID";

    }
}