#ifndef PLAYER_H
#define PLAYER_H

#include "general.h"
#include "entities/Object.h"
#include "animation/Animation.h"

class Player : public Object
{
    public:
        Player(int id = -1);
        virtual ~Player();

    public:

        Object*     weapon = nullptr;

        float decceleration = 8.0f;
        float acceleration = 60.0f; // world units per second
        float maxMoveSpeed = 6.0f; // world units per second
        Vector2 moveDirection = Vector2();

        virtual void onPrePhysicsUpdate();
		virtual void onPostPhysicsUpdate();
		virtual void onEnterCollision(Object* objectB);
		virtual void onExitCollision(Object* objectB);

        void setMoveDirection(Vector2 direction);
        //void readAnimations();

		void flap();
        void applyImpulse(Vector2 impulse);

        Animation* a_attack = nullptr;


    private:
};

#endif // PLAYER_H
