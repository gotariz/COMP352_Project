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
	gdata.world = world;

	factory = PhysicsFactory(world);

	purista12 = new sdlFontRenderer(gdata.renderer);
	purista12->setFont(assets.getFont("purista-medium-14-white"));

	manager.setPhysicsWorld(world);

	bg = new Image();
	bg->setTexture(assets.getTexture("bg"));
	bg->size.set(1, 1);
	bg->scale.set(1, 1);

	d_inputHandler.init();
	loadLevel();

	gdata.zoom = (gdata.settings->getScreenWidth() / 1920.f);

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
	SDL_SetRenderDrawColor(gdata.renderer, 255, 255, 255, 255);
	SDL_RenderClear(gdata.renderer);
	SDL_SetRenderDrawColor(gdata.renderer, 0, 0, 0, 255);

	Vector2 pos = gdata.toPixels(0, 0);
	pos.x -= camera.getScreenX();
	pos.y -= camera.getScreenY();
	bg->scale.set(gdata.zoom, gdata.zoom);
	bg->renderImage(gdata.renderer, pos.x, pos.y);

	manager.draw();

	//world->DrawDebugData();

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

				Image* img = new Image();
				img->setTexture(assets.getTexture("block"));
				img->size.set(size.x, size.y);
				img->anchor.x = ((size.x * WORLD_SCALE) / 2);
				img->anchor.y = ((size.y * WORLD_SCALE) / 2);
				obs->m_image = img;

				manager.addObject(obs);

			}
			else if (attribute_type == "barrier")
			{
				Vector2 pos		= Vector2(element->Attribute("position"));
				Vector2 size	= Vector2(element->Attribute("size"));
				float	angle	= atof(element->Attribute("rotation"));

				Object* ground = new Object();
				ground->setPhysicsObject(factory.createGround(pos.x, pos.y, size.x, size.y, angle));

				Image* img = new Image();
				img->setTexture(assets.getTexture("block"));
				img->size.set(size.x, size.y);
				img->anchor.x = ((size.x * WORLD_SCALE) / 2);
				img->anchor.y = ((size.y * WORLD_SCALE) / 2);
				ground->m_image = img;

				manager.addObject(ground);

			}
			else if (attribute_type == "player")
			{
				Vector2 pos = Vector2(element->Attribute("position"));

				player = new Player(manager.getValidID());
				player->setPhysicsObject(factory.createPlayer(pos.x, pos.y, player));
				player->m_name = "Object: player";
				player->restart_pos = pos;
				manager.addObject(player);

				Image* p = new Image();
				p->setTexture(assets.getTexture("player"));
				p->anchor.set(25, 25);
				p->size.set(1, 1);
				player->m_image = p;

				d_inputHandler.m_player = player;
				gdata.player = player;
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

				laser_dir.print("pos");

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
				l->m_moving = moving;
				l->m_duration = move_duration;
				l->m_time = move_time;

				l->start_angle = start_angle;
				l->delta_angle = delta_angle;
				l->r_duration = rot_dur;
				l->m_rotating = rotating;
				l->r_time = rot_time;

				manager.addObject(l);
			}
			else if (attribute_type == "hole")
			{
				Vector2 pos = Vector2(element->Attribute("position"));

				Object* hole = new Object();
				hole->setPhysicsObject(factory.createHole(pos.x,pos.y));
				hole->m_type = HOLE;

				Image* p = new Image();
				p->setTexture(assets.getTexture("end"));
				p->anchor.set(25, 25);
				p->size.set(1, 1);
				hole->m_image = p;

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