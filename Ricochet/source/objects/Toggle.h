#ifndef SWITCH_H
#define SWITCH_H

#include "general.h"
#include "Obstacle.h"

class Toggle : public Obstacle
{
    public:
        Toggle();
        virtual ~Toggle();

    public:
        int switch_type = TOGGLE;
        bool active = false;

        sf::Texture* on = nullptr;
        sf::Texture* off = nullptr;

        float time = 0;
        float max_time = 2;

        virtual void onCreate();
        virtual void onDestroy();
        virtual void onUpdate();
        virtual void onCollision(Object* objectB);
        virtual void onEnterCollision(CollisionData cd);
        virtual void onExitCollision(CollisionData cd);


        void toggleObstacles();
        vector<Obstacle*> obs;
};

#endif // SWITCH_H
