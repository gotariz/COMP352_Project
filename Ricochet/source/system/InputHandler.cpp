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

    if (!gdata.window->hasFocus()) return;

    handlePlayerEvents();
    handleMouseEvents();
    handleControllerEvents();

    debug_events();

	if (gdata.keys[sf::Keyboard::R].isKeyPressed)
	{
		gdata.reload = true;
		gdata.show_progress = false;
		gdata.replay_level = false;
	}

	if(gdata.keys[sf::Keyboard::Comma].isKeyPressed)
    {
        gdata.level -= 1;
        gdata.reload = true;
        gdata.show_progress = false;
        gdata.replay_level = false;
        gdata.shotData.clear();
    }

    if(gdata.keys[sf::Keyboard::Period].isKeyPressed)
    {
        gdata.level += 1;
        gdata.reload = true;
        gdata.show_progress = false;
        gdata.replay_level = false;
        gdata.shotData.clear();
    }

    if(gdata.keys[sf::Keyboard::D].isKeyPressed)
    {
        gdata.draw_debug = !gdata.draw_debug;
    }
    if(gdata.keys[sf::Keyboard::G].isKeyPressed)
    {
        gdata.draw_grid = !gdata.draw_grid;
    }

    if(gdata.keys[sf::Keyboard::Escape].isKeyPressed)
    {
        gdata.gamestate = STATE_MENU;
        gdata.show_progress = false;
        gdata.replay_level = false;
        gdata.shotData.clear();
        cout << "Back to menu"<< endl;
    }
}

void InputHandler::handlePlayerEvents()
{
    if (!m_player) return;

    // check to see if mouse is hovering
    s_pos = gdata.toScreenPixels(m_player->getAbsolutePosition());
    s_pos.y = gdata.window->getSize().y - s_pos.y;

    Vector2 d = gdata.mouse - s_pos;
    if (d.getMagnitude() <= (0.5 * WORLD_SCALE * gdata.zoom))
    {
        if (!m_player->hover)
        {
            m_player->hover = true;
            m_player->shrink_thickness = m_player->circle.getOutlineThickness();
        }
    }
    else
    {
        m_player->hover = false;
    }

    if (gdata.keys[KEY_MOUSE_RIGHT].isKeyPressed)
    {
        if (selecting && !launched)
            angle_lock = !angle_lock;
    }

    if (gdata.keys[sf::Keyboard::Space].isKeyPressed)
    {
        angle_snap = angle_snap == 1 ? 0 : 1;
        gdata.angle_snap = angle_snap;
    }

    if (gdata.keys[sf::Keyboard::F1].isKeyPressed)
    {
        gdata.show_help = !gdata.show_help;
    }

    if (gdata.keys[sf::Keyboard::C].isKeyPressed)
    {
        gdata.random_colors = !gdata.random_colors;
    }

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
                m_player->shot = true;
                //power = 10;
            }
        }
	}

	if (gdata.keys[KEY_MOUSE_LEFT].isKeyDown)
	{
	    if (selecting)
        {
            if (!angle_lock)
            {
                e_pos = gdata.mouse;
                // don't allow for zero velocity
                if (e_pos == s_pos) ++e_pos.y;

                vel = s_pos - e_pos;
                vel.setMagnitude(vel.getMagnitude());

                if (vel.getMagnitude() > max_dist) vel.setMagnitude(max_dist);
                if (vel.getMagnitude() < min_dist) vel.setMagnitude(min_dist);

                float vel_percent = vel.getMagnitude() / max_dist;
                float speed = m_player->maxSpeed * vel_percent;
                vel.setMagnitude( speed );
                if (angle_snap > 0)
                {
                    float a = utils::roundNearest(vel.getAngle(),angle_snap);
                    Vector2 newVel(speed,0);
                    newVel.rotate(a);
                    vel = newVel;
                }


                power = utils::roundNearest(vel_percent*100,1);
                angle = vel.getAngle();
                m_player->angle = angle;
                m_player->power = power;
            }
            else
            {
                Vector2 m = s_pos - gdata.mouse;
                // don't change the angle just change the magnitude
                if (m.getMagnitude() > max_dist)        vel.setMagnitude(max_dist);
                else if (m.getMagnitude() < min_dist)   vel.setMagnitude(min_dist);
                else                                    vel.setMagnitude(m.getMagnitude());

                float vel_percent = vel.getMagnitude() / max_dist;
                vel.setMagnitude( m_player->maxSpeed * vel_percent );

                power = utils::roundNearest(vel_percent*100,1);
                angle = vel.getAngle();
                m_player->power = power;
                m_player->angle = angle;
            }
	    }
	}

	if (gdata.keys[KEY_MOUSE_LEFT].isKeyReleased)
	{
	    if (selecting && !launched)
		{
		    m_player->shootPlayer();
		    //m_player->currentSpeed = vel.getMagnitude();
            //m_player->trail.addPoint( m_player->getAbsolutePosition() );
            //m_player->setLinearVelocity(vel);
            //m_player->trail.length = MAX_TAIL_LENGTH * (vel.getMagnitude() / m_player->maxSpeed);

		    launched = true;
		    selecting = false;
		    gdata.last_angle = vel.getAngle();
		    gdata.first_shot = false;

		    Vector2 dir(50,0);
		    dir.rotate(vel.getAngle());
		    gdata.p1 = m_player->getAbsolutePosition();
		    gdata.p2 = gdata.p1 + dir;

		    gdata.audio->playSound("shoot",true);

		    // need to keep track for direction, speed and time
		    BallShotData bsd(timer,vel.getAngle(),power);
		    gdata.shotData.push_back(bsd);
		    cout << "timer:" << timer << endl;
		}
	}
}

void InputHandler::debug_events()
{
    //if (gdata.kbKeys.at(sf::Keyboard::Escape).isKeyPressed)  gdata.m_bridge.running = false;

    //zoom TODO: set scale of assets
//	if (zoomin->isKeyDown)		if ((gdata.zoom += 1 * gdata.m_timeDelta) > 3) gdata.zoom = 3;
//	if (zoomout->isKeyDown)		if ((gdata.zoom -= 1 * gdata.m_timeDelta) < 0.1) gdata.zoom = 0.1;
//
//	if (cameraU->isKeyDown)			gdata.camera->y += 5.0f * (3 - gdata.zoom) * gdata.m_timeDelta;
//	if (cameraD->isKeyDown)			gdata.camera->y += -5.0f * (3 - gdata.zoom) * gdata.m_timeDelta;
//	if (cameraL->isKeyDown)			gdata.camera->x += -5.0f * (3 - gdata.zoom) * gdata.m_timeDelta;
//	if (cameraR->isKeyDown)			gdata.camera->x += 5.0f * (3 - gdata.zoom) * gdata.m_timeDelta;
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

