#ifndef IMAGE_H
#define IMAGE_H

#include "system/GameData.h"
#include "general.h"

class Image
{
	public:
		Image(){}
		virtual ~Image(){}

		SDL_Rect src_rec;
		SDL_Rect dst_rec;
		SDL_Point rotation_point;

		float scale_x = 1.f;
		float scale_y = 1.f;

		float angle = 0.f;

	public:

		void freeTexture();

		int getWidth();
		int getHeight();

		void setX(int x);
		void setY(int y);
		void setPosition(int x, int y);

		bool loadTexture(string filename);
		void setTexture(SDL_Texture* t);

		void renderImage(SDL_Renderer* renderer);
		void renderImage(SDL_Renderer* renderer, int x, int y);
		void renderImage(SDL_Renderer* renderer, int x, int y, float nangle);
		void renderImage(SDL_Renderer* renderer, int x, int y, int w, int h);
		void renderImage(SDL_Renderer* renderer, int x, int y, int w, int h, float nangle);

	protected:
		int w = 0;
		int h = 0;
		SDL_Texture* texture = nullptr;


};

#endif // IMAGE_H
