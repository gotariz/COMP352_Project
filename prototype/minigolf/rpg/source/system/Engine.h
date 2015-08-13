#ifndef ENGINE_H
#define ENGINE_H

#include "general.h"

#include "system/GameData.h"
#include "system/Settings.h"
#include "system/states/IState.h"
#include "system/states/StateGame.h"

class Engine
{
    public:
        Engine();
        virtual ~Engine();

    private: // private member variables
        IState*     activeState = nullptr;

    public: // public member variables
        bool running;
		Settings	settings;

    public:
        void run();
        bool initialise();
        void updateState();
        void exit();
};

#endif // ENGINE_H
