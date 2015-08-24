#include "Engine.h"

Engine::Engine()
{
    //ctor
}

Engine::~Engine()
{
    //dtor
}

void Engine::run()
{
	gzClock clock;
	clock.getDeltaSeconds();
    // check to switch states
    while(running)
    {
		double delta = clock.getDeltaSeconds();

		// calculate fps
		double fps = 1.f / delta;
		string title = "fps" + gz::toString(fps);
		gdata.window->setTitle( title.c_str() );
		gdata.m_timeDelta = delta;

        // update mouse position
        sf::Vector2i mp = sf::Mouse::getPosition(*gdata.window);
        gdata.mouse.x = mp.x;
        gdata.mouse.y = gdata.window->getSize().y - mp.y;
        gdata.mouse_raw.x = mp.x;
        gdata.mouse_raw.y = mp.y;

        updateState();

        activeState->handleEvents();
        activeState->update();
        activeState->draw();
        running = gdata.running;

		sf::sleep(sf::milliseconds(1));
    }
}

void Engine::updateState()
{
    if (!activeState || activeState->getStateType() != gdata.gamestate)
    {
        if (activeState) // delete the active state then create the new one
        {
            activeState->freeResources();
            delete activeState;
            activeState = nullptr;
        }

        if (gdata.gamestate == RunState::STATE_GAME)
        {
            IState* stateGame = new StateGame();
            stateGame->initialise();
            activeState = stateGame;
        }
		else if (gdata.gamestate == RunState::STATE_MENU)
        {
            IState* stateMenu = new StateMenu();
            stateMenu->initialise();
            activeState = stateMenu;
        }
    }
}

bool Engine::initialise()
{
    running = true;
    return true;
}

void Engine::exit()
{
    gdata.window->close();

    if (activeState)
    {
        activeState->freeResources();
        delete activeState;
        activeState = nullptr;
    }

	//Destroy window
	//SDL_DestroyWindow(gdata.window);

	//Quit SDL subsystems
	//SDL_Quit();
}


