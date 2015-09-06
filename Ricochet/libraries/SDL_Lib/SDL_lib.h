#ifndef SDL_LIB_H
#define SDL_LIB_H

#include <string>
#include <iostream>

#include "SDL.h"
#include "SDL_Image.h"
//#include "sdlFont.h"

using namespace std;

namespace SDLib
{
	static SDL_Texture* loadTexture(string filename, SDL_Renderer* ren);

	static SDL_Texture* loadTexture(string filename, SDL_Renderer* ren)
	{
		SDL_Texture* texture = IMG_LoadTexture(ren, filename.c_str());
		if (texture == nullptr)
		{
			cout << "load texture error:" << SDL_GetError() << endl;
		}
		return texture;
	}
}

#endif // SDL_LIB_H

