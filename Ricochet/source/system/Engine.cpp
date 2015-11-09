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
        gdata.window->clear(sf::Color::Black);
        activeState->draw();
        draw();
        gdata.window->display();
        running = gdata.running;
    }
}

void Engine::draw()
{
    for (unsigned i =0; i < gdata.achieves.size(); ++i)
    {
        gdata.achieves.at(i)->draw(
                                   (gdata.settings->getScreenWidth() / 2) - 250,        // x pos
                                   (gdata.settings->getScreenHeight() - 120) - (60 * i) // y pos
                                   );
    }
}

void Engine::updateEngine()
{
    time_delta = clock.getDeltaSeconds();
    fps_delta = time_delta;

    unsigned fpsLimit = gdata.settings->getFpsLimit();

    if (fpsLimit == 60)
    {
        time_delta = 0.01666f;
    }
    else if (fpsLimit == 120)
    {
        time_delta = 0.00833f;
    }
    else
    {
        time_delta = (time_delta > 1.f /60) ? 1.f / 60 : time_delta;
    }

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

    for (int i =0; i < static_cast<signed>(gdata.achieves.size()); ++i)
    {
        gdata.achieves.at(i)->update();
        if (gdata.achieves.at(i)->age >= 5)
        {
            delete gdata.achieves.at(i);
            gdata.achieves.erase(gdata.achieves.begin() + i);
            --i;
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
    audio.freeResources();
    assets.freeResources();

    if (activeState)
    {
        activeState->freeResources();
        delete activeState;
        activeState = nullptr;
    }

    gdata.window->close();
}



