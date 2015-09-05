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
		for (int j = 0; j < o->m_collidingObjects.size(); ++j)
		{
			o->onCollision(o->m_collidingObjects.at(j));
		}
		vector<Object*> children = o->getChildren();
		for (int j = 0; j < children.size(); j++)
		{
			callOnCollision_recursive(children.at(j));
		}

	}
}

void ObjectManager::callOnCollision_recursive(Object* obj)
{
	for (int j = 0; j < obj->m_collidingObjects.size(); ++j)
	{
		obj->onCollision(obj->m_collidingObjects.at(j));
	}

	vector<Object*> children = obj->getChildren();
	for (int j = 0; j < children.size(); j++)
	{
		callOnCollision_recursive(children.at(j));
	}
}

void ObjectManager::draw()
{
    for (unsigned i = 0; i < m_objects.size(); ++i)
    {
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

void ObjectManager::freeResources()
{
    for (int i = 0; i < m_objects.size(); ++i)
    {
        Object* o = m_objects.at(i);
        o->freeResources();
        delete o;
    }
    m_objects.clear();
}


