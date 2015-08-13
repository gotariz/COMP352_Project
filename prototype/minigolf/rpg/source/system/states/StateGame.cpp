#include "StateGame.h"



StateGame::StateGame() : IState(STATE_GAME)
{
    //ctor
}

StateGame::~StateGame()
{
    //dtor
}

void StateGame::load()
{
	assets.renderer = gdata.renderer;
	assets.loadAssetList("data/assets.xml");

	camera.m_x = 0;
	camera.m_y = 0;
	camera.m_w = gdata.settings->getScreenWidth();
	camera.m_h = gdata.settings->getScreenHeight();
	gdata.camera = &camera;

	visualDebugger = new VisualDebugger();
	visualDebugger->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
	visualDebugger->cam = &camera;

	world = new b2World(GRAVITY);
	world->SetDebugDraw(visualDebugger);
	world->SetContactListener(&d_contactListener);

	factory = PhysicsFactory(world);

	purista12 = new sdlFontRenderer(gdata.renderer);
	purista12->setFont(assets.getFont("purista-medium-14-white"));

	manager.setPhysicsWorld(world);

	d_inputHandler.init();
	loadLevel();

    loading = false;
}

bool StateGame::initialise()
{
	loading = true;
	load();

    return true;
}

void StateGame::start()
{
}


void StateGame::handleEvents()
{
	d_inputHandler.handleEvents();
}

void StateGame::update()
{
	manager.update();
}

void StateGame::draw()
{
	//aimg.m_angle += 90.f / 60.f;
	SDL_RenderClear(gdata.renderer);

	manager.draw();

	world->DrawDebugData();

	purista12->drawString(200, 200, player->getAbsolutePosition().toString());
	
	// flip the buffer
	SDL_RenderPresent(gdata.renderer);
}

void StateGame::freeResources()
{
}

void StateGame::loadLevel()
{
	try
	{
		XMLDocument doc;
		XMLError error = doc.LoadFile(  gz::toString(LEVEL_PATH + "1.xml").c_str() );

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
				bool moves		= atoi(element->Attribute("moves"));
				float duration	= atof(element->Attribute("duration"));
				float time		= atof(element->Attribute("time"));
				float angle		= atof(element->Attribute("rotation"));

				Object* obs = new Object();
				obs->setPhysicsObject(factory.createObsticle(pos.x, pos.y, size.x, size.y, angle));
				obs->m_moving	= moves;
				obs->m_duration = duration;
				obs->m_point1	= p1;
				obs->m_point2	= p2;
				obs->m_time		= time;
				obs->m_duration = duration;
				manager.addObject(obs);

			}
			else if (attribute_type == "barrier")
			{
				Vector2 pos		= Vector2(element->Attribute("position"));
				Vector2 size	= Vector2(element->Attribute("size"));
				float	angle	= atof(element->Attribute("rotation"));

				Object* ground = new Object();
				ground->setPhysicsObject(factory.createGround(pos.x, pos.y, size.x, size.y, angle));
				manager.addObject(ground);

			}
			else if (attribute_type == "player")
			{
				Vector2 pos = Vector2(element->Attribute("position"));

				player = new Player(manager.getValidID());
				player->setPhysicsObject(factory.createPlayer(pos.x, pos.y, player));
				player->m_name = "Object: player";
				manager.addObject(player);

				d_inputHandler.m_player = player;
				gdata.player = player;
			}
			else if (attribute_type == "hole")
			{
				Vector2 pos = Vector2(element->Attribute("position"));

				Object* hole = new Object();
				hole->setPhysicsObject(factory.createHole(pos.x,pos.y));
				hole->m_type = HOLE;
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