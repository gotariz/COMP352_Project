#ifndef PLAYER_H
#define PLAYER_H


#include "general.h"
#include "gObject.h"
#include "sfColor.h"
#include "video/Trail.h"

class Player : public gObject
{
    public:
        Player() : gObject(){onCreate();}
        virtual ~Player(){}

    public:
        virtual void onCreate();
        virtual void onUpdate();
        virtual void onCollision(Object* objectB);
        virtual void onEnterCollision(CollisionData cd);
        virtual void onPostPhysicsUpdate();
        virtual void onDraw();

        float maxSpeed = 30;
		float minSpeed = 5;
		float currentSpeed = 0;

        sfColor color;
        Trail trail;

        Vector2 reset_pos;
};

#endif // PLAYER_H
