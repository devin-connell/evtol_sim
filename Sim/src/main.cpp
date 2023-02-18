


#include "SimTypes.h"
#include "SimParams.h"
#include "Simulation.h"


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

    return 0;
}
