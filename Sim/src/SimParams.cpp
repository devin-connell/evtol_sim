
#include <iostream>
#include <fstream>

#include "SimParams.h"

#define MAX_LINE_LENGTH 256
#define TIME_STEP "TIMESTEP"
#define NUM_VEHICLES "VEHICLES"
#define NUM_CHARGERS "CHARGERS"
#define SIM_DURATION "DURATION"
#define PRESET "PRESET"

SimParams::SimParams()
{
    timeStep = 1.0;
    numVehicles = 20;
    numChargers = 3;
    simDuration = 3;

    simPreset = SimPreset::DEFAULT;
}

SimParams::~SimParams()
{

}

bool_t SimParams::InitializeParameters(string fileName)
{
    fstream cfg_file;
    bool_t status = false;

    cfg_file.open(fileName, ios::in);

    if (cfg_file.is_open())
    {
        string file_line;
        string token;
        string value;
        uint32_t token_position = 0;
        uint16_t error_count = 0;

        while (getline(cfg_file, file_line))
        {
            if (file_line.size() == 0 || file_line[0] == '#')
            {
                continue;
            }

            token_position = (uint32_t)file_line.find('=', 0);
            if (token_position != string::npos)
            {
                token = file_line.substr(0, token_position);
                value = file_line.substr((uint64_t)token_position + 1, string::npos);

                for (uint16_t i = 0; i<token.length(); ++i)
                {
                    token[i] = toupper(token[i]);
                }
                
                if (token.compare(PRESET) == 0)
                {
                    simPreset = (SimPreset)stoul(value, NULL, 10);
                    if (simPreset > SimPreset::NUM_PRESETS)
                    {
                        simPreset = SimPreset::DEFAULT;
                    }
                }
                else if (token.compare(TIME_STEP) == 0)
                {
                    timeStep = (float64_t)stod(value, NULL);
                    if (timeStep > 60)
                    {
                        timeStep = 60;
                    }
                }
                else if (token.compare(NUM_VEHICLES) == 0)
                {
                    numVehicles = (uint32_t)stoul(value, NULL, 10);
                    if (numVehicles > 100)
                    {
                        numVehicles = 100;
                    }
                }
                else if (token.compare(NUM_CHARGERS) == 0)
                {
                    numChargers = (uint32_t)stoul(value, NULL, 10);
                }
                else if (token.compare(SIM_DURATION) == 0)
                {
                    simDuration = (uint32_t)stoul(value, NULL, 10);
                    if (simDuration > 24)
                    {
                        simDuration = 24;
                    }
                }
                else
                {
                    cout << "WARNING: Invalid configuration entry" << endl;
                    error_count++;
                }

            }
            else
            {
                cout << "WARNING: Invalid token" << endl;
                error_count++;
            }
        }

        if (error_count == 0)
        {
            status = true;
        }
    }

    return status;
}
