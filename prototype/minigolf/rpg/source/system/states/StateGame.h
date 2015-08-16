#ifndef STATEGAME_H
#define STATEGAME_H

#include "general.h"

#include "system/states/IState.h"
#include "system/AssetManager.h"
#include "system/GameData.h"
#include "system/Settings.h"
#include "system/InputHandler.h"

#include "scene/Camera.h"

#include "physics/PhysicsFactory.h"
#include "physics/debug/VisualDebugger.h"
#include "physics/ContactListener.h"

#include "entities/Laser.h"
#include "entities/Object.h"
#include "entities/Player.h"
#include "entities/ObjectManager.h"

#include "video/AnimatedImage.h"
#include "video/Image.h"
#include "video/sdlFontRenderer.h"


/////////////////////////////////////////////////////////
#include "animation/AnimationManager.h"
#include "animation/AnimationInstruction.h"
#include "animation/Animation.h"

class StateGame : public IState
{
    public:
        StateGame();
        virtual ~StateGame();

    public: // member variables
        gzClock clock;

    public:
        virtual void load();
        virtual bool initialise();
        virtual void handleEvents();
        virtual void update();
        virtual void draw();
        virtual void freeResources();
        virtual void start();


    private:
        Camera	camera;

    public: // debug variables
        bool done = false;
        bool drawPhysicsDebug = true;

		AssetManager	assets;

		sdlFontRenderer* purista12;

		// input
		InputHandler		d_inputHandler;

		// entities
		ObjectManager		manager;
		Player*				player = nullptr;
		//bot*				npc = nullptr;
		//Object*				obj = nullptr;
		float timer = 0;

		// physics
		b2World*			world = nullptr;
		VisualDebugger*		visualDebugger = nullptr;
		ContactListener		d_contactListener;
		PhysicsFactory		factory;

		Image*				bg;

		void loadLevel();
};

#endif // STATEGAME_H
