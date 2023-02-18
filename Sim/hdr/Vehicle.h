#pragma once

#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include "SimTypes.h"
#include "SimParams.h"
#include "Statistics.h"

class Vehicle
{
public:

    enum VehicleType
    {
        INVALID = 0,
        ALPHA,
        BRAVO,
        CHARLIE,
        DELTA,
        ECHO

    };

    Vehicle(SimParams& params);
    ~Vehicle();

    void Update();

    void InitializeVehicle(VehicleType type);

    bool_t ComputeFault(float64_t timeElapsed);

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

    void SetChargerNeeded(bool_t status)
    {
        chargerNeeded = status;
    }

    bool_t GetChargerNeeded()
    {
        return chargerNeeded;
    }
    
    void SetWaitingForCharger(bool_t status)
    {
        waitingForCharger = status;
    }

    bool_t GetWaitingForCharger()
    {
        return waitingForCharger;
    }

    void SetChargingComplete(bool_t status)
    {
        chargingComplete = status;
    }

    bool_t GetChargingComplete()
    {
        return chargingComplete;
    }

    void SetChargingStatus(bool_t status)
    {
        charging = status;
    }

    bool_t GetChargingStatus()
    {
        return charging;
    }

    VehicleType GetVehicleType()
    {
        return vehicleType;
    }


private:

    uint32_t cruiseSpeed;               //! Maximum speed of the vehicle in miles per hour
    uint32_t batteryCapacity;           //! Maximum battery capacity
    float64_t chargeTime;               //! Time in hours to reach full battery
    float64_t energyUse;                //! Rate of battery drain at cruise speed per hour
    uint32_t numPassengers;             //! Passenger capacity, always full
    float64_t faultChance;              //! Probability of fault per hour

    float64_t currentBattery;           //! Battery level, determined as function of time and usage rate.
    bool_t charging;                    //! True when the vehicle is charging, distance is not updated during this time.
    bool_t chargerNeeded;               //! Signals to the simulation that this vehicle needs to connect to a charger
    bool_t chargingComplete;            //! Signals the simulation that this vehicle is done charging and can be removed from a charger queue
    bool_t waitingForCharger;           //! Indicates this vehicle is still waiting for a charger to be available.

    Statistics vehicleStats;
    SimParams& simParams;

    VehicleType vehicleType;
};

#endif