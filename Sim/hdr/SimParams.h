#pragma once

#ifndef __SIMPARAMS_H__
#define __SIMPARAMS_H__

#include <string>

#include "SimTypes.h"


class SimParams
{
public:

    typedef enum SimPreset
    {
        INVALID = 0,
        DEFAULT,            //! Minimum 1 of each type, random for remaining number
        EQUAL_NUMBER,       //! Equal number of vehicles of all types
        MAX_ALPHA,          //! 1 of each type all others Alpha type
        MAX_BRAVO,
        MAX_CHARLIE,
        MAX_DELTA,
        MAX_ECHO,
        DOUBLE_CHARGERS,    //! Double the number of default chargers
        ONE_CHARGER,        //! Limit the number of chargers to 1
        CHARGE_AT_75,
        CHARGE_AT_90,

        NUM_PRESETS

    } SimPreset_t;

    SimParams();
    ~SimParams();

    bool_t InitializeParameters(string fileName);

    void SetTimeStep(float64_t step)
    {
        timeStep = step;
    }

    float64_t GetTimeStep()
    {
        return timeStep;
    }

    void SetNumVehicles(uint32_t vehicles)
    {
        numVehicles = vehicles;
    }

    uint32_t GetNumVehicles()
    {
        return numVehicles;
    }

    void SetNumChargers(uint32_t chargers)
    {
        numChargers = chargers;
    }

    uint32_t GetNumChargers()
    {
        return numChargers;
    }

    void SetSimDuration(uint32_t duration)
    {
        simDuration = duration;
    }

    uint32_t GetSimDuration()
    {
        return simDuration;
    }

    void SetSimPreset(SimPreset_t preset)
    {
        simPreset = preset;
    }

    SimPreset_t GetSimPreset()
    {
        return simPreset;
    }


private:

    float64_t timeStep;
    uint32_t numVehicles;
    uint32_t numChargers;
    uint32_t simDuration;

    SimPreset_t simPreset;
};

#endif