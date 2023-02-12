


#include "SimParams.h"

SimParams::SimParams()
{
    timeStep = 0.0;
    numVehicles = 0;
    numChargers = 0;
    simDuration = 0;

    simPreset = SimPreset::INVALID;
}

SimParams::~SimParams()
{

}

void SimParams::InitializeParameters(string fileName)
{
    
}
