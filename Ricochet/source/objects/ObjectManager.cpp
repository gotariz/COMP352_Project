#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
    //ctor
}

ObjectManager::~ObjectManager()
{
    //dtor
}

void ObjectManager::initialise()
{

}

void ObjectManager::freeResources()
{
    for (unsigned i = 0; i < m_objects.size(); ++i)
    {
        Object* obj = m_objects.at(i);
        obj->freeResources();
        delete obj;
    }
}

void ObjectManager::setPhysicsWorld(b2World* physicsWorld)
{
    physics_world = physicsWorld;
}

void ObjectManager::update()
{
    for (unsigned i = 0; i < m_objects.size(); ++i)
    {
        Object* object = m_objects.at(i);
        object->onUpdate();
    }

    // PHYSICS_UPDATE
	accumulator += gdata.m_timeDelta;
	//cout << "accumulator=" << gdata.m_timeDelta << endl;
	while(accumulator > 0)
    {
        updatePhysicsWorld();
    }
}

void ObjectManager::updatePhysicsWorld()
{
    for (unsigned i = 0; i < m_objects.size(); ++i)
    {
        Object* object = m_objects.at(i);
        object->onPrePhysicsUpdate();
    }

    float timeStep = accumulator > MAX_TIME_STEP ? MAX_TIME_STEP : accumulator;
    //float timeStep = 1.f/120.f;
    //cout << "time_step:" << timeStep << endl;
	//float timeStep_seconds = timeStep / 1000.f;
	physics_world->Step(timeStep, MAX_POSITION_ITERATIONS, MAX_VELOCITY_ITERATIONS);
    accumulator -= timeStep;

    for (unsigned i = 0; i < m_objects.size(); ++i)
    {
        Object* object = m_objects.at(i);
        object->onPostPhysicsUpdate();
    }

	callOnCollision();
}

void ObjectManager::callOnCollision()
{
	for (unsigned i = 0; i < m_objects.size(); ++i)
	{
		Object* o = m_objects.at(i);
		for (unsigned j = 0; j < o->m_collidingObjects.size(); ++j)
		{
			o->onCollision(o->m_collidingObjects.at(j));
		}
		vector<Object*> children = o->getChildren();
		for (unsigned j = 0; j < children.size(); j++)
		{
			callOnCollision_recursive(children.at(j));
		}

	}
}

void ObjectManager::callOnCollision_recursive(Object* obj)
{
	for (unsigned j = 0; j < obj->m_collidingObjects.size(); ++j)
	{
		obj->onCollision(obj->m_collidingObjects.at(j));
	}

	vector<Object*> children = obj->getChildren();
	for (unsigned j = 0; j < children.size(); j++)
	{
		callOnCollision_recursive(children.at(j));
	}
}

void ObjectManager::draw()
{
    Object* obj = nullptr;
    // draw holes and switches
    for (unsigned i = 0; i < m_objects.size(); ++i)
    {
        obj = m_objects.at(i);
        if (obj->m_type == SWITCH || obj->m_type == HOLE)
            m_objects.at(i)->onDraw();
    }

    // draw lasers
    for (unsigned i = 0; i < m_objects.size(); ++i)
    {
        obj = m_objects.at(i);
        if (obj->m_type == LASER)
            m_objects.at(i)->onDraw();
    }

    // draw players
    for (unsigned i = 0; i < m_objects.size(); ++i)
    {
        obj = m_objects.at(i);
        if (obj->m_type == PLAYER || obj->m_type == GHOST_PLAYER)
            m_objects.at(i)->onDraw();
    }

    // draw walls
    for (unsigned i = 0; i < m_objects.size(); ++i)
    {
        obj = m_objects.at(i);
        if (obj->m_type == WALL)
            m_objects.at(i)->onDraw();
    }
}

unsigned ObjectManager::getValidID()
{
    return idCounter++;
}

bool ObjectManager::find(Object* object)
{
    bool result = false;
    for (unsigned i = 0; i < m_objects.size(); ++i)
    {
        if (m_objects.at(i) == object)
        {
            result = true;
            i = m_objects.size();
        }
    }

    return result;
}

void ObjectManager::addObject(Object* object)
{
    if (!find(object))
    {
        m_objects.push_back(object);
    }
}

void ObjectManager::removeObject(Object* object)
{
    int index = -1;

    for (unsigned i = 0; i < m_objects.size(); ++i)
    {
        if (m_objects.at(i) == object)
        {
            index = i;
            i = m_objects.size();
        }
    }

    // swap with last object then remove
	if (index != -1)
	{
		m_objects.at(index) = m_objects.at(m_objects.size() - 1);
		m_objects.pop_back();
	}
}

void ObjectManager::removeObject(int id)
{
    int index = -1;

    for (unsigned i = 0; i < m_objects.size(); ++i)
    {
        if (m_objects.at(i)->getID() == id)
        {
            index = i;
            i = m_objects.size();
        }
    }

    if (index != -1)
    {
        m_objects.at(index) = m_objects.at( m_objects.size() - 1);
        m_objects.erase( m_objects.end() );
    }
}

Object* ObjectManager::getObject(int id)
{
    Object* result = nullptr;
    for (unsigned i = 0; i < m_objects.size(); ++i)
    {
        if (m_objects.at(i)->getID() == id)
        {
            result = m_objects.at(i);
            i = m_objects.size();
        }
    }

    return result;
}

