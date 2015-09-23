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
	clock.getDeltaSeconds();
    // check to switch states
    while(running)
    {
        updateEngine();
        activeState->handleEvents();
        activeState->update();
        activeState->draw();
        running = gdata.running;
    }
}

void Engine::updateEngine()
{
    time_delta = clock.getDeltaSeconds();
    fps_delta = time_delta;

    // calculate fps
    time_delta = (time_delta > 1.f /60) ? 1.f / 60 : time_delta;
    double fps = 1.f / fps_delta;
    string title = "fps" + gz::toString(fps);
    gdata.window->setTitle( title.c_str() );
    gdata.m_timeDelta = time_delta;

    // update mouse position
    sf::Vector2i mp = sf::Mouse::getPosition(*gdata.window);
    gdata.mouse.x = mp.x;
    gdata.mouse.y = gdata.window->getSize().y - mp.y;
    gdata.mouse_raw.x = mp.x;
    gdata.mouse_raw.y = mp.y;

    audio.update();

    if (gdata.countdown > 0)
    {
        gdata.countdown -= time_delta;
        if (gdata.countdown <= 0)
        {
            gdata.countdown = 0;
            gdata.reload = true;
        }
    }

    updateState();
}


void Engine::updateState()
{
    if (!activeState || activeState->getStateType() != gdata.gamestate || gdata.reload)
    {

        if (gdata.reload && activeState) // delete the active state then create the new one
        {
            activeState->freeResources();
            delete activeState;
            activeState = nullptr;
        }
        gdata.reload = false;

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
    assets.loadAssetList("data/assets.xml");
	gdata.assets = &assets;
	gdata.audio = &audio;
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

    assets.freeResources();
    audio.freeResources();
}



