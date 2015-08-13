#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED


#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include <map>
#include <queue>

// third party libraries
#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_Mixer.h"
#include "SDL_Mixer.h"
#include "SDL2_gfxPrimitives.h"
#include "Box2D/Box2D.h"
#include "TinyXml2.h"

class Image;

struct guiEvent
{
    guiEvent(int a = -1, int b = -1) : id(a), type(b) {}

    int id;
    int type;
};

struct Frame
{
   int       m_duration;
   Image*    m_frame;

   Frame(int dur,Image* img) : m_duration(dur), m_frame(img){}
};

struct KeyboardKey
{
   SDL_Scancode	m_key;
   int			m_code;
   std::string	m_name;

   bool        isKeyDown = false;
   bool        isKeyPressed = false;
   bool        isKeyReleased = false;

   void updateKey(bool isDown)
   {
       isKeyPressed     = (!isKeyDown && isDown);
       isKeyReleased    = (isKeyDown && !isDown);
       isKeyDown        = isDown;
   }

   KeyboardKey(int code = SDL_SCANCODE_UNKNOWN, std::string name = "Unknown") : m_code(code), m_name(name) 
   {
	   if (code == 0  || (code >= 4 && code <= 103))
	   {
		   m_key = static_cast<SDL_Scancode>(code);
	   }
   }
};

#endif // STRUCTS_H_INCLUDED
