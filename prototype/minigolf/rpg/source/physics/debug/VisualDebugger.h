#ifndef VISUALDEBUGGER_H
#define VISUALDEBUGGER_H

#include "general.h"

//#include "system/GameData.h"
#include "scene/Camera.h"


class VisualDebugger : public b2Draw
{
    public:
		VisualDebugger(){ scale = WORLD_SCALE; };

        //float       zoom;
        float       scale;
        Camera*     cam;
    private: // member variables

    public:
        void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
        void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
        void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
        void DrawTransform(const b2Transform& xf);

    public: //inliners

        inline Vector2 CartToScreen(b2Vec2 point)
        {
            Vector2 pos = gdata.toPixels(point.x, point.y);
            pos.x -= cam->getScreenX();
            pos.y -= cam->getScreenY();
            return pos;
        }


        //inline sf::Color GLColorToSFML(const b2Color &color, sf::Uint8 alpha = 255)
        //{ return sf::Color(static_cast<sf::Uint8>(color.r * 255), static_cast<sf::Uint8>(color.g * 255), static_cast<sf::Uint8>(color.b * 255), alpha); }

        //inline sf::Vector2f B2VecToSFVec(const b2Vec2 &vector, bool scaleToPixels = true)
        //{ return sf::Vector2f(vector.x * (scaleToPixels ? scale : 1.f), vector.y * (scaleToPixels ? scale : 1.f)); }
};

#endif // VISUALDEBUGGER_H
