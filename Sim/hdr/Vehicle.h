#pragma once

#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include "SimTypes.h"
#include "SimParams.h"
#include "Statistics.h"

#define NUM_VEHICLE_TYPES 5

class Vehicle
{
public:

    enum VehicleType
    {
        ALPHA = 0,
        BRAVO,
        CHARLIE,
        DELTA,
        ECHO,
        INVALID

    };

    Vehicle(SimParams& params);
    ~Vehicle();

    //
    //Name: Update
    //Brief:  Called at each iteration this function updates the vehicles parameters (battery, distance, etc).
    //
    //Param: None
    //
    //Retval: None
    void Update();

    //
    //Name: InitializeVehicle
    //Brief:  Sets the initial values for a vehicle given the vehicle type.
    //
    //Param[in]: VehicleType type
    //
    //Retval: None
    void InitializeVehicle(VehicleType type);

    //
    //Name: ComputeFault
    //Brief:  Calculates whether or not a fault occurred during the time between sim iterations (time steps)
    //
    //Param[in]: float64_t timeElapsed
    //
    //Retval: true if a fault occurred, false otherwise.
    bool_t ComputeFault(float64_t timeElapsed);

    //-------------------------------------------------------------------------------------
    // Setters and Getters.
    //-------------------------------------------------------------------------------------

    //
    //Name: SetCruiseSpeed
    //Brief:  Sets the vehicle cruise speed attribute.
    //
    //Param[in]: uint32_t speed in mph
    //
    //Retval: None
    void SetCruiseSpeed(uint32_t speed)
    {
        cruiseSpeed = speed;
    }

    //
    //Name: GetCruiseSpeed
    //Brief:  Accesses the vehicle cruise speed attribute.
    //
    //Param: None
    //
    //Retval: uint32_t vehicle cruise speed attribute.
    uint32_t GetCruiseSpeed()
    {
        return cruiseSpeed;
    }

    //
    //Name: SetBatteryCapacity
    //Brief:  Sets the total battery capacity attribute
    //
    //Param[in]: uint32_t capacity in kWh
    //
    //Retval: None
    void SetBatteryCapacity(uint32_t capacity)
    {
        batteryCapacity = capacity;
    }

    //
    //Name: GetBatteryCapacity
    //Brief:  Accesses the vehicle total battery capacit.
    //
    //Param: None
    //
    //Retval: vehicle battery capacity.
    uint32_t GetBatteryCapacity()
    {
        return batteryCapacity;
    }

    //
    //Name: SetChargeTime
    //Brief:  Sets the time it takes for the vehicle to fully charge the battery.
    //
    //Param[in]: float64_t time in hours
    //
    //Retval: None
    void SetChargeTime(float64_t time)
    {
        chargeTime = time;
    }

    //
    //Name: GetChargeTime
    //Brief:  Accesses the attribute indicating time required to charge the battery to full.
    //
    //Param: None
    //
    //Retval: vehicle charge time.
    float64_t GetChargeTime()
    {
        return chargeTime;
    }

    //
    //Name: SetEnergyUse
    //Brief:  Sets the vehicle battery usage rate at cruise speed.
    //
    //Param[in]: uint32_t usage in kWh/mile
    //
    //Retval: None
    void SetEnergyUse(float64_t usage)
    {
        energyUse = usage;
    }

    //
    //Name: GetEnergyUse
    //Brief:  Accesses the energy use rate of the vehicle.
    //
    //Param: None
    //
    //Retval: vehicle energy use rate.
    float64_t GetEnergyUse()
    {
        return energyUse;
    }

    //
    //Name: SetNumPassengers
    //Brief:  Sets the vehicle passenger capacity
    //
    //Param[in]: uint32_t passengers
    //
    //Retval: None
    void SetNumPassengers(uint32_t passengers)
    {
        numPassengers = passengers;
    }

    //
    //Name: GetNumPassengers
    //Brief:  Accesses the vehicle passenger capacity attribute.
    //
    //Param: None
    //
    //Retval: vehicle passenger capacity
    uint32_t GetNumPassengers()
    {
        return numPassengers;
    }

    //
    //Name: SetFaultChance
    //Brief:  Sets the vehicle fault chance in probabily of fault per hour.
    //
    //Param[in]: float64_t chance 
    //
    //Retval: None
    void SetFaultChance(float64_t chance)
    {
        faultChance = chance;
    }

    //
    //Name: GetFaultChances
    //Brief:  Accesses the vehicle fault chance attribute
    //
    //Param: None
    //
    //Retval: vehicle fault chance.
    float64_t GetFaultChance()
    {
        return faultChance;
    }

    //
    //Name: GetVehicleStats
    //Brief:  Accesses the vehicle statistics.
    //
    //Param: None
    //
    //Retval: Vehicle statistics 
    Statistics& GetVehicleStats()
    {
        return vehicleStats;
    }

    //
    //Name: SetChargerNeeded
    //Brief:  Sets the flag to indicate if the vehicle needs a charger.
    //
    //Param[in]: bool_t status
    //
    //Retval: None
    void SetChargerNeeded(bool_t status)
    {
        chargerNeeded = status;
    }

    //
    //Name: GetChargerNeeded
    //Brief:  Accesses the flag indicating if the vehicle needs to charge.
    //
    //Param: None
    //
    //Retval: true if a charge is needed, false otherwise.
    bool_t GetChargerNeeded()
    {
        return chargerNeeded;
    }
    
    //
    //Name: SetWaitingForCharger
    //Brief:  Sets the flag to indicate if the vehicle is in line to use a charger.
    //
    //Param[in]: bool_t status
    //
    //Retval: None
    void SetWaitingForCharger(bool_t status)
    {
        waitingForCharger = status;
    }

    //
    //Name: GetWaitingForCharger
    //Brief:  Accesses the flag indicating if the vehicle is in line for a charger.
    //
    //Param: None
    //
    //Retval: true if the vehicle is waiting to charge, false otherwise.
    bool_t GetWaitingForCharger()
    {
        return waitingForCharger;
    }

    //
    //Name: SetChargingComplete
    //Brief:  Sets the flag to indicate if the vehicle is fully charged and can be removed from the charger (charging queue).
    //
    //Param[in]: bool_t status
    //
    //Retval: None
    void SetChargingComplete(bool_t status)
    {
        chargingComplete = status;
    }

    //
    //Name: GetChargingComplete
    //Brief:  Accesses the flag indicating if the vehicle has completed charging.
    //
    //Param: None
    //
    //Retval: true if the vehicle battery is charged, false otherwise
    bool_t GetChargingComplete()
    {
        return chargingComplete;
    }

    //
    //Name: SetChargingStatus
    //Brief:  Sets the flag to indicate if the vehicle is actively charging.
    //
    //Param[in]: bool_t status
    //
    //Retval: None
    void SetChargingStatus(bool_t status)
    {
        charging = status;
    }

    //
    //Name: GetChargingStatus
    //Brief:  Accesses the charging status of the vehicle.
    //
    //Param: None
    //
    //Retval: true if the vehicle is currently charging, false otherwise.
    bool_t GetChargingStatus()
    {
        return charging;
    }

    //
    //Name: SetSimParams
    //Brief:  Sets the simulation parameters used in vehicle calculations.
    //
    //Param[in]: SimParams& params
    //
    //Retval: None
    void SetSimParams(SimParams& params)
    {
        simParams = params;
    }

    //
    //Name: GeVehicleType
    //Brief:  Accesses the vehicle type attribute.
    //
    //Param: None
    //
    //Retval: Vehicle enumeration value.
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