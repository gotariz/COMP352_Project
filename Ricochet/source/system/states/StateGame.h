#ifndef STATEGAME_H
#define STATEGAME_H

#include "general.h"

#include "system/states/IState.h"
#include "system/AssetManager.h"
#include "system/GameData.h"
#include "system/Settings.h"
#include "system/InputHandler.h"

#include "physics/PhysicsFactory.h"
#include "physics/debug/VisualDebugger.h"
#include "physics/ContactListener.h"

#include "objects/Laser.h"
#include "objects/Player.h"
#include "objects/Hole.h"
#include "objects/Object.h"
#include "objects/Wall.h"
#include "objects/Toggle.h"
#include "objects/ObjectManager.h"

#include "video/Camera.h"
#include "video/sfFontRenderer.h"
#include "video/particles/ParticleEmitter.h"
#include "video/Background.h"
#include "video/ProgressScreen.h"


/////////////////////////////////////////////////////////
//#include "animation/AnimationManager.h"
//#include "animation/AnimationInstruction.h"
//#include "animation/Animation.h"

class StateGame : public IState
{
    public:
        StateGame();
        virtual ~StateGame();

    public: // member variables
        //gzClock clock;

    public:
        virtual void load();
        virtual bool initialise();
        virtual void handleEvents();
        virtual void update();
        virtual void draw();
        virtual void freeResources();
        virtual void start();
        virtual void reload();

        Vector2 raycast(Vector2 start, Vector2 dir, float length);

        void loadLevel();

        void reInit();

        void drawLine(Vector2 p1, Vector2 p2, sf::Color c = sf::Color::White);
        void drawLine(Vector2 p1, Vector2 p2, int thickness, sf::Color c = sf::Color::White);
        sf::RectangleShape rec;

    public:

		ObjectManager		manager;
		InputHandler		input;
		Camera	            camera;

        sfFontRenderer     font;
        sfFontRenderer     fntPower;
        sfFontRenderer     fntAngle;
        sfFontRenderer     fntIns;

        Player*             player = nullptr;
        Background          bg;

		// Box2D physics
		b2World*			world = nullptr;
		VisualDebugger*		debugDraw = nullptr;
		ContactListener		collisions;
		PhysicsFactory		factory;
		bool                drawPhysicsDebug = true;

		ProgressScreen      ps;

		vector<TextData>    text_data;
		sfFontRenderer      text_renderer;

		void render_texts();


		float cx = 20;

        private:
            void createPlatform(XMLElement* element,Toggle* t = nullptr);
            void createWall(XMLElement* element);
            void createPlayer(XMLElement* element);
            void createHole(XMLElement* element);
            void createSwitch(XMLElement* element);
            void createLaser(XMLElement* element,Toggle* t = nullptr);
            void createText(XMLElement* element);

};

#endif // STATEGAME_H
