#pragma once

#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include "SimTypes.h"
#include "SimParams.h"
#include "Statistics.h"

class Vehicle
{
public:

    typedef enum VehicleType
    {
        INVALID = 0,
        ALPHA,
        BRAVO,
        CHARLIE,
        DELTA,
        ECHO,

        NUM_TYPES

    } VehicleType_t;

    Vehicle();
    ~Vehicle();

    void Update();

    void InitializeVehicle(VehicleType_t type);

    //Setters and Getters.
    void SetCruiseSpeed(uint32_t speed)
    {
        cruiseSpeed = speed;
    }

    uint32_t GetCruiseSpeed()
    {
        return cruiseSpeed;
    }

    void SetBatteryCapacity(uint32_t capacity)
    {
        batteryCapacity = capacity;
    }

    uint32_t GetBatteryCapacity()
    {
        return batteryCapacity;
    }

    void SetChargeTime(float64_t time)
    {
        chargeTime = time;
    }

    float64_t GetChargeTime()
    {
        return chargeTime;
    }

    void SetEnergyUse(float64_t usage)
    {
        energyUse = usage;
    }

    float64_t GetEnergyUse()
    {
        return energyUse;
    }

    void SetNumPassengers(uint32_t passengers)
    {
        numPassengers = passengers;
    }

    uint32_t GetNumPassengers()
    {
        return numPassengers;
    }

    void SetFaultChance(float64_t chance)
    {
        faultChance = chance;
    }

    float64_t GetFaultChance()
    {
        return faultChance;
    }

    Statistics& GetVehicleStats()
    {
        return vehicleStats;
    }

    void SetSimParams(SimParams& params)
    {
        simParams = params;
    }

    bool_t GetChargingStatus()
    {
        return charging;
    }

    VehicleType_t GetVehicleType()
    {
        return vehicleType;
    }


private:

    uint32_t cruiseSpeed;
    uint32_t batteryCapacity;
    float64_t chargeTime;
    float64_t energyUse;
    uint32_t numPassengers;
    float64_t faultChance;

    uint32_t numFaults;
    float64_t currentBattery;
    bool_t charging;

    Statistics vehicleStats;
    SimParams simParams;

    VehicleType_t vehicleType;
};

#endif