#include "States.h"


bool States::GetPausedState()
{
    return States::bPaused;
}

void States::SetPausedState(bool bState)
{
    bPaused = bState;
}
