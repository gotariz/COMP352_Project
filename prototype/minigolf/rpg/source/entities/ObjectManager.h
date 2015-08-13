#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "general.h"

#include "entities/Object.h"
#include "system/GameData.h"

class ObjectManager
{
    public:
        ObjectManager();
        virtual ~ObjectManager();
    public:
        void initialise();
        void update();
        void draw();

        unsigned getValidID();
        void addObject(Object* object);
        void removeObject(Object* object);
        void removeObject(int id);

        Object* getObject(int id);
        bool find(Object* object);
        void setPhysicsWorld(b2World* physicsWorld);

	private: // functions
		void updatePhysicsWorld();

		void callOnCollision();
		void callOnCollision_recursive(Object* obj);

    private:
        b2World*                physics_world = nullptr;
        unsigned                idCounter;
        std::vector<Object*>    m_objects;


        // physics
        float accumulator = 0;

};

#endif // OBJECTMANAGER_H
