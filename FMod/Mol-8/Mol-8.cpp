

#include <math.h>
#include "stdafx.h"
#include <iostream>
#include <conio.h> 
#include <stdio.h>
#include <windows.h>
#include "inc\fmod.hpp"
#include "inc\fmod_errors.h"
//#include "fmod_dsp.h"
//#include "fmod_errors.h"
#pragma comment(lib, "fmodex_vc.lib")
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    FMOD::System* system;
    FMOD::System_Create(&system);
    system->init(16, FMOD_INIT_NORMAL, 0);
    FMOD::Sound* sound;
    FMOD::Channel* channel = NULL;
    FMOD::DSP* dspecho = 0;
    int               key = 0;
    unsigned int      version;
    FMOD_RESULT res = system->set3DSettings(100, 0.123, -0.1);
    res = system->getVersion(&version);
    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        return 0;
    }
    res = system->createSound("ASAP.mp3", FMOD_SOFTWARE, 0, &sound);
    printf("Press SPACE to paused/unpause sound.\n");
    printf("Press 1 to toggle dspecho effect.\n");
    printf("Press 'Esc' to quit\n");
    printf("\n");
    res = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
    res = system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dspecho);
    do
    {
        if (_kbhit())
        {
            key = _getch();

            switch (key)
            {
            case ' ':
            {
                bool paused;
                channel->getPaused(&paused);
                paused = !paused;
                res = channel->setPaused(paused);
                break;
            }
            case '1':
            {
                bool active;
                res = dspecho->getActive(&active);
                if (active)
                {
                    res = dspecho->remove();
                }
                else
                {
                    res = system->addDSP(dspecho, 0);
                    res = dspecho->setParameter(FMOD_DSP_ECHO_DELAY, 50.0f);
                }
                break;
            }
            }
        }

        system->update();

        {
            bool paused = 0;
            bool dspecho_active;
            dspecho->getActive(&dspecho_active);
            if (channel)
            {
                res = channel->getPaused(&paused);
                if ((res != FMOD_OK) && (res != FMOD_ERR_INVALID_HANDLE) && (res != FMOD_ERR_CHANNEL_STOLEN))
                {
                    std::cout << "pauseerror\n";
                }
            }

            printf("%s : echo[%c] \r",
                paused ? "Paused " : "Playing",
                dspecho_active ? 'x' : ' '
            );
        }

        Sleep(10);

    } while (key != 27);
    printf("\n");
    res = sound->release();
    res = system->close();
    res = system->release();
    return 0;
}
