#ifndef VISUALDEBUGGER_H
#define VISUALDEBUGGER_H

#include "general.h"

#include "system/AssetManager.h"
#include "system/GameData.h"
#include "video/Camera.h"
#include "video/sfFontRenderer.h"



class VisualDebugger : public b2Draw
{
    public:
		VisualDebugger()
		{
		    scale = WORLD_SCALE;
		    font.setWindow(gdata.window);
        }

        float       scale;
        Camera*     cam;
        sfFontRenderer font;
    private: // member variables

    public:
        void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
        void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
        void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
        void DrawTransform(const b2Transform& xf);
        void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
        void DrawString(int x, int y, const char* string);
        void DrawAABB(b2AABB* aabb, const b2Color& color);

        sf::Color B2SFColor(const b2Color &color, int alpha);
        void DrawMouseJoint(b2Vec2& p1, b2Vec2& p2, const b2Color &boxColor, const b2Color &lineColor);
};

#endif // VISUALDEBUGGER_H
