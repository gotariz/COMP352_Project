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
    }

	// update bound keys
	gdata.updateKeys();
    handlePlayerEvents();
    handleMouseEvents();
    handleControllerEvents();

    debug_events();

	if (gdata.keys[sf::Keyboard::R].isKeyPressed)
	{
		m_player->setLinearVelocity(Vector2(0, 0));
		m_player->setAbsolutePosition(m_player->reset_pos);
		m_player->trail.clearTrail();
		launched = false;
		selecting = false;
		cout << "restarted" << endl;
	}
}

void InputHandler::handlePlayerEvents()
{
    float h = 0;
    float v = 0;

	if (gdata.keys[KEY_MOUSE_LEFT].isKeyPressed)
	{
	    if (!launched)
        {
            s_pos = gdata.toScreenPixels(m_player->getAbsolutePosition());
            s_pos.y = gdata.window->getSize().y - s_pos.y;
            Vector2 d = gdata.mouse - s_pos;
            if (d.getMagnitude() <= (0.5 * WORLD_SCALE * gdata.zoom))
            {
                selecting = true;
            }
        }
	}

	if (gdata.keys[KEY_MOUSE_LEFT].isKeyDown)
	{
        if (selecting && !launched)
		{
		    e_pos = gdata.mouse;
            velocity = s_pos - e_pos;
            angle = velocity.getAngle();

            float dist = velocity.getMagnitude();
            if (dist > pullbackDistance) dist = pullbackDistance;

            power = static_cast<int>((dist / pullbackDistance) * 100);
            float percent = power / 100.f;

            velocity.normalise();
            //angle = velocity.getAngle();
            velocity.set(1,0);
            velocity.rotate(angle);
            velocity.setMagnitude( m_player->maxSpeed * percent );
		}
	}

	if (gdata.keys[KEY_MOUSE_LEFT].isKeyReleased)
	{
	    if (selecting && !launched)
		{
		    velocity = s_pos - e_pos;
		    angle = velocity.getAngle();

            float dist = velocity.getMagnitude();
            if (dist > pullbackDistance) dist = pullbackDistance;

            power = static_cast<int>((dist / pullbackDistance) * 100);
            float percent = power / 100.f;

            velocity.normalise();
            //angle = velocity.getAngle();
            velocity.set(1,0);
            velocity.rotate(angle);
            velocity.setMagnitude( m_player->maxSpeed * percent );


            m_player->currentSpeed = velocity.getMagnitude();
            m_player->trail.addPoint( m_player->getAbsolutePosition() );
            m_player->setLinearVelocity(velocity);
            m_player->trail.length = MAX_TAIL_LENGTH * (velocity.getMagnitude() / m_player->maxSpeed);
            selecting = false;
            launched = true;
		}
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

