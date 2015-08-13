#include "InputHandler.h"

InputHandler::InputHandler()
{
    //ctor
}

InputHandler::~InputHandler()
{
    //dtor
}

void InputHandler::init()
{
	zoomin = gdata.keys[SDL_SCANCODE_EQUALS];
	zoomout = gdata.keys[SDL_SCANCODE_MINUS];

	cameraL = gdata.keys[SDL_SCANCODE_LEFT];
	cameraR = gdata.keys[SDL_SCANCODE_RIGHT];
	cameraU = gdata.keys[SDL_SCANCODE_UP];
	cameraD = gdata.keys[SDL_SCANCODE_DOWN];
}

void InputHandler::handleEvents()
{

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
		if (event.type == SDL_QUIT)
			gdata.running = false;
    }
	
	// update bound keys
	gdata.updateKeys();

	SDL_GetMouseState(&mx, &my);

	// update 
    handlePlayerEvents();

    handleMouseEvents();
    //handleKeybordEvents();
    handleControllerEvents();

    debug_events();

    m_player->setMoveDirection(Vector2(m_rawVelocity));
}

void InputHandler::handlePlayerEvents()
{
    float h = 0;
    float v = 0;

	if (gdata.keys[SDL_SCANCODE_MOUSE_LEFT]->isKeyPressed)
	{

		s_pos = Vector2(mx,gdata.settings->getScreenHeight() - my);
	}

	if (gdata.keys[SDL_SCANCODE_MOUSE_LEFT]->isKeyDown)
	{
		//Vector2 playerPosition = m_player->getAbsolutePosition();
		//playerPosition = gdata.toPixels(playerPosition.x - gdata.camera->m_x, playerPosition.y - gdata.camera->m_y);

		e_pos = Vector2(mx, gdata.settings->getScreenHeight() - my);
	}

	if (gdata.keys[SDL_SCANCODE_MOUSE_LEFT]->isKeyReleased)
	{
		Vector2 velocity = s_pos - e_pos;
		velocity /= WORLD_SCALE;
		velocity *= 10;
		m_player->applyImpulse(velocity);
	}
}

void InputHandler::debug_events()
{
    //if (gdata.kbKeys.at(sf::Keyboard::Escape).isKeyPressed)  gdata.m_bridge.running = false;

    //zoom TODO: set scale of assets
	if (zoomin->isKeyDown)		if ((gdata.zoom += 1 * gdata.m_timeDelta) > 3) gdata.zoom = 3;
	if (zoomout->isKeyDown)		if ((gdata.zoom -= 1 * gdata.m_timeDelta) < 0.1) gdata.zoom = 0.1;

	if (cameraU->isKeyDown)			gdata.camera->m_y += 5.0f * (3 - gdata.zoom) * gdata.m_timeDelta;
	if (cameraD->isKeyDown)			gdata.camera->m_y += -5.0f * (3 - gdata.zoom) * gdata.m_timeDelta;
	if (cameraL->isKeyDown)			gdata.camera->m_x += -5.0f * (3 - gdata.zoom) * gdata.m_timeDelta;
	if (cameraR->isKeyDown)			gdata.camera->m_x += 5.0f * (3 - gdata.zoom) * gdata.m_timeDelta;
}

void InputHandler::handleMouseEvents()
{
    //if (lastUsed == 0)
    //{
    //    Vector2 mousePosition = Vector2(sf::Mouse::getPosition(*gdata.m_window).x,sf::Mouse::getPosition(*gdata.m_window).y);

    //    Vector2 playerPosition = m_player->getAbsolutePosition();
    //    playerPosition = gdata.toPixels(playerPosition.x - gdata.m_camera->m_x, playerPosition.y - gdata.m_camera->m_y);

    //    Vector2 distance = mousePosition - playerPosition;


    //    m_player->setRotation( Utils::convertToAngle(360 - distance.getAngle() - 90) );
    //}
}

void InputHandler::handleControllerEvents()
{
    //js_move = false;

    //float jsleft_x = 0;
    //float jsleft_y = 0;
    //float jsright_x = 0;
    //float jsright_y = 0;

    //if (sf::Joystick::isConnected(0))
    //{
    //    jsleft_x = sf::Joystick::getAxisPosition(0,sf::Joystick::X);
    //    jsleft_y = sf::Joystick::getAxisPosition(0,sf::Joystick::Y);
    //    jsright_x = sf::Joystick::getAxisPosition(0,sf::Joystick::U);
    //    jsright_y = sf::Joystick::getAxisPosition(0,sf::Joystick::R);
    //}

    //    float deadzone = 25;

    //    float xjs = jsleft_x;
    //    float yjs = 0 - jsleft_y;

    //    float joystick_distance = sqrt( (xjs * xjs) + (yjs * yjs) );

    //    if (joystick_distance > deadzone)
    //    {
    //        js_move = true;
    //        m_rawVelocity.Set(xjs,yjs);
    //        float nx = xjs / m_rawVelocity.Length();
    //        float ny = yjs / m_rawVelocity.Length();
    //        m_rawVelocity.Set(nx,ny);
    //        //gz::print_value("rv:",m_rawVelocity.Length());
    //    }

    //    deadzone = 50;

    //    float xs = 0 - jsright_x;
    //    float ys = 0 - jsright_y;

    //    float distance = sqrt( (xs * xs) + (ys * ys) );

    //    if (distance > deadzone)
    //    {
    //        float joyu = sf::Joystick::getAxisPosition(0,sf::Joystick::U);
    //        float joyr = 0 - sf::Joystick::getAxisPosition(0,sf::Joystick::R);

    //        // calculate direction to face using mouse pointer
    //        m_rawRotation = atan2( joyr, joyu) * 180.f / PI;
    //        m_player->setRotation(m_rawRotation);
    //        lastUsed = 1;

    //    }
}

