
#include "SimTypes.h"
#include "SimParams.h"
#include "Simulation.h"
#include "Statistics.h"


int main()
{
    bool_t sim_ready = false;
    SimParams simulationParameters;
    Simulation evtol_sim(simulationParameters);
    simulationParameters.InitializeParameters("..\\cfg\\sim_params.cfg");
    
    sim_ready = evtol_sim.InitSim();
    
    if (sim_ready)
    {
        evtol_sim.RunSim();
    }

    evtol_sim.ComputeStatistics();

    evtol_sim.PrintStatistics();

    return 0;
}

