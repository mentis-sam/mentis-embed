#ifndef MACHINE_STATE
#define MACHINE_STATE

#include "settings.h"

#include "modules/RTCModule.h"
#include "utils/NavManager.h"
#include "utils/TempController.h"

#include "IO.h"

enum State { none, colonisation , fruiting , dehydration };

class MachineState{
public:
    MachineState();

    static uint8_t initialise(void);
    static void    startState(uint8_t state, DateTime length);
    static float   getStateProgress(void);
    static uint8_t getState(void);
private:
    static void _saveState(void);
    static void _loadState(void);

    static uint8_t  _state;
    static uint32_t _stateStart;
    static uint32_t _stateEnd;
};

class StateController{
public:
    StateController();

    static void update(void);
private:
    
};

#endif /* MACHINE_STATE */
