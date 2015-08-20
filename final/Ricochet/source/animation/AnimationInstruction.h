#ifndef ANIMATIONINSTRUCTION_H
#define ANIMATIONINSTRUCTION_H

#include "general.h"

class Animation;

class AnimationInstruction
{
    friend class Animation;
    public:
        AnimationInstruction();
        virtual ~AnimationInstruction();

    private:

        bool        m_isStarted = false;
        bool        m_isRunning = false;
        bool        m_isFinished = false;

    public:

        bool        m_relativeStartPosition = false;
        bool        m_relativeStartRotation = false;
        bool        m_relativeEndPosition = false;
        bool        m_relativeEndRotation = false;

        unsigned    m_loops = 0;
        float       m_startTime = 0;
        float       m_duration = 0; // milliseconds

        float       m_startRotation = 0;
        float       m_endRotation = 0;
        Vector2     m_startPosition;
        Vector2     m_endPosition;

        float       m_elapsedLoops = 0;
        float       m_elapsedDuration = 0;

        Vector2     m_absoluteStartPosition;
        Vector2     m_absoluteEndPosition;
        float       m_absoluteStartRotation;
        float       m_absoluteEndRotation;

        int         m_rotationMethod = 1; // 0=quickest, 1=clockwise, 2=anticlockwise

    public:

        bool        getIsStarted();
        bool        getIsRunning();
        void        hardReset();
        void        softReset();
};

#endif // ANIMATIONINSTRUCTION_H
