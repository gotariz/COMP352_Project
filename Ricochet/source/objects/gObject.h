#ifndef GOBJECT_H
#define GOBJECT_H

#include "general.h"
#include "Object.h"

#include "system/GameData.h"
#include "video/Camera.h"
#include "system/AudioManager.h"

class gObject : public Object
{
    public:
        gObject();
        virtual ~gObject();

    public:
        virtual void onCreate();
        virtual void onDestroy();
        virtual void onUpdate();
        virtual void onPrePhysicsUpdate();
        virtual void onPostPhysicsUpdate();
        virtual void onCollision(Object* objectB);
        virtual void onEnterCollision(CollisionData cd);
        virtual void onExitCollision(CollisionData cd);
        virtual void onDraw();
};

#endif // GOBJECT_H
