#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "general.h"

#include "video/Camera.h"
#include "video/sfFontRenderer.h"

#include "system/GameData.h"
#include "system/Settings.h"

#include "objects/Player.h"

class InputHandler
{
    public:
        InputHandler();
        virtual ~InputHandler();

        void init();
        void handleEvents();

        void handleMouseEvents();
        void handleControllerEvents();
        void handlePlayerEvents();

        void debug_events();

        Player* m_player;
        sfFontRenderer* font = nullptr;

        Vector2 s_pos;
		Vector2 e_pos;

		float pullbackDistance = 300;
		int power = 0;
		int angle = 0;
		bool selecting = false;
		bool launched = false;
		Vector2 velocity;

    private:

        int         lastUsed = 0;
        b2Vec2      m_rawVelocity;
        float       m_rawRotation = 0;
        bool        js_move = false;

		KeyboardKey* zoomin;
		KeyboardKey* zoomout;

		KeyboardKey* cameraL;
		KeyboardKey* cameraR;
		KeyboardKey* cameraU;
		KeyboardKey* cameraD;
};

#endif // INPUTHANDLER_H
