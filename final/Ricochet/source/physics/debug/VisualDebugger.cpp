#include "VisualDebugger.h"

sf::Color VisualDebugger::B2SFColor(const b2Color &color, int alpha = 255)
{
	sf::Color result((sf::Uint8)(color.r*255), (sf::Uint8)(color.g*255), (sf::Uint8)(color.b*255), (sf::Uint8) alpha);
	return result;
}

void VisualDebugger::DrawAABB(b2AABB* aabb, const b2Color& color)
{
    Vector2 lower = gdata.toScreenPixels(aabb->lowerBound);
    Vector2 upper = gdata.toScreenPixels(aabb->upperBound);
	sf::ConvexShape polygon;
    polygon.setPoint(0,sf::Vector2f(lower.x, lower.y));
    polygon.setPoint(1,sf::Vector2f(upper.x, lower.y));
    polygon.setPoint(2,sf::Vector2f(upper.x, upper.y));
    polygon.setPoint(3,sf::Vector2f(lower.x, upper.y));

    polygon.setOutlineThickness(1.0f);

    polygon.setFillColor(B2SFColor(color,50));
    polygon.setOutlineColor(B2SFColor(color));

	gdata.window->draw(polygon);
}

void VisualDebugger::DrawString(int x, int y, const char* string)
{
    font->drawString(x,y,string);
}

void VisualDebugger::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
    std::cout << "DrawPoint" << endl;
}

void VisualDebugger::DrawTransform(const b2Transform& xf)
{
//    float lineLength = 0.4;
//
//    Vector2 pos = gdata.toScreenPixels(xf.p);
//
//	b2Vec2 xAxis = xf.p + lineLength * xf.q.GetXAxis();
//	Vector2 xa = gdata.toScreenPixels(xAxis);
//	sf::Vertex redLine[] =
//	{
//		sf::Vertex(sf::Vector2f(pos.x,pos.y), sf::Color::Red),
//		sf::Vertex(sf::Vector2f(xa.x,xa.y), sf::Color::Red)
//	};
//
//	// You might notice that the ordinate(Y axis) points downward unlike the one in Box2D testbed
//	// That's because the ordinate in SFML coordinate system points downward while the OpenGL(testbed) points upward
//	/*b2Vec2 yAxis(b2Vec2(xf.p.x + (lineLength * -xf.q.s), xf.p.y + (lineLength * xf.q.c)));*/
//	b2Vec2 yAxis = xf.p + lineLength * xf.q.GetYAxis();
//	Vector2 ya = gdata.toScreenPixels(yAxis);
//	sf::Vertex greenLine[] =
//	{
//		sf::Vertex(sf::Vector2f(pos.x,pos.y), sf::Color::Green),
//		sf::Vertex(sf::Vector2f(ya.x,ya.y), sf::Color::Green)
//	};
//
//	gdata.window->draw(redLine, 2, sf::Lines);
//	gdata.window->draw(greenLine, 2, sf::Lines);
}

void VisualDebugger::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    Vector2 point1 = gdata.toScreenPixels(p1);
    Vector2 point2 = gdata.toScreenPixels(p2);

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(point1.x,point1.y),B2SFColor(color)),
        sf::Vertex(sf::Vector2f(point2.x,point2.y),B2SFColor(color))
    };

    gdata.window->draw(line,2,sf::Lines);
}

void VisualDebugger::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    //no converion in cordinates of center and upper left corner, Circle in sfml is managed by default with the center
    sf::CircleShape circle = sf::CircleShape( (radius * WORLD_SCALE) * gdata.zoom );
    circle.setOrigin(circle.getRadius(),circle.getRadius());
    circle.setFillColor(B2SFColor(color));

    Vector2 c = gdata.toScreenPixels(center);
    Vector2 p = gdata.toScreenPixels(center + (radius * axis));

    circle.setPosition(c.x,c.y);

    // line of the circle wich shows the angle
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(c.x,c.y),B2SFColor(color)),
        sf::Vertex(sf::Vector2f(p.x,p.y),B2SFColor(color))
    };

    gdata.window->draw(circle);
    gdata.window->draw(line,2,sf::Lines);
}

void VisualDebugger::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
        //no converion in cordinates of center and upper left corner, Circle in sfml is managed by default with the center
    sf::CircleShape circle = sf::CircleShape(radius * WORLD_SCALE);
    circle.setOrigin(circle.getRadius(),circle.getRadius());
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(B2SFColor(color));

    Vector2 c = gdata.toScreenPixels(center);
    circle.setPosition(c.x,c.y);

    gdata.window->draw(circle);
}

void VisualDebugger::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon(vertexCount);
	sf::Vector2f center;
	for(int i = 0; i < vertexCount; i++)
	{
		//polygon.setPoint(i, SFMLDraw::B2VecToSFVec(vertices[i]));
		Vector2 v = gdata.toScreenPixels(vertices[i]);
		sf::Vector2f transformedVec = sf::Vector2f(v.x,v.y);
		polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y))); // flooring the coords to fix distorted lines on flat surfaces
	}																								   // they still show up though.. but less frequently
	polygon.setOutlineThickness(-1.f);
	polygon.setFillColor(sf::Color::Transparent);
	polygon.setOutlineColor(B2SFColor(color));

	gdata.window->draw(polygon);
}
void VisualDebugger::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::ConvexShape polygon(vertexCount);
	for(int i = 0; i < vertexCount; i++)
	{
		//polygon.setPoint(i, SFMLDraw::B2VecToSFVec(vertices[i]));
		Vector2 v = gdata.toScreenPixels(vertices[i]);
		sf::Vector2f transformedVec = sf::Vector2f(v.x,v.y);
		polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y))); // flooring the coords to fix distorted lines on flat surfaces
	}																								   // they still show up though.. but less frequently
	polygon.setOutlineThickness(-1.f);
	polygon.setFillColor(B2SFColor(color, 60));
	polygon.setOutlineColor(B2SFColor(color));

	gdata.window->draw(polygon);
}

void VisualDebugger::DrawMouseJoint(b2Vec2& p1, b2Vec2& p2, const b2Color &boxColor, const b2Color &lineColor)
{
//    sf::Shape polygon;
//    sf::Shape polygon2;
//    float p1x = p1.x * RATIO;
//    float p1y = p1.y * RATIO;
//    float p2x = p2.x * RATIO;
//    float p2y = p2.y * RATIO;
//    float size = 4.0f;
//
//    sf::Color boxClr = this->B2SFColor(boxColor);
//    sf::Color lineClr = this->B2SFColor(lineColor);
//
//    //first green box for the joint
//    polygon.AddPoint(p1x-size/2, p1y-size/2, boxClr);
//    polygon.AddPoint(p1x+size/2, p1y-size/2, boxClr);
//    polygon.AddPoint(p1x+size/2, p1y+size/2, boxClr);
//    polygon.AddPoint(p1x-size/2, p1y+size/2, boxClr);
//
//    //second green box for the joint
//    polygon2.AddPoint(p2x-size/2, p2y-size/2, boxClr);
//    polygon2.AddPoint(p2x+size/2, p2y-size/2, boxClr);
//    polygon2.AddPoint(p2x+size/2, p2y+size/2, boxClr);
//    polygon2.AddPoint(p2x-size/2, p2y+size/2, boxClr);
//
//    sf::Shape line = sf::Shape::Line(p1x, p1y, p2x, p2y, 1, lineClr);
//    line.EnableFill(true);
//
//    this->window->Draw(polygon);
//    this->window->Draw(polygon2);
//    this->window->Draw(line);
}
/*void VisualDebugger::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
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
*/
