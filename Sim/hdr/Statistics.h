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

    //
    //Name: IncrementNumFaults
    //Brief:  Increments the current number of faults by 1. Used while the simulation is running.
    //
    //Param: None.
    //
    //Retval: None.
    void IncrementNumFaults()
    {
        numFaults++;
    }

    //-------------------------------------------------------------------------------------
    // Setters and Getters.
    //-------------------------------------------------------------------------------------


    //
    //Name: SetTimeStep
    //Brief:  Sets simulation time step in seconds
    //
    //Param[in]: float64_t step in hours
    //
    //Retval: None
    void SetFlightTime(float64_t time)
    {
        flightTime = time;
    }

    //
    //Name: GetTimeStep
    //Brief:  Gets time flown during the simulation
    //
    //Param: None
    //
    //Retval: Flight time in hours
    float64_t GetFlightTime()
    {
        return flightTime;
    }

    //
    //Name: SetFlightDistance
    //Brief:  Sets distance flown during the simulation
    //
    //Param[in]: float64_t distance in miles
    //
    //Retval: None
    void SetFlightDistance(float64_t distance)
    {
        flightDistance = distance;
    }

    //
    //Name: GetFlightDistance
    //Brief:  Gets flight distance flown during the simulation
    //
    //Param: None
    //
    //Retval: Flight distance in miles
    float64_t GetFlightDistance()
    {
        return flightDistance;
    }

    //
    //Name: SetChargeTime
    //Brief:  Sets the time a vehicle or type of vehicle was charging
    //
    //Param[in]: float64_t time in seconds
    //
    //Retval: None
    void SetChargeTime(float64_t time)
    {
        chargeTime = time;
    }

    //
    //Name: GetChargeTime
    //Brief:  Gets time spent charging during the simulation.
    //
    //Param: None
    //
    //Retval: Flight charge time in hours
    float64_t GetChargeTime()
    {
        return chargeTime;
    }

    //
    //Name: SetNumFaults
    //Brief:  Sets the number of faults detected. Used when calculating total statistics by vehicle type.
    //
    //Param[in]: uint32_t faults
    //
    //Retval: None
    void SetNumFaults(uint32_t faults)
    {
        numFaults = faults;
    }

    //
    //Name: GetNumFaults
    //Brief:  Gets the number of faults that occurred during the sim.
    //
    //Param: None
    //
    //Retval: Number of faults
    uint32_t GetNumFaults()
    {
        return numFaults;
    }

    //
    //Name: SetPassengerMiles
    //Brief:  Sets the passenger miles flown
    //
    //Param[in]: float64_t miles
    //
    //Retval: None
    void SetPassengerMiles(float64_t miles)
    {
        passengerMiles = miles;
    }

    //
    //Name: GetPassengerMiles
    //Brief:  Gets the number of passenger miles flown in the simulation
    //
    //Param: None
    //
    //Retval: Number of passenger miles
    float64_t GetPassengerMiles()
    {
        return passengerMiles;
    }

private:

    float64_t flightTime;               //! Time spent flying in hours
    float64_t flightDistance;           //! Distance flown in miles
    float64_t chargeTime;               //! Time spent charging in hours
    uint32_t numFaults;                 //! Count of faults that occurred during the sim
    float64_t passengerMiles;           //! Passenger miles flown (vehicle capacity * flight distance)

};

#endif