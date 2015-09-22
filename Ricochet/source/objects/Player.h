#ifndef PLAYER_H
#define PLAYER_H


#include "general.h"
#include "gObject.h"
#include "sfColor.h"
#include "video/Trail.h"
#include "video/particles/BounceEmitter.h"
#include "video/particles/ExplodeEmitter.h"
#include "system/AssetManager.h"
#include "system/AudioManager.h"

class Player : public gObject
{
    public:
        Player() : gObject(){onCreate();m_type = PLAYER;}
        virtual ~Player(){}

    public:
        virtual void onCreate();
        virtual void onUpdate();
        virtual void onCollision(Object* objectB);
        virtual void onEnterCollision(CollisionData cd);
        virtual void onPostPhysicsUpdate();
        virtual void onDestroy();
        virtual void onDraw();
        virtual void freeResources();

        float maxSpeed = 30;
		float currentSpeed = 0;

		BounceEmitter   emitter;
		ExplodeEmitter  explode_emitter;

		bool draw_player = true;

        sfColor color;
        Trail trail;
        sf::Sound sfx;

        Vector2 reset_pos;
};

#endif // PLAYER_H
