#include "VisualDebugger.h"

void VisualDebugger::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	int r = color.r * 255;
	int g = color.g * 255;
	int b = color.b * 255;
	int a = 255;

	const int32 n = vertexCount;
	vector<Sint16> x;
	vector<Sint16> y;

	for (int i = 0; i < vertexCount; ++i)
	{
		//b2Vec2 point = b2Vec2(vertices[i].x, vertices[i].y);
		Vector2 p = CartToScreen(vertices[i]);
		x.push_back(p.x);
		y.push_back(p.y);
	}

	polygonRGBA(gdata.renderer, &x[0], &y[0], vertexCount, r, g, b, a);

	SDL_SetRenderDrawColor(gdata.renderer, 0, 0, 0, 255);
}
void VisualDebugger::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	int r = color.r * 255;
	int g = color.g * 255;
	int b = color.b * 255;
	int a = 128;

	const int32 n = vertexCount;
	vector<Sint16> x;
	vector<Sint16> y;

	for (int i = 0; i < vertexCount; ++i)
	{
		//b2Vec2 point = b2Vec2(vertices[i].x, vertices[i].y);
		Vector2 p = CartToScreen(vertices[i]);
		x.push_back(p.x);
		y.push_back(p.y);
	}

	filledPolygonRGBA(gdata.renderer, &x[0], &y[0], vertexCount, r, g, b, a);

	SDL_SetRenderDrawColor(gdata.renderer, 0, 0, 0, 255);
}
void VisualDebugger::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	// color
	int r = color.r * 255;
	int g = color.g * 255;
	int b = color.b * 255;
	int a = 255;
	// circle radius
	float rad = radius * (scale * gdata.zoom);
	// position
	Vector2 pos = CartToScreen(center);

	ellipseRGBA(gdata.renderer, pos.x, pos.y, rad, rad, r, g, b, a);

	SDL_SetRenderDrawColor(gdata.renderer, 0, 0, 0, 255);
}
void VisualDebugger::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	// color
	int r = color.r * 255;
	int g = color.g * 255;
	int b = color.b * 255;
	int a = 128;
	// circle radius
	float rad = radius * (scale * gdata.zoom);
	// position
	Vector2 pos = CartToScreen(center);

	filledEllipseRGBA(gdata.renderer, pos.x, pos.y, rad, rad, r, g, b, a);

	SDL_SetRenderDrawColor(gdata.renderer, 0, 0, 0, 255);
}
void VisualDebugger::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	int r = color.r * 255;
	int g = color.g * 255;
	int b = color.b * 255;
	int a = 255;
	Vector2 point1 = CartToScreen(p1);
	Vector2 point2 = CartToScreen(p2);
	lineRGBA(gdata.renderer, point1.x, point1.y, point2.x, point2.y, r, g, b, a);
	//sf::Vertex line[] =
	//{
	//	sf::Vertex(CartToScreen(p1).toSfmlVector(), GLColorToSFML(color)),
	//	sf::Vertex(CartToScreen(p2).toSfmlVector(), GLColorToSFML(color))
	//};

	//m_gameData.m_window->draw(line, 2, sf::Lines);
	SDL_SetRenderDrawColor(gdata.renderer, 0, 0, 0, 255);
}
void VisualDebugger::DrawTransform(const b2Transform& xf)
{
	// this draws object axis
	float linelength = 0.4;

	b2Vec2 xaxis = xf.p + linelength * xf.q.GetXAxis();
	Vector2 redp1 = CartToScreen(xf.p);
	Vector2 redp2 = CartToScreen(xaxis);

	b2Vec2 yaxis = xf.p + linelength * xf.q.GetYAxis();
	Vector2 greenp1 = CartToScreen(xf.p);
	Vector2 greenp2 = CartToScreen(yaxis);

	lineRGBA(gdata.renderer, redp1.x, redp1.y, redp2.x, redp2.y, 255, 0, 0, 255);
	lineRGBA(gdata.renderer, greenp1.x, greenp1.y, greenp2.x, greenp2.y, 0, 255, 0, 255);
	
	SDL_SetRenderDrawColor(gdata.renderer, 0, 0, 0, 255);
}
