#ifndef ANIMATION_H
#define ANIMATION_H

#include "general.h"

#include "system/GameData.h"

#include "animation/AnimationInstruction.h"
#include "entities/Object.h" // fix this

class Object;

class Animation
{
    public:
        Animation();
        virtual ~Animation();

    private: // variables

        bool    m_isRunning = false;
        bool    m_isEnded = false;

        Object*                             m_object = nullptr;
        std::vector<AnimationInstruction*>  m_actions;

    public: // variables

        bool getIsRunning() {return m_isRunning;}
        bool getIsEnded() {return m_isEnded;}

        std::string m_name;
        GameData*   gdata;
        unsigned    m_loops = 0;
        float       m_duration = 0; // milliseconds

        unsigned    m_elapsedLoops = 0;
        float       m_elapsedDuration = 0;

        bool        m_reset = false;
        Vector2     m_resetPosition;
        float       m_resetRotation = 0;

        bool        m_startPositionRelative = false;

        void setInstructions(std::vector<AnimationInstruction*> actions);
        std::vector<AnimationInstruction*> getInstructions();

    public: // functions

        void    start();
        void    pause();
        void    resume();
        void    hardReset();
        void    softReset();

        void    update();

        void    addAction(AnimationInstruction* ai);
        void    setObject(Object* obj);


};

#endif // ANIMATION_H
