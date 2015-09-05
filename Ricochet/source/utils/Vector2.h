#ifndef VECTOR2_H
#define VECTOR2_H

//using sqrt;
//#include "general.h"
#include "dependencies.h"
#include "consts.h"

class Vector2
{
    public: //constructors & destructors
        Vector2(){}
        Vector2(const char* vectorString);
        Vector2(b2Vec2 bullet_vector);
        Vector2(float xval, float yval);
        virtual ~Vector2();

    public: // variables
        float x = 0;
        float y = 0;

    public: // functions
        float   getMagnitude();
        Vector2 getNormalised();
        b2Vec2  toBulletVector();
        sf::Vector2f  toSfmlVector();
        float getAngle();

        void    rotate(float angle);
        void    rotateAround(float angle, Vector2 vec);
        void    rotateAround(float angle, float origin_x, float origin_y);
        void    normalise();
        void    setMagnitude(float magnitude);
        void    set(float xval, float yval);
        void    set(Vector2 vectorToCopy);

        void    print(std::string name);

    public: // operators
        void operator=(Vector2 vec);
        bool operator==(Vector2 vec);
        bool operator!=(Vector2 vec);

        Vector2 operator+(Vector2 vec);
        Vector2 operator-(Vector2 vec);
        Vector2 operator*(Vector2 vec);
        Vector2 operator/(Vector2 vec);
        Vector2 operator+(float scalar);
        Vector2 operator-(float scalar);
        Vector2 operator*(float scalar);
        Vector2 operator/(float scalar);

        void operator+=(Vector2 vec);
        void operator-=(Vector2 vec);
        void operator*=(Vector2 vec);
        void operator/=(Vector2 vec);
        void operator+=(float scalar);
        void operator-=(float scalar);
        void operator*=(float scalar);
        void operator/=(float scalar);
};

#endif // VECTOR2_H
