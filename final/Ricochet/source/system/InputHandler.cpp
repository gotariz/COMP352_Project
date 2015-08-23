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
	zoomin = &gdata.keys[sf::Keyboard::Equal];
	zoomout = &gdata.keys[sf::Keyboard::Dash];

	cameraL = &gdata.keys[sf::Keyboard::Left];
	cameraR = &gdata.keys[sf::Keyboard::Right];
	cameraU = &gdata.keys[sf::Keyboard::Up];
	cameraD = &gdata.keys[sf::Keyboard::Down];
}

void InputHandler::handleEvents()
{

    sf::Event event;
    while (gdata.window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            gdata.running = false;
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            gdata.mouse.x = event.mouseMove.x;
            gdata.mouse.y = gdata.window->getSize().y - event.mouseMove.y;
        }
    }

	// update bound keys
	gdata.updateKeys();
    handlePlayerEvents();
    handleMouseEvents();
    handleControllerEvents();

    debug_events();

	if (gdata.keys[sf::Keyboard::R].isKeyPressed)
	{
		//m_player->setLinearVelocity(Vector2(0, 0));
		//m_player->setAbsolutePosition(m_player->restart_pos);
		cout << "restarted" << endl;
	}
}

void InputHandler::handlePlayerEvents()
{
    float h = 0;
    float v = 0;

	if (gdata.keys[KEY_MOUSE_LEFT].isKeyPressed)
	{

		s_pos = Vector2(gdata.mouse.x,gdata.settings->getScreenHeight() - gdata.mouse.y);
	}

	if (gdata.keys[KEY_MOUSE_LEFT].isKeyDown)
	{
		Vector2 playerPosition = m_player->getAbsolutePosition();
		playerPosition = gdata.toPixels(playerPosition.x - gdata.camera->x, playerPosition.y - gdata.camera->y);

		e_pos = Vector2(gdata.mouse.x, gdata.settings->getScreenHeight() - gdata.mouse.y);
	}

	if (gdata.keys[KEY_MOUSE_LEFT].isKeyReleased)
	{
		Vector2 velocity = s_pos - e_pos;
		velocity.y *= -1;

		float d = velocity.getMagnitude();
		if (d > 500) d = 500;
		d /= 500;

		velocity.normalise();
		velocity.setMagnitude( 25.f * d );

		cout << "vel=" << 25.f * d << endl;



		if (velocity.getMagnitude() > 25)       velocity.setMagnitude(25);
		else if (velocity.getMagnitude() < 5)   velocity.setMagnitude(5);
		//m_player->m_physicsObject->ApplyLinearImpulse(velocity.toBulletVector(),b2Vec2(0,0),true);
		//m_player->setLinearVelocity(Vector2(0,0));
		//m_player->applyImpulse(velocity);
		m_player->setLinearVelocity(velocity);
		//velocity.print("vel:");
	}
}

void InputHandler::debug_events()
{
    //if (gdata.kbKeys.at(sf::Keyboard::Escape).isKeyPressed)  gdata.m_bridge.running = false;

    //zoom TODO: set scale of assets
	if (zoomin->isKeyDown)		if ((gdata.zoom += 1 * gdata.m_timeDelta) > 3) gdata.zoom = 3;
	if (zoomout->isKeyDown)		if ((gdata.zoom -= 1 * gdata.m_timeDelta) < 0.1) gdata.zoom = 0.1;

	if (cameraU->isKeyDown)			gdata.camera->y += 5.0f * (3 - gdata.zoom) * gdata.m_timeDelta;
	if (cameraD->isKeyDown)			gdata.camera->y += -5.0f * (3 - gdata.zoom) * gdata.m_timeDelta;
	if (cameraL->isKeyDown)			gdata.camera->x += -5.0f * (3 - gdata.zoom) * gdata.m_timeDelta;
	if (cameraR->isKeyDown)			gdata.camera->x += 5.0f * (3 - gdata.zoom) * gdata.m_timeDelta;
}

void InputHandler::handleMouseEvents()
{
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

