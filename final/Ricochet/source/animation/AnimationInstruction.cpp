#include "AnimationInstruction.h"

AnimationInstruction::AnimationInstruction()
{
    //ctor
}

AnimationInstruction::~AnimationInstruction()
{
    //dtor
}


bool AnimationInstruction::getIsStarted()
{
    return m_isStarted;
}

bool AnimationInstruction::getIsRunning()
{
    return m_isRunning;
}

void AnimationInstruction::hardReset()
{
    m_isStarted = false;
    m_elapsedLoops = 0;
    m_elapsedDuration = 0;
}

void AnimationInstruction::softReset()
{
    m_isStarted = false;
    m_elapsedDuration = 0;
}
