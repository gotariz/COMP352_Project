#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include <vector>
using namespace std;
class Object;
#include "utils/Vector2.h"


struct CollisionData
{
    Object* objectB = nullptr;
    vector<Vector2> points;
    vector<Vector2> normals;
};

struct KeyboardKey
{
   sf::Keyboard::Key   m_key;
   int                 m_code;
   std::string         m_name;

   bool        isKeyDown = false;
   bool        isKeyPressed = false;
   bool        isKeyReleased = false;

   void updateKey(bool isDown)
   {
       isKeyPressed     = (!isKeyDown && isDown);
       isKeyReleased    = (isKeyDown && !isDown);
       isKeyDown        = isDown;
   }

   KeyboardKey(int code = sf::Keyboard::Unknown, std::string name = "Unknown") : m_code(code), m_name(name)
   {
       if (code >= 0 && code <= sf::Keyboard::KeyCount)
           m_key = static_cast<sf::Keyboard::Key>(code);
       else
           m_key = sf::Keyboard::Unknown;
   }
};

#endif // STRUCTS_H_INCLUDED
