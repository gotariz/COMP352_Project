#include "StateGame.h"

StateGame::StateGame() : IState(STATE_GAME)
{
    //ctor
}

StateGame::~StateGame()
{
    //dtor
}

void StateGame::reload()
{

}

void StateGame::reInit()
{
    gdata.settings->setScreenWidth(1920);
    gdata.settings->setScreenHeight(1080);

    gdata.settings->saveSettings();

    gdata.window->setSize(sf::Vector2u(gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight()));
    gdata.view = new sf::View(sf::FloatRect(0,0,gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight())); // remember to delete this
    gdata.window->setView(*gdata.view);
    gdata.window->setFramerateLimit(gdata.settings->getFpsLimit());
}

void StateGame::load()
{
    cout << "===================================================" << endl;
    cout << "Loading Level " << gdata.level << endl;
    cout << "===================================================" << endl;

    cout << "setting RNG seed:";
    gzClock clock;
	srand(clock.getCurrentTimeMilliseconds());
	cout << "complete" << endl;

    cout << "creating camera:";
    camera = Camera(0,0,gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight());
	gdata.camera = &camera;
	cout << "complete" << endl;

    cout << "initialising physics:";
	debugDraw = new VisualDebugger();
	debugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
	debugDraw->cam = &camera;
	debugDraw->font.setFont(gdata.assets->getFont("purista-medium-14-white"));

	world = new b2World(GRAVITY);
	world->SetDebugDraw(debugDraw);
	world->SetContactListener(&collisions);
	gdata.world = world;

	factory = PhysicsFactory(world);
	gdata.factory = &factory;
	cout << "complete" << endl;

	manager.setPhysicsWorld(world);

    cout << "creating background:";
	bg.bubble_alpha_range.set(0,8);
    bg.bubble_color = sf::Color(255,255,255,0);
	bg.num_circles = 60;
	bg.init();

	int min = 15;
    int max = 30;
    float brightness = 0.055f;
    int s = utils::getRandom(1,3);

    int r = utils::getRandom(s == 1 ? 0 : min,s == 1 ? 5 : max);
    int b = utils::getRandom(s == 2 ? 0 : min,s == 2 ? 5 : max);
    int g = utils::getRandom(s == 3 ? 0 : min,s == 3 ? 5 : max);

    r += (255.f * brightness);
    g += (255.f * brightness);
    b += (255.f * brightness);

    r = r > 255 ? 255 : r;
    g = g > 255 ? 255 : g;
    b = b > 255 ? 255 : b;

    bg.rec.setFillColor(sf::Color(r,g,b,255));
	cout << "complete" << endl;

    cout << "initialising input:";
	input.init();
	input.m_player = player;
	cout << "complete" << endl;

    cout << "initialising input:";
    loadLevel();
	cout << "complete" << endl;

	cout << "createing fonts:";
    font.setWindow(gdata.window);
    font.setFont(gdata.assets->getFont("purista-medium-14-white"));
    font.setColor(sf::Color::Red);

    sf::Color purple = sf::Color(135,0,135);
    fntPower.setWindow(gdata.window);
    fntPower.setFont(gdata.assets->getFont("segoe-ui-light-48"));
    fntPower.setColor(purple);

    fntAngle.setWindow(gdata.window);
    fntAngle.setFont(gdata.assets->getFont("segoe-ui-light-20"));
    fntAngle.setColor(purple);

    fntIns.setWindow(gdata.window);
    fntIns.setFont(gdata.assets->getFont("segoe-ui-light-20"));
    fntIns.setColor(sf::Color::White);

    fntLevel.setWindow(gdata.window);
    fntLevel.setFont(gdata.assets->getFont("segoe-ui-light-48"));
    fntLevel.setColor(sf::Color::White);
    cout << "complete" << endl;

    cout << "adjusting screen size:";
	gdata.zoom = (gdata.settings->getScreenWidth() / 1900.f);
	cout << "complete" << endl;

    cout << "color:" << r << "-" << g << "-" << b << endl;

    cout << "===================================================" << endl;
    loading = false;
}

bool StateGame::initialise()
{
	loading = true;
    sf::Thread loading_thread(&StateGame::load,this);
    loading_thread.launch();

    // loading screen data
    gzClock clock;
	float timedelta = clock.getDeltaSeconds();
    sf::Sprite sprite;
    sf::Texture texture;
    if (texture.loadFromFile("media/images/loading.png"))
    {
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2,texture.getSize().y / 2);
        sprite.setPosition( gdata.settings->getScreenWidth() / 2,gdata.settings->getScreenHeight() / 2 );
    }

    while (loading)
    {
        timedelta = clock.getDeltaSeconds();
        sf::Event event;
        while (gdata.window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                gdata.running = false;
            }
        }

        // draw
        gdata.window->clear(sf::Color(0,0,0,255));
        gdata.window->draw(sprite);
        gdata.window->display();

        sprite.rotate( 90.f * timedelta );

    }

    return true;
}

void StateGame::start()
{
}


void StateGame::handleEvents()
{
	input.handleEvents();
}

void StateGame::update()
{
	manager.update();
	bg.update();
}

void StateGame::draw()
{
    gdata.window->clear(sf::Color::Black);

    bg.draw();

    if (input.selecting)
    {
        // draw the line
        Vector2 start = player->getAbsolutePosition();
        Vector2 dir = input.vel;
        dir.setMagnitude(50);

        Vector2 p = gdata.toScreenPixels(start);
        Vector2 n = gdata.toScreenPixels(start + dir);
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(p.x, p.y),sf::Color(255,255,255,32)),
            sf::Vertex(sf::Vector2f(n.x, n.y),sf::Color(255,255,255,32))
        };
        gdata.window->draw(line, 2, sf::Lines);

        dir.setMagnitude( (static_cast<float>(input.power) / 100.f) * WORLD_SCALE * 0.4);
        Vector2 n2 = gdata.toScreenPixels(start + dir);
        sf::Vertex line2[] =
        {
            sf::Vertex(sf::Vector2f(p.x, p.y),sf::Color::White),
            sf::Vertex(sf::Vector2f(n2.x, n2.y),sf::Color::White)
        };
        gdata.window->draw(line2, 2, sf::Lines);

    }

	manager.draw();

    if (gdata.draw_debug)
    {
        world->DrawDebugData();
    }

	if (input.selecting)
    {
        float dist = 140;
        float xo = 20;
        float duration = 0.25;
        if (input.angle <= 90 || (input.angle >= 180 && input.angle < 270))
        {
            // move text to the left
            if (cx > -120)
            {
                cx -= dist * (gdata.m_timeDelta / duration);
                if (cx < -120) cx = -120;
            }
        }
        else
        {
            //moving text to the right
            if (cx < 20)
            {
                cx += dist * (gdata.m_timeDelta / duration);
                if (cx > 20) cx = 20;
            }
        }

        Vector2 p = gdata.toScreenPixels(player->getAbsolutePosition());
        string v = gz::toString(input.power) + "%";
        string a = gz::toString(input.angle) + " degrees";
        fntPower.drawString(p.x + cx,p.y - 100,v);
        fntAngle.drawString(p.x + cx,p.y - 50,a);
    }

    fntIns.drawString(10,10,"Press R to restart level");
    fntLevel.drawString(130,110,"Level " + gz::toString(gdata.level));


    //===========================================
    // DRAW A GRID
    //===========================================
    if (gdata.draw_grid)
    {
        for (int x = -19; x <= 19; ++x)
        {
            Vector2 p1(x,10.5);
            Vector2 p2(x,-10.5);

            p1 = gdata.toScreenPixels(p1);
            p2 = gdata.toScreenPixels(p2);
            drawLine(p1,p2);
        }

        for (int y = -10; y <= 10; ++y)
        {
            Vector2 p1(-19,y);
            Vector2 p2(19,y);

            p1 = gdata.toScreenPixels(p1);
            p2 = gdata.toScreenPixels(p2);
            drawLine(p1,p2);
        }
    }
    //===========================================




	// flip the buffer
	gdata.window->display();
}

Vector2 StateGame::raycast(Vector2 start, Vector2 dir, float length)
{
    dir.normalise(); //ensure dir is normalised

	b2RayCastInput	input;
	input.p1 = start.toBulletVector();
	input.p2 = (start + dir).toBulletVector();
	input.maxFraction = length;

	float contact_distance = length;
	for (b2Body* b = gdata.world->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
		    if (f->GetFilterData().categoryBits != CF_PARTICLE && !f->IsSensor() && f->GetFilterData().categoryBits != CF_PLAYER)
			{
			    b2RayCastOutput output;
                if (!f->RayCast(&output, input, 0))
                {
                    continue;
                }
                if (output.fraction < contact_distance)
                {
                    contact_distance = output.fraction;
                }
			}
		}
	}

    Vector2 delta = dir;
    delta.normalise();
    delta.setMagnitude(contact_distance);

	return (delta);
}

void StateGame::drawLine(Vector2 p1, Vector2 p2)
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(p1.x, p1.y),sf::Color(255,255,255,128)),
        sf::Vertex(sf::Vector2f(p2.x, p2.y),sf::Color(255,255,255,128))
    };
    gdata.window->draw(line, 2, sf::Lines);
}

void StateGame::freeResources()
{
    manager.freeResources();

    delete world;
    delete debugDraw;
}

void StateGame::loadLevel()
{
	try
	{
		XMLDocument doc;
		XMLError error = doc.LoadFile(  gz::toString(LEVEL_PATH + gz::toString(gdata.level) + ".xml").c_str() );

		if (error != XML_NO_ERROR)
		{
			gz::print_w("Error loading level xml error#" + XML_NO_ERROR);
			return;
		}

		XMLElement* root = doc.RootElement();

		if (!root)
		{
			gz::print_w("Error getting root element");  // no root element
			return;
		}

		// reading the objects
		XMLElement* element = root->FirstChildElement("object");
		while (element)
		{
			std::string attribute_type = element->Attribute("type");

			if (attribute_type == "platform")
			{
				Vector2 pos		= Vector2(element->Attribute("position"));
				Vector2 size	= Vector2(element->Attribute("size"));
				Vector2 p1		= Vector2(element->Attribute("p1"));
				Vector2 p2		= Vector2(element->Attribute("p2"));
				bool moving		= atoi(element->Attribute("moves"));
				float duration	= atof(element->Attribute("duration"));
				float progress	= atof(element->Attribute("progress"));
				float angle		= atof(element->Attribute("rotation"));
				float rotspeed  = atof(element->Attribute("rotationspeed"));

                Wall* platform = new Wall();
                platform->setPhysicsObject(factory.createObsticle(pos.x, pos.y, size.x, size.y, angle, platform));

                platform->m_moving	    = moving;
                if (moving)
                {
                    platform->setPosition( p1 + ((p2 - p1) * progress));
                    platform->m_duration    = duration;
                    platform->m_point1	    = p1;
                    platform->m_point2	    = p2;
                    platform->m_dest        = p2;

                    platform->setAngularVelocity(rotspeed * DEGTORAD);
                    platform->setLinearVelocity( (p2 - p1) / duration);
                }

                manager.addObject(platform);

			}
			else if (attribute_type == "wall")
			{
				Vector2 pos		= Vector2(element->Attribute("position"));
				Vector2 size	= Vector2(element->Attribute("size"));
				float	angle	= atof(element->Attribute("rotation"));

				Wall* wall = new Wall();
				wall->setPhysicsObject(factory.createGround(pos.x, pos.y, size.x, size.y, angle,wall));

				manager.addObject(wall);

			}
			else if (attribute_type == "player")
			{
				Vector2 pos = Vector2(element->Attribute("position"));

				player = new Player();
				player->setPhysicsObject(factory.createPlayer(pos.x, pos.y, player));
				player->m_name = "Object: player";
				player->reset_pos = pos;
				manager.addObject(player);
				input.m_player = player;
			}
			else if (attribute_type == "laser")
			{
				Vector2 pos			= Vector2(element->Attribute("position"));
				Vector2 laser_dir	= Vector2(element->Attribute("laser_direction"));
				Vector2 p1			= Vector2(element->Attribute("p1"));
				Vector2 p2			= Vector2(element->Attribute("p2"));
				bool moving			= atoi(element->Attribute("moving"));
				float move_duration = atof(element->Attribute("duration"));
				float move_time		= atof(element->Attribute("time"));

				float start_angle	= atof(element->Attribute("start_angle"));
				float delta_angle	= atof(element->Attribute("delta_angle"));
				float rot_dur		= atof(element->Attribute("rotation_duration"));
				bool rotating		= atoi(element->Attribute("rotating"));
				float rot_time		= atof(element->Attribute("rotation_time"));

				Laser* l = new Laser();
				l->laserPos = pos;
				l->laser_dir = laser_dir;
				l->m_point1 = p1;
				l->m_point2 = p2;
				l->m_dest = p2;
				l->m_moving = moving;
				l->m_duration = move_duration;
				l->m_time = move_time;

				l->start_angle = start_angle;
				l->delta_angle = delta_angle;
				l->r_duration = rot_dur;
				l->rotating = rotating;
				l->r_time = rot_time;

				manager.addObject(l);
			}
			else if (attribute_type == "hole")
			{
				Vector2 pos = Vector2(element->Attribute("position"));

				Hole* hole = new Hole();
				hole->setPhysicsObject(factory.createHole(pos.x,pos.y));
				hole->m_type = HOLE;
				hole->m_image.setTexture(*gdata.assets->getTexture("hole_off"));
				manager.addObject(hole);
			}

			element = element->NextSiblingElement("object");
		}



	}
	catch (std::exception& ex)
	{
		gz::print_w("Exception Thrown:" + gz::toString(ex.what()));
	}
}
