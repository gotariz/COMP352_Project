#ifndef PHYSICSFACTORY_H
#define PHYSICSFACTORY_H

#include "general.h"

#include "system/GameData.h"

class PhysicsFactory
{
    public:
        PhysicsFactory(b2World* world = nullptr);
        virtual ~PhysicsFactory();

    public:
        b2World* m_world;

    public:
        b2Body* createPlayer(float x = 0, float y = 0, void* userPointer = nullptr);
		
		b2Body* createGround(float x, float y, float width, float height, float angle = 0.f);
		b2Body* createHole(float x, float y);

		b2Body* createObsticle(float x, float y, float w, float h, float angle);
};

#endif // PHYSICSFACTORY_H
