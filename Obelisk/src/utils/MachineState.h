#ifndef MACHINE_STATE
#define MACHINE_STATE

#include "settings.h"

#include <RTCModule.h>

#include "utils/TempController.h"

#include "utils/NavManager.h"
#include "utils/Notify.h"

#include "IO.h"



struct State_Settings{
    uint8_t  mode;
    uint32_t startT;
    uint32_t endT;
};

class MachineState{
public:
    MachineState();

    static uint8_t   initialise(void);
    static void      startState(uint8_t state, uint16_t* length = NULL, bool save = true);
    static float     updateStateProgress(void);
    static uint8_t   getState(void);
    static uint32_t  getTimeLeft(void);
private:
    static void _saveState(void);
    static void _loadState(void);

    static float       _timeLeft;
    static State_Settings _state;
};

class StateController{
public:
    StateController();

    static void update(void);
private:
    
};

#endif /* MACHINE_STATE */
