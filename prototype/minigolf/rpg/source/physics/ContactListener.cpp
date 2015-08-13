#include "ContactListener.h"

ContactListener::ContactListener()
{
    //ctor
}

ContactListener::~ContactListener()
{
    //dtor
}

void ContactListener::BeginContact(b2Contact* contact)
{
    void* userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* userDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if (userDataA && userDataB)
    {
        Object* objectA = static_cast<Object*>(contact->GetFixtureA()->GetBody()->GetUserData());
        Object* objectB = static_cast<Object*>(contact->GetFixtureB()->GetBody()->GetUserData());

        objectA->m_collidingObjects.push_back(objectB);
        objectB->m_collidingObjects.push_back(objectA);

        objectA->onEnterCollision(objectB);
        objectB->onEnterCollision(objectA);
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
    void* userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* userDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if (userDataA && userDataB)
    {
        Object* objectA = static_cast<Object*>(contact->GetFixtureA()->GetBody()->GetUserData());
        Object* objectB = static_cast<Object*>(contact->GetFixtureB()->GetBody()->GetUserData());
		
		// remove objectA from objectB
		//vector<Object*>::iterator a = find(objectB->m_collidingObjects.begin(), objectB->m_collidingObjects.end(), objectA);
		//if (a != objectB->m_collidingObjects.end())	objectB->m_collidingObjects.erase(a);

		// remove objectB from objectA
		//vector<Object*>::iterator b = find(objectA->m_collidingObjects.begin(), objectA->m_collidingObjects.end(), objectB);;
		//if (a != objectA->m_collidingObjects.end())	objectA->m_collidingObjects.erase(b);

        objectA->onExitCollision(objectB);
        objectB->onExitCollision(objectA);
    }
}

