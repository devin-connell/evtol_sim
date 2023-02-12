

#include "Vehicle.h"

Vehicle::Vehicle()
{
    cruiseSpeed = 0;
    batteryCapacity = 0;
    chargeTime = 0.0;
    energyUse = 0.0;
    numPassengers = 0;
    faultChance = 0.0;

    numFaults = 0;
    currentBattery = 0.0;

}

Vehicle::~Vehicle()
{
    
}

void Vehicle::InitializeVehicle(VehicleType_t type)
{
    vehicleType = type;
    switch (vehicleType)
    {
    case ALPHA:
    {
        SetCruiseSpeed(120);
        SetBatteryCapacity(320);
        SetChargeTime(0.6);
        SetEnergyUse(1.6);
        SetNumPassengers(4);
        SetFaultChance(0.25);
        currentBattery = GetBatteryCapacity();
        charging = false;

        break;
    }

    case BRAVO:
    {
        SetCruiseSpeed(100);
        SetBatteryCapacity(100);
        SetChargeTime(0.2);
        SetEnergyUse(1.5);
        SetNumPassengers(5);
        SetFaultChance(0.1);
        currentBattery = GetBatteryCapacity();
        charging = false;

        break;
    }

    case CHARLIE:
    {
        SetCruiseSpeed(160);
        SetBatteryCapacity(220);
        SetChargeTime(0.8);
        SetEnergyUse(2.2);
        SetNumPassengers(3);
        SetFaultChance(0.05);
        currentBattery = GetBatteryCapacity();
        charging = false;

        break;
    }

    case DELTA:
    {
        SetCruiseSpeed(90);
        SetBatteryCapacity(120);
        SetChargeTime(0.62);
        SetEnergyUse(0.8);
        SetNumPassengers(2);
        SetFaultChance(0.22);
        currentBattery = GetBatteryCapacity();
        charging = false;

        break;
    }

    case ECHO:
    {
        SetCruiseSpeed(30);
        SetBatteryCapacity(150);
        SetChargeTime(0.3);
        SetEnergyUse(5.8);
        SetNumPassengers(2);
        SetFaultChance(0.61);
        currentBattery = GetBatteryCapacity();
        charging = false;

        break;
    }

    case INVALID:
    default:
    {
        SetCruiseSpeed(0);
        SetBatteryCapacity(0);
        SetChargeTime(0.0);
        SetEnergyUse(0.0);
        SetNumPassengers(0);
        SetFaultChance(0.0);
        currentBattery = GetBatteryCapacity();
        charging = false;

        break;
    }

    } // END SWITCH
}

//Increment time step and check current values vs vehicle capabilities.
void Vehicle::Update()
{
    
}