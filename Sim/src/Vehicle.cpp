

#include "Vehicle.h"

Vehicle::Vehicle(SimParams& params) :
    simParams(params)
{
    cruiseSpeed = 0;
    batteryCapacity = 0;
    chargeTime = 0.0;
    energyUse = 0.0;
    numPassengers = 0;
    faultChance = 0.0;

    currentBattery = 0.0;
    charging = false;
    chargerNeeded = false;
    chargingComplete = false;
    waitingForCharger = false;
    vehicleType = VehicleType::INVALID;

}

Vehicle::~Vehicle()
{
    
}

void Vehicle::InitializeVehicle(VehicleType type)
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

//Compute amount of time elapsed since last iteration and check current values vs vehicle capabilities.
void Vehicle::Update()
{
    //Determine what how much things changed over the time step

    //Distance += speed * timeStep (hours)
    //Battery -= energyUse / distance (miles)

    float64_t time_elapsed = simParams.GetTimeStep() / 3600.0; //hours

    if (ComputeFault(time_elapsed))
    {
        vehicleStats.IncrementNumFaults();
    }

    if (charging)
    {
        //amount of battery gained per time step:
        //charging rate = capacity/charge time
        //battery gained = rate * time_elapsed.
        //When battery total >= capacity then charging = false
        float64_t charging_rate = GetBatteryCapacity() / GetChargeTime();
        float64_t charge_gained = charging_rate * time_elapsed;
        currentBattery = currentBattery + charge_gained;
        vehicleStats.SetChargeTime(vehicleStats.GetChargeTime() + time_elapsed);

        if (currentBattery >= GetBatteryCapacity())
        {
            currentBattery = GetBatteryCapacity();
            chargingComplete = true;
        }
    }
    else if (waitingForCharger)
    {
        vehicleStats.SetChargeTime(vehicleStats.GetChargeTime() + time_elapsed);
    }
    else
    {
        float64_t distance = GetCruiseSpeed() * time_elapsed;
        float64_t battery = GetEnergyUse() * distance;  

        //only increase distance if not charging
        vehicleStats.SetFlightDistance(vehicleStats.GetFlightDistance() + distance);
        currentBattery = currentBattery - battery;
        vehicleStats.SetFlightTime(vehicleStats.GetFlightTime() + time_elapsed);
        vehicleStats.SetPassengerMiles(vehicleStats.GetPassengerMiles() + ((float64_t)GetNumPassengers() * distance));

        if (currentBattery <= 0.0)
        {
            //Next time step the vehicle will be on the charger.
            currentBattery = 0.0;
            chargerNeeded = true;
            waitingForCharger = true;
        }
    }
}

bool_t Vehicle::ComputeFault(float64_t timeElapsed)
{
    //Chance of fault per time increment is the fault chance per hour * number of hours elapsed per time increment.
    float64_t fault_chance = GetFaultChance() * timeElapsed;

    return ((float64_t)((float64_t)rand() / (float64_t)RAND_MAX)) < fault_chance;
}