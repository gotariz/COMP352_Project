#ifndef PHYSICSFACTORY_H
#define PHYSICSFACTORY_H

#include "general.h"

#include "system/GameData.h"
#include "Box2D/Common/b2Settings.h"

class PhysicsFactory
{
    public:
        PhysicsFactory(b2World* world = nullptr);
        virtual ~PhysicsFactory();

    public:
        b2World* m_world;

    public:

        b2Body* createHole(float x, float y, void* userPointer);
        b2Body* createPlayer(float x, float y, void* userPointer);
		b2Body* createGround(float x, float y, float width, float height, float angle, void* userPointer);
		b2Body* createObsticle(float x, float y, float w, float h, float angle, void* userPointer);
		b2Body* createParticle(float x, float y, void* userPointer);

		b2Body* createSwitch(float x, float y, void* userPointer);
};

#endif // PHYSICSFACTORY_H
