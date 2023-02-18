#pragma once

#ifndef __SIMPARAMS_H__
#define __SIMPARAMS_H__

#include <string>

#include "SimTypes.h"


class SimParams
{
public:

    enum SimPreset
    {
        INVALID = 0,
        DEFAULT,            //! Minimum 1 of each type, random for remaining number
        EQUAL_NUMBER,       //! Equal number of vehicles of all types
        MAX_ALPHA,          //! 1 of each type all others ALPHA type
        MAX_BRAVO,          //! 1 of each type all others BRAVO type
        MAX_CHARLIE,        //! 1 of each type all others CHARLIE type
        MAX_DELTA,          //! 1 of each type all others DELTA type
        MAX_ECHO,           //! 1 of each type all others ECHO type
        DOUBLE_CHARGERS,    //! Double the number of chargers indicated in the Chargers token in the config file
        ONE_CHARGER,        //! Limit the number of chargers to 1
        CHARGE_AT_25,       //! Vehicles are allowed to charge at 25% battery
        CHARGE_AT_10,       //! Vehicles are allowed to charge at 10% battery

        NUM_PRESETS

    };

    SimParams();
    ~SimParams();

    //
    //Name: InitializeParameters
    //Brief:  Sets the simulation parameters based on what is read from the configuration file.
    //
    //Param[in]: string fileName
    //
    //Retval: true if parameters set without error, false if a parameter read error occurs
    bool_t InitializeParameters(string fileName);


    //-------------------------------------------------------------------------------------
    // Setters and Getters.
    //-------------------------------------------------------------------------------------

    //
    //Name: SetTimeStep
    //Brief:  Sets simulation time step in seconds
    //
    //Param[in]: float64_t step in seconds
    //
    //Retval: None
    void SetTimeStep(float64_t step)
    {
        timeStep = step;
    }

    //
    //Name: GetTimeStep
    //Brief:  Accesses the simulation time step.
    //
    //Param: None
    //
    //Retval: Simulation time step in seconds.
    float64_t GetTimeStep()
    {
        return timeStep;
    }

    //
    //Name: SetNumVehicles
    //Brief:  Sets the number of vehicles in the simulation.  Valid range 5-100
    //
    //Param[in]: uint32_t number of vehicles
    //
    //Retval: None
    void SetNumVehicles(uint32_t vehicles)
    {
        numVehicles = vehicles;
    }

    //
    //Name: GetNumVehicles
    //Brief:  Accesses the number of vehicles in the simulation.
    //
    //Param: None
    //
    //Retval: Number of vehicles.
    uint32_t GetNumVehicles()
    {
        return numVehicles;
    }

    //
    //Name: SetNumChargers
    //Brief:  Sets the number of chargers used in the simulation.
    //
    //Param[in]: uint32_t chargers
    //
    //Retval: None
    void SetNumChargers(uint32_t chargers)
    {
        numChargers = chargers;
    }

    //
    //Name: GetNumChargers
    //Brief:  Accesses the number of chargers in the simulation.
    //
    //Param: None
    //
    //Retval: Number of chargers.
    uint32_t GetNumChargers()
    {
        return numChargers;
    }

    //
    //Name: SetSimDuration
    //Brief:  Sets the simulation duration in hours, valid range 3-24
    //
    //Param[in]: uint32_t duration
    //
    //Retval: None
    void SetSimDuration(uint32_t duration)
    {
        simDuration = duration;
    }

    //
    //Name: GetSimDuration
    //Brief:  Accesses the simulation duration parameter.
    //
    //Param: None
    //
    //Retval: Simulation duration in hours.
    uint32_t GetSimDuration()
    {
        return simDuration;
    }

    //
    //Name: SetSimPreset
    //Brief:  Sets the simulation preset enumeration value.  The preset determines additional behaviors within the sim.
    //        An example is MAX_BRAVO where there is 1 of each type of vehicle and all others are the BRAVO type.
    //
    //Param[in]: SimPreset preset
    //
    //Retval: None
    void SetSimPreset(SimPreset preset)
    {
        simPreset = preset;
    }

    //
    //Name: GetSimPreset
    //Brief:  Accesses the current simulation preset.
    //
    //Param: None
    //
    //Retval: Sim Preset enumeration value.
    SimPreset GetSimPreset()
    {
        return simPreset;
    }


private:

    float64_t timeStep;         //! Time elapsed between iterations of the simulation, in seconds
    uint32_t numVehicles;       //! Total number of vehicles in the sim (3, 24)
    uint32_t numChargers;       //! Total number of chargers used in the sim.
    uint32_t simDuration;       //! Total duration of the simulation in hours (3, 24)

    SimPreset simPreset;        //! Preset enumeration value to change how the sim is initialized
};

#endif