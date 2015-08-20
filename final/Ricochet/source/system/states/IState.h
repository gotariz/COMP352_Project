#ifndef ISTATE_H_INCLUDED
#define ISTATE_H_INCLUDED

#include "general.h"

class IState
{
    public:
        IState(RunState state) : m_state(state) {}
        virtual ~IState(){}

    private: // variables
        RunState m_state;

    public: // variables
        bool loading;

    public: //virtual functions
        virtual void load() = 0;
        virtual bool initialise() = 0;
        virtual void handleEvents() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void freeResources() = 0;

        RunState getStateType() {return m_state;}
};

#endif // ISTATE_H_INCLUDED
