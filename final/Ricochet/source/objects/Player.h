#ifndef PLAYER_H
#define PLAYER_H


#include "general.h"
#include "Object.h"

class Player : public Object
{
    public:
        Player(){}
        virtual ~Player(){}

    public:
        virtual void onUpdate();
        virtual void onCollision(Object* objectB);
        virtual void onEnterCollision(CollisionData cd);
        virtual void onDraw();

        //sf::Color c =sf::Color(5,91,165,255);
        sf::Color c =sf::Color(5,91,165,255);
        vector<sf::CircleShape> circles;
        vector<sf::CircleShape> trail;
};

#endif // PLAYER_H
