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
    b2WorldManifold wm;
    contact->GetWorldManifold(&wm);

    void* userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* userDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if (userDataA && userDataB)
    {
        Object* objectA = static_cast<Object*>(contact->GetFixtureA()->GetBody()->GetUserData());
        Object* objectB = static_cast<Object*>(contact->GetFixtureB()->GetBody()->GetUserData());

        objectA->m_collidingObjects.push_back(objectB);
        objectB->m_collidingObjects.push_back(objectA);

        CollisionData ca;
        CollisionData cb;

        ca.objectB = objectA;
        cb.objectB = objectB;
        for (int i = 0; i < contact->GetManifold()->pointCount; i++)
        {
            Vector2 v(wm.points[i]);
            ca.points.push_back(v);
            cb.points.push_back(v);
        }

        objectA->onEnterCollision(cb);
        objectB->onEnterCollision(ca);
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
    b2Manifold* m = contact->GetManifold();

    void* userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* userDataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if (userDataA && userDataB)
    {
        Object* objectA = static_cast<Object*>(contact->GetFixtureA()->GetBody()->GetUserData());
        Object* objectB = static_cast<Object*>(contact->GetFixtureB()->GetBody()->GetUserData());

        CollisionData ca;
        CollisionData cb;


        ca.objectB = objectA;
        ca.points.push_back(objectA->getAbsolutePosition());

        cb.objectB = objectB;
        ca.points.push_back(objectA->getAbsolutePosition());

		// remove objectA from objectB
		vector<Object*>::iterator a = find(objectB->m_collidingObjects.begin(), objectB->m_collidingObjects.end(), objectA);
		if (a != objectB->m_collidingObjects.end())	objectB->m_collidingObjects.erase(a);

		// remove objectB from objectA
		vector<Object*>::iterator b = find(objectA->m_collidingObjects.begin(), objectA->m_collidingObjects.end(), objectB);;
		if (a != objectA->m_collidingObjects.end())	objectA->m_collidingObjects.erase(b);

        objectA->onExitCollision(cb);
        objectB->onExitCollision(ca);
    }
}

