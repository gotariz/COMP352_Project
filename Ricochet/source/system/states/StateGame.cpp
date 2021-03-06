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

void StateGame::loadBezier()
{
    try
    {
        XMLDocument doc;
        XMLError error = doc.LoadFile("data/bezier.xml");

        if (error != XML_NO_ERROR)
        {
            gz::print_w("Error loading bezier.xml error#" + XML_NO_ERROR);
            return;
        }

        XMLElement* root = doc.RootElement();

        if (!root)
        {
            gz::print_w("Error getting bezier root element");  // no root element
            return;
        }


        XMLElement* element = root->FirstChildElement("point");
        while (element)
        {
            std::string sh1 = element->Attribute("h1");
            std::string sp = element->Attribute("p");
            std::string sh2 = element->Attribute("h2");


            Vector2 p(sp.c_str());
            Vector2 h1(sh1.c_str());
            Vector2 h2(sh2.c_str());
            bezier.points.push_back(BPoint(p,h1,h2));

            p.print("p");
            h1.print("h1");
            h2.print("h2");

            element = element->NextSiblingElement("point");
        }

        cout << bezier.points.size() << endl;

    }
    catch ( std::exception& ex )
    {
        gz::print_w("Exception Thrown:" + gz::toString(ex.what()) );
    }
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

    loadBezier();

    cout << "adjusting screen size:";
	gdata.zoom = (gdata.settings->getScreenWidth() / 1900.f);
	cout << "complete" << endl;

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
	debugDraw->font.setFont(gdata.assets->getFont("purista-medium-14"));

	world = new b2World(GRAVITY);
	world->SetDebugDraw(debugDraw);
	world->SetContactListener(&collisions);
	gdata.world = world;

	factory = PhysicsFactory(world);
	gdata.factory = &factory;
	cout << "complete" << endl;

	manager.setPhysicsWorld(world);

    cout << "initialising input:";
	input.init();
	input.angle_snap = gdata.angle_snap;
	input.m_player = player;
	cout << "complete" << endl;

    cout << "loading level:";
    loadLevel();
	cout << "complete" << endl;

	cout << "createing fonts:";
    font.setWindow(gdata.window);
    font.setFont(gdata.assets->getFont("purista-medium-14"));
    font.setColor(sf::Color::Red);

    fntPower.setWindow(gdata.window);
    fntPower.setFont(gdata.assets->getFont("segoe-ui-light-48"));
    fntPower.setColor(sf::Color::White);

    fntAngle.setWindow(gdata.window);
    fntAngle.setFont(gdata.assets->getFont("segoe-ui-light-20"));
    fntAngle.setColor(sf::Color::White);

    fntIns.setWindow(gdata.window);
    fntIns.setFont(gdata.assets->getFont("segoe-ui-light-20"));
    fntIns.setColor(sf::Color::White);

    text_renderer.setWindow(gdata.window);
    cout << "complete" << endl;

    cout << "creating background:";
	bg.bubble_alpha_range.set(5,10);
    bg.bubble_color = sf::Color(255,255,255,0);
	bg.num_circles = 60;
	bg.init();

	int min = 15;
    int max = 30;
    float brightness = 0.055f;
    int s = utils::getRandom(1,3);

    int r = 0;
    int g = 0;
    int b = 0;

    if (gdata.random_colors)
    {
        r = utils::getRandom(s == 1 ? 0 : min,s == 1? 5 : max);
        g = utils::getRandom(s == 2 ? 0 : min,s == 2 ? 5 : max);
        b = utils::getRandom(s == 3 ? 0 : min,s == 3 ? 5 : max);

        r += (255.f * brightness);
        g += (255.f * brightness);
        b += (255.f * brightness);

        r = r > 255 ? 255 : r;
        g = g > 255 ? 255 : g;
        b = b > 255 ? 255 : b;

        bg.rec.setFillColor(sf::Color(r,g,b,255));
    }
    else
    {
        if (gdata.level < 10)
            bg.rec.setFillColor(sf::Color(16,33,57,255));
        else if (gdata.level < 19)
            bg.rec.setFillColor(sf::Color(41,26,79,255));
        else if (gdata.level < 28)
            bg.rec.setFillColor(sf::Color(18,73,29,255));
        else //if (gdata.level < 36)
            bg.rec.setFillColor(sf::Color(73,18,61,255));
    }

    cout << "complete" << endl;

    gdata.countdown = 0;
    gdata.bounce_counter = 0;
    ps.init();
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
    sf::Texture& texture = *gdata.assets->getTexture("loading");
    sprite.setTexture(texture);
    texture.setSmooth(true);
    sprite.setOrigin(texture.getSize().x / 2,texture.getSize().y / 2);
    sprite.setPosition( gdata.settings->getScreenWidth() / 2,gdata.settings->getScreenHeight() / 2 );

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
        sf::sleep(sf::milliseconds(10));

    }

    return true;
}

void StateGame::start()
{
}


void StateGame::handleEvents()
{
	input.handleEvents();
	if (gdata.show_progress)
	{
	    ps.handleEvents();
	}
}

void StateGame::update()
{
    if (gdata.replay_level && !replay)
    {
        timer = 0;
        input.show_replay = false;
        replay = true;

        // add all the players to the world
        shotData = gdata.shotData;
        for (unsigned i = 0; i < shotData.size(); ++i)
        {
            Player* gplayer = new Player();
            gplayer->setPhysicsObject(factory.createPlayer(startpos.x, startpos.y, gplayer));
            gplayer->m_name = "Object: player";
            gplayer->reset_pos = startpos;
            gplayer->makeGhost();

            manager.addObject(gplayer);

            shotData.at(i).p = gplayer;
        }
    }

    if (replay)
    {
        for (unsigned i = 0; i < shotData.size(); ++i)
        {
            Player* gplayer = shotData.at(i).p;

            if (timer >= shotData.at(i).time && !shotData.at(i).shot)
            {
                cout << "timer:" << timer << endl;
                shotData.at(i).shot = true;

                gplayer->angle = shotData.at(i).angle;
                gplayer->power = shotData.at(i).power;
                gplayer->shootPlayer();
            }
        }
    }


	manager.update();
	bg.update();
	ps.update();

	if (gdata.keys[sf::Keyboard::A].isKeyPressed)
    {
        AchievementBar* achieve = new AchievementBar;
        achieve->init();
        achieve->setText("This is a test achievemet, hooray!");
        gdata.achieves.push_back(achieve);
    }
}

void StateGame::draw()
{
    bg.draw();

    if (gdata.keys[sf::Keyboard::S].isKeyDown && !gdata.first_shot)
    {

        Vector2 p1 = gdata.toScreenPixels(gdata.p1);
        Vector2 p2 = gdata.toScreenPixels(gdata.p2);

        drawLine(p1,p2,1,sf::Color(255,255,255,64));
    }


    if (input.selecting)
    {
        // draw the line
        Vector2 start = player->getAbsolutePosition();
        Vector2 dir = input.vel;
        dir.setMagnitude(30);

        Vector2 p = gdata.toScreenPixels(start);
        Vector2 n = gdata.toScreenPixels(start + dir);
        drawLine(p,n,50 * gdata.zoom,sf::Color(255,255,255,16));
        drawLine(p,n,1,sf::Color(255,255,255,32));


        dir.setMagnitude( (static_cast<float>(input.power) / 100.f) * WORLD_SCALE * 0.4);
        Vector2 n2 = gdata.toScreenPixels(start + dir);
        drawLine(p,n2,1,sf::Color::White);

    }

	manager.draw();

    if (gdata.draw_debug)
    {
        world->DrawDebugData();
    }

	if (input.selecting)
    {
        const int L = -1;
        const int R = 1;
        float dist = 200;
        float duration = 0.5;

        bool aimingRight    = input.angle <= 90 || (input.angle >= 180 && input.angle < 270);
        bool aimingLeft     = !aimingRight;

        if (aimingRight && text == R && !transitioning)
        {
            transitioning = true;
            elapsed = 0;
        }
        if (aimingLeft && text == L && !transitioning)
        {
            transitioning = true;
            elapsed = 0;
        }

        if (transitioning)
        {
            elapsed += gdata.m_timeDelta;
            if (elapsed > duration) elapsed = duration;
            float delta = elapsed / duration;

            if      (text == R)  cx = 100 - (bezier.getPoint(delta).y) * dist; // move left
            else if (text == L)  cx = -100 + bezier.getPoint(delta).y * dist; // move right

            if (delta >= 1)
            {
                delta = 0;
                transitioning = false;
                if (text == L)          text = R;
                else if (text == R)     text = L;
            }
        }

        Vector2 p = gdata.toScreenPixels(player->getAbsolutePosition());
        string v = gz::toString(input.power) + "%";
        string a = gz::toString(input.angle) + " degrees";
        fntPower.drawString(p.x + cx,p.y - 100,v,MIDDLE);
        fntAngle.drawString(p.x + cx,p.y - 50,a,MIDDLE);
    }

    //===========================================
    // DRAW A GRID
    //===========================================
    if (gdata.draw_grid)
    {
        for (int x = -19; x <= 19; ++x)
        {
            Vector2 p1(x,10.5);
            Vector2 p2(x,-10.5);

            sf::Color c = sf::Color::White;
            if (x == 0) c = sf::Color::Red;

            p1 = gdata.toScreenPixels(p1);
            p2 = gdata.toScreenPixels(p2);
            drawLine(p1,p2,c);
        }

        for (int y = -10; y <= 10; ++y)
        {
            Vector2 p1(-19,y);
            Vector2 p2(19,y);

            sf::Color c = sf::Color::White;
            if (y == 0) c = sf::Color::Blue;

            p1 = gdata.toScreenPixels(p1);
            p2 = gdata.toScreenPixels(p2);
            drawLine(p1,p2,c);
        }
    }
    //===========================================

    render_texts();

    fntIns.drawString(10,0,"F1:Help");
    if (gdata.show_help)
    {
        font.drawString(10,30,"Controls");
        font.drawString(10,50,"===================================");
        font.drawString(10,70,"shoot:         click and drag the ball");
        font.drawString(10,90,"right click:   toggle lock angle");
        font.drawString(10,110,"spacebar:   toggle snapping the angle");
        font.drawString(10,130,"S:                show previous shot");
        font.drawString(10,150,"R:                restart level");
    }

    if (gdata.show_progress)
    {
        if (gdata.bounce_counter <= gold)           ps.setStars(3,gdata.bounce_counter);
        else if (gdata.bounce_counter <= silver)    ps.setStars(2,gdata.bounce_counter);
        else                                        ps.setStars(1,gdata.bounce_counter);

        ps.draw();
    }


    timer += gdata.m_timeDelta;
    input.timer = timer;
}

void StateGame::render_texts()
{
    for (unsigned i = 0; i < text_data.size(); ++i)
    {
        TextData& td = text_data.at(i);

        Vector2 sp = gdata.toScreenPixels(td.pos);

        text_renderer.setTransparency( td.transparency );
        text_renderer.setFont(gdata.assets->getFont(td.font));
        text_renderer.setRotation(td.rotation);
        text_renderer.setColor(td.color);
        text_renderer.drawString(sp.x,sp.y,td.text,td.h_align,td.v_align);
    }
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

void StateGame::drawLine(Vector2 p1, Vector2 p2, sf::Color c)
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(p1.x, p1.y),c),
        sf::Vertex(sf::Vector2f(p2.x, p2.y),c)
    };
    gdata.window->draw(line, 2, sf::Lines);
}

void StateGame::drawLine(Vector2 p1, Vector2 p2, int thickness, sf::Color c)
{
    Vector2 delta = p2 - p1;
    float angle = delta.getAngle();
    float length = delta.getMagnitude();

    rec.setSize(sf::Vector2f(length,thickness));
    rec.setRotation(angle);
    rec.setPosition(p1.x,p1.y);
    rec.setFillColor(c);

    rec.setOrigin(0,thickness / 2);

    gdata.window->draw(rec);
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

			if (attribute_type == "platform")       createPlatform(element);
			else if (attribute_type == "wall")      createWall(element);
			else if (attribute_type == "player")    createPlayer(element);
			else if (attribute_type == "laser")     createLaser(element);
			else if (attribute_type == "hole")      createHole(element);
			else if (attribute_type == "switch")    createSwitch(element);
			else if (attribute_type == "text")      createText(element);
			else if (attribute_type == "color")
            {
                mr = atoi(element->Attribute("r"));
                mg = atoi(element->Attribute("g"));
                mb = atoi(element->Attribute("b"));

                //bg.rec.setFillColor( sf::Color(r,g,b) );
            }
            else if (attribute_type == "score")
            {
                gold = atoi(element->Attribute("gold"));
                silver = atoi(element->Attribute("silver"));
                par = gold;
                ps.one_star = gold;
                ps.two_star = silver;
            }

			element = element->NextSiblingElement("object");
		}



	}
	catch (std::exception& ex)
	{
		gz::print_w("Exception Thrown:" + gz::toString(ex.what()));
	}
}

void StateGame::createLaser(XMLElement* element,Toggle* t)
{
    Vector2 pos			= Vector2(element->Attribute("position"));
    Vector2 p1			= Vector2(element->Attribute("p1"));
    Vector2 p2			= Vector2(element->Attribute("p2"));
    float rot	        = atof(element->Attribute("rotation"));
    float stand_rot	    = atof(element->Attribute("stand_rotation"));
    bool moving			= atoi(element->Attribute("moving"));
    float move_duration = atof(element->Attribute("duration"));
    float move_time		= atof(element->Attribute("time"));

    float start_angle	= atof(element->Attribute("start_angle"));
    float delta_angle	= atof(element->Attribute("delta_angle"));
    float rot_dur		= atof(element->Attribute("rotation_duration"));
    bool rotating		= atoi(element->Attribute("rotating"));
    float rot_time		= atof(element->Attribute("rotation_time"));

    float rot_speed		= atof(element->Attribute("rotation_speed"));

    int switch_bits     = atoi(element->Attribute("switch_bits"));
    bool disabled        = atoi(element->Attribute("disabled"));
    bool mov_disabled    = atoi(element->Attribute("disabled_mov"));
    bool rot_disabled    = atoi(element->Attribute("disabled_rot"));

    Laser* l = new Laser();
    l->laserPos = pos;
    l->rotation = rot;
    l->stand_rotation = stand_rot;
    l->m_point1 = p1;
    l->m_point2 = p2;
    l->m_dest = p2;
    l->m_moving = moving;
    l->m_duration = move_duration;
    l->m_time = move_time;
    l->rotation_speed = rot_speed;

    l->start_angle = start_angle;
    l->delta_angle = delta_angle;
    l->r_duration = rot_dur;
    l->rotating = rotating;
    l->r_time = rot_time;
    l->rotation_speed = rot_speed;

    l->laser_head.setTexture(*gdata.assets->getTexture("laser_head"));
    l->laser_head.setOrigin(8,6);

    l->switch_mask = switch_bits;
    l->enable(!disabled);
    l->enableMovement(!mov_disabled);
    l->enableRotation(!rot_disabled);

    if (t) t->obs.push_back(l);

    manager.addObject(l);
}

void StateGame::createPlatform(XMLElement* element,Toggle* t)
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

    int switch_bits     = atoi(element->Attribute("switch_bits"));
    bool disabled        = atoi(element->Attribute("disabled"));
    bool mov_disabled    = atoi(element->Attribute("disabled_mov"));
    bool rot_disabled    = atoi(element->Attribute("disabled_rot"));

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
        platform->setLinearVelocity( (p2 - p1) / duration);
    }

    platform->setAngularVelocity(rotspeed * DEGTORAD);

    platform->switch_mask = switch_bits;
    if (disabled) {
        platform->enable(false);
    } else {
        if (mov_disabled)   platform->enableMovement(false);
        if (rot_disabled)   platform->enableRotation(false);
    }

    if (t) t->obs.push_back(platform);


    wall = platform;
    manager.addObject(platform);
}

void StateGame::createWall(XMLElement* element)
{
    Vector2 pos		= Vector2(element->Attribute("position"));
    Vector2 size	= Vector2(element->Attribute("size"));
    float	angle	= atof(element->Attribute("rotation"));

    Wall* wall = new Wall();
    wall->setPhysicsObject(factory.createGround(pos.x, pos.y, size.x, size.y, angle,wall));

    manager.addObject(wall);
}

void StateGame::createPlayer(XMLElement* element)
{
    Vector2 pos = Vector2(element->Attribute("position"));
    startpos = pos;

    if (gdata.replay_level) return;

    player = new Player();
    player->setPhysicsObject(factory.createPlayer(pos.x, pos.y, player));
    player->m_name = "Object: player";
    player->reset_pos = pos;
    manager.addObject(player);
    input.m_player = player;
}

void StateGame::createHole(XMLElement* element)
{
    Vector2 pos = Vector2(element->Attribute("position"));
    Hole* hole = new Hole();
    hole->setPhysicsObject(factory.createHole(pos.x,pos.y,hole));
    hole->m_type = HOLE;
    hole->m_image.setTexture(*gdata.assets->getTexture("hole_off"));
    manager.addObject(hole);
}

void StateGame::createSwitch(XMLElement* element)
{
    Vector2 pos = Vector2(element->Attribute("position"));
    int switch_type = atoi(element->Attribute("switch_type"));
    float time = atof(element->Attribute("time"));
    Toggle* tog = new Toggle();
    tog->setPhysicsObject(factory.createSwitch(pos.x,pos.y,tog));
    tog->m_image.setTexture(*gdata.assets->getTexture("switch_off"));
    tog->on = gdata.assets->getTexture("switch_on");
    tog->off = gdata.assets->getTexture("switch_off");
    tog->switch_type = switch_type;
    tog->max_time = time;
    manager.addObject(tog);

    XMLElement* child = element->FirstChildElement("object");
    while (child)
    {
        std::string attribute_type = child->Attribute("type");

        if (attribute_type == "platform")       createPlatform(child,tog);
        else if (attribute_type == "wall")      createWall(child);
        else if (attribute_type == "player")    createPlayer(child);
        else if (attribute_type == "laser")     createLaser(child,tog);
        else if (attribute_type == "hole")      createHole(child);
        else if (attribute_type == "switch")    createSwitch(child);

        child = child->NextSiblingElement("object");
    }
}

void StateGame::createText(XMLElement* element)
{
    string text	    = element->Attribute("text");
    string font	    = element->Attribute("font");
    Vector2 pos		= Vector2(element->Attribute("pos"));
    float rotation	= atof(element->Attribute("rotation"));

    int r		    = atoi(element->Attribute("r"));
    int g		    = atoi(element->Attribute("g"));
    int b		    = atoi(element->Attribute("b"));
    int a		    = atoi(element->Attribute("a"));

    int h_align = 0;
    int v_align = 0;

    string h = element->Attribute("h_align");
    string v = element->Attribute("v_align");

    if (h == "right")       h_align = Align::RIGHT;
    else if (h == "middle") h_align = Align::MIDDLE;
    else                    h_align = Align::LEFT;

    if (v == "bottom")      v_align = Align::BOTTOM;
    else if (v == "middle") v_align = Align::MIDDLE;
    else                    v_align = Align::TOP;

    TextData td;

    td.text = text;
    td.font = font;
    td.pos = pos;
    td.rotation = rotation;
    td.color = sf::Color(r,g,b,a);
    td.transparency = a;
    td.h_align = h_align;
    td.v_align = v_align;

    text_data.push_back(td);
}




























