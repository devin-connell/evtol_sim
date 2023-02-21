
#include <iostream>

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
        cout << "Simulation Executing..." << endl;
        evtol_sim.RunSim();
    }
    else
    {
        cout << "An Error has occurred, check executable location and configuration file name and location." << endl;
    }

    evtol_sim.ComputeStatistics();

    evtol_sim.PrintStatistics();

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}

