#pragma once

#ifndef __STATISTICS_H__
#define __STATISTICS_H__

#include "SimTypes.h"
#include "SimParams.h"


//Statistics class, this could really be a struct. Could just make the vehicle class a friend since it will be accessing these items constantly.
class Statistics
{
public:

    Statistics();
    ~Statistics();

    void SetFlightTime(float64_t time)
    {
        flightTime = time;
    }

    float64_t GetFlightTime()
    {
        return flightTime;
    }

    void SetFlightDistance(float64_t distance)
    {
        flightDistance = distance;
    }

    float64_t GetFlightDistance()
    {
        return flightDistance;
    }

    void SetChargeTime(float64_t time)
    {
        chargeTime = time;
    }

    float64_t GetChargeTime()
    {
        return chargeTime;
    }

    void IncrementNumFaults()
    {
        numFaults++;
    }

    uint32_t GetNumFaults()
    {
        return numFaults;
    }

    void SetPassengerMiles(float64_t miles)
    {
        passengerMiles = miles;
    }

    float64_t GetPassengerMiles()
    {
        return passengerMiles;
    }

private:

    float64_t flightTime;
    float64_t flightDistance;
    float64_t chargeTime;
    uint32_t numFaults;                 //! Count of faults that occurred during the sim
    float64_t passengerMiles;

};

#endif