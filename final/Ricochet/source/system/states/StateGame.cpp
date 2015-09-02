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
    //reInit();

    gzClock clock;
	srand(clock.getCurrentTimeMilliseconds());

	assets.loadAssetList("data/assets.xml");
	gdata.assets = &assets;

    font = new sfFontRenderer(gdata.window);
    font->setFont(assets.getFont("purista-medium-14-white"));
    font->setColor(sf::Color::Red);

    sf::Color purple = sf::Color(135,0,135);
    fntPower = new sfFontRenderer(gdata.window);
    fntPower->setFont(assets.getFont("segoe-ui-light-48"));
    fntPower->setColor(purple);

    fntAngle = new sfFontRenderer(gdata.window);
    fntAngle->setFont(assets.getFont("segoe-ui-light-20"));
    fntAngle->setColor(purple);

    fntIns = new sfFontRenderer(gdata.window);
    fntIns->setFont(assets.getFont("segoe-ui-light-20"));
    fntIns->setColor(sf::Color::White);

    fntLevel = new sfFontRenderer(gdata.window);
    fntLevel->setFont(assets.getFont("segoe-ui-light-48"));
    fntLevel->setColor(sf::Color::White);

	camera = Camera(0,0,gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight());
	gdata.camera = &camera;

	debugDraw = new VisualDebugger();
	debugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
	debugDraw->cam = &camera;
	debugDraw->font->setFont(assets.getFont("purista-medium-14-white"));

	world = new b2World(GRAVITY);
	world->SetDebugDraw(debugDraw);
	world->SetContactListener(&collisions);
	gdata.world = world;

	factory = PhysicsFactory(world);
	gdata.factory = &factory;

	manager.setPhysicsWorld(world);

	bg.bg_image.setTexture(*assets.getTexture("background"));
	bg.num_circles = 60;
	bg.init();

	input.init();
	input.m_player = player;
	input.font = new sfFontRenderer(gdata.window);
	input.font->setFont(assets.getFont("purista-medium-14-white"));

	loadLevel();

	gdata.zoom = (gdata.settings->getScreenWidth() / 1900.f);

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
    gdata.window->clear(sf::Color(32,32,32,255));
    //gdata.window->clear(sf::Color::Green);

    bg.draw();

    if (input.selecting)
    {
        // draw the line
        Vector2 p = gdata.toScreenPixels(player->getAbsolutePosition());
        Vector2 n = gdata.toScreenPixels(player->getAbsolutePosition() + input.velocity);
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(p.x, p.y)),
            sf::Vertex(sf::Vector2f(n.x, n.y))
        };
        gdata.window->draw(line, 2, sf::Lines);

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
        fntPower->drawString(p.x + cx,p.y - 100,v);
        fntAngle->drawString(p.x + cx,p.y - 50,a);
    }

    fntIns->drawString(10,10,"Press R to restart level");
    fntLevel->drawString(130,110,"Level " + gz::toString(gdata.level));
    //font->drawString(0,0,"Level " + gz::toString(gdata.level));


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

			if (attribute_type == "block")
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

                Wall* wall = new Wall();
                wall->setPhysicsObject(factory.createObsticle(pos.x, pos.y, size.x, size.y, angle));

                wall->m_moving	    = moving;
                if (moving)
                {
                    wall->setPosition( p1 + ((p2 - p1) * progress));
                    wall->m_duration    = duration;
                    wall->m_point1	    = p1;
                    wall->m_point2	    = p2;
                    wall->m_dest        = p2;

                    wall->setAngularVelocity(rotspeed * DEGTORAD);
                    wall->setLinearVelocity( (p2 - p1) / duration);
                }

                manager.addObject(wall);

			}
			else if (attribute_type == "barrier")
			{
				Vector2 pos		= Vector2(element->Attribute("position"));
				Vector2 size	= Vector2(element->Attribute("size"));
				float	angle	= atof(element->Attribute("rotation"));

				Wall* wall = new Wall();
				wall->setPhysicsObject(factory.createGround(pos.x, pos.y, size.x, size.y, angle));

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
				hole->m_image.setTexture(*assets.getTexture("hole_off"));
				manager.addObject(hole);
			}
			else if (attribute_type == "bgcolor")
			{
//				int r = atoi(element->Attribute("r"));
//				int g = atoi(element->Attribute("g"));
//				int b = atoi(element->Attribute("b"));
				int r = utils::getRandom(1,50);
				int g = utils::getRandom(1,50);
				int b = utils::getRandom(1,50);
				int a = atoi(element->Attribute("a"));

				bg.bg_image.setColor(sf::Color(r,g,b,a));
			}

			element = element->NextSiblingElement("object");
		}



	}
	catch (std::exception& ex)
	{
		gz::print_w("Exception Thrown:" + gz::toString(ex.what()));
	}
}
