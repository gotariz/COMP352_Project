#include "PhysicsFactory.h"

PhysicsFactory::PhysicsFactory(b2World* world) : m_world(world)
{
    //ctor
}

PhysicsFactory::~PhysicsFactory()
{
    //dtor
}

b2Body* PhysicsFactory::createPlayer(float x, float y, void* userPointer)
{
    // create temp physics player
    b2CircleShape shape;
    shape.m_radius = 0.5;

    b2FixtureDef fixtureDef;
    fixtureDef.shape        = &shape;
    fixtureDef.density      = 1;
    fixtureDef.restitution  = 1.0f;
	fixtureDef.friction     = 0.0f;

	fixtureDef.filter.categoryBits = CF_PLAYER;			// what the object is
	fixtureDef.filter.maskBits = CF_WALL | CF_GROUND;   // what the object collides with

	b2BodyDef bodyDef;
	bodyDef.type            = b2_dynamicBody;
    bodyDef.fixedRotation   = true;

    bodyDef.position.Set(x,y);

    b2Body* body = m_world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
	body->SetLinearDamping(0.0);
	body->SetBullet(false);
	body->SetSleepingAllowed(false);

	return body;
}

b2Body* PhysicsFactory::createGround(float x, float y, float width, float height, float angle)
{
	float hw = width / 2;
	float hh = height / 2;
	b2Vec2 h[4];
	h[0].Set(-hw, -hh);
	h[1].Set(hw, -hh);
	h[2].Set(hw, hh);
	h[3].Set(-hw, hh);

	b2PolygonShape polygon_shape;
	polygon_shape.Set(h, 4);

	b2FixtureDef fixtureDef;
	fixtureDef.shape		= &polygon_shape;
	fixtureDef.density		= 1.0f;
	fixtureDef.restitution	= 0.0f;
	fixtureDef.friction	= 0.0f;
	fixtureDef.isSensor	= false;
	fixtureDef.filter.categoryBits	= CF_GROUND;    // what the object is
	fixtureDef.filter.maskBits		= CF_ALL;		// what the object collides with

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.angle = angle * DEGTORAD;
;
	bodyDef.fixedRotation = true;
	bodyDef.angularDamping = 0.0f;
	bodyDef.linearDamping = 0.0f;
	bodyDef.position.Set(x, y);
	bodyDef.allowSleep = false;

	b2Body* body = m_world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
	body->SetBullet(false);

	return body;
}

b2Body* PhysicsFactory::createHole(float x, float y)
{
	// create temp physics player
	b2CircleShape shape;
	shape.m_radius = 0.5;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1;
	fixtureDef.restitution = 0.85f;
	fixtureDef.friction = 0.25f;
	fixtureDef.isSensor = true;

	fixtureDef.filter.categoryBits = CF_HOLE;     // what the object is
	fixtureDef.filter.maskBits = CF_PLAYER;        // what the object collides with

	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(x, y);

	b2Body* body = m_world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
	body->SetLinearDamping(1.0);
	body->SetBullet(false);
	body->SetSleepingAllowed(false);

	return body;
}

b2Body* PhysicsFactory::createObsticle(float x, float y, float w, float h, float angle)
{
	float hw = w / 2;
	float hh = h / 2;

	b2Vec2 v[4];
	v[0].Set(-hw, -hh);
	v[1].Set(hw, -hh);
	v[2].Set(hw, hh);
	v[3].Set(-hw, hh);

	b2PolygonShape polygon_shape;
	polygon_shape.Set(v, 4);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygon_shape;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.isSensor = false;
	fixtureDef.filter.categoryBits = CF_GROUND;    // what the object is
	fixtureDef.filter.maskBits = CF_ALL;		// what the object collides with

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.fixedRotation = true;
	bodyDef.angularDamping = 0.0f;
	bodyDef.linearDamping = 0.0f;
	bodyDef.position.Set(x, y);
	bodyDef.angle = angle * DEGTORAD;
	bodyDef.allowSleep = false;

	b2Body* body = m_world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
	body->SetBullet(false);

	return body;
}


















