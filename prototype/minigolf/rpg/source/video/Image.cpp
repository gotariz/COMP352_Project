#include "Image.h"

void Image::freeTexture()
{
	if (texture != nullptr) SDL_DestroyTexture(texture);
}

bool Image::loadTexture(string filename)
{
	texture = IMG_LoadTexture(gdata.renderer, filename.c_str());
	if (texture == nullptr)
	{
		cout << "LoadTexture Error:" << SDL_GetError() << endl;
		return false;
	}

	SDL_QueryTexture(texture, NULL, NULL, &src_rec.w, &src_rec.h);
	src_rec.x = 0;
	src_rec.y = 0;

	dst_rec.x = 0;
	dst_rec.y = 0;
	dst_rec.w = src_rec.w;
	dst_rec.h = src_rec.h;
	
	w = src_rec.w;
	h = src_rec.h;

	rotation_point.x = static_cast<float>(w) / 2.f;
	rotation_point.y = static_cast<float>(h) / 2.f;

	return true;
}

void Image::setTexture(SDL_Texture* t)
{
	texture = t;

	SDL_QueryTexture(texture, NULL, NULL, &src_rec.w, &src_rec.h);
	src_rec.x = 0;
	src_rec.y = 0;

	dst_rec.x = 0;
	dst_rec.y = 0;
	dst_rec.w = src_rec.w;
	dst_rec.h = src_rec.h;

	w = src_rec.w;
	h = src_rec.h;

	rotation_point.x = static_cast<float>(w) / 2.f;
	rotation_point.y = static_cast<float>(h) / 2.f;
}

void Image::renderImage(SDL_Renderer* renderer)
{
	SDL_RenderCopyEx(
		renderer, 
		texture,
		&src_rec, 
		&dst_rec,
		-angle,
		&rotation_point,
		SDL_FLIP_NONE
		);
}

void Image::renderImage(SDL_Renderer* renderer, int x, int y)
{
	SDL_Rect d;
	d.x = x;
	d.y = y;
	d.w = dst_rec.w;
	d.h = dst_rec.h;

	SDL_RenderCopyEx(
		renderer,
		texture,
		&src_rec,
		&d,
		-angle,
		&rotation_point,
		SDL_FLIP_NONE
		);
}

void Image::renderImage(SDL_Renderer* renderer, int x, int y, float nangle)
{
	SDL_Rect d;
	d.x = x;
	d.y = y;
	d.w = dst_rec.w;
	d.h = dst_rec.h;

	SDL_RenderCopyEx(
		renderer,
		texture,
		&src_rec,
		&d,
		-nangle,
		&rotation_point,
		SDL_FLIP_NONE
		);
}

void Image::renderImage(SDL_Renderer* renderer, int x, int y, int w, int h)
{
	SDL_Rect d;
	d.x = x;
	d.y = y;
	d.w = w;
	d.h = h;

	SDL_RenderCopyEx(
		renderer,
		texture,
		&src_rec,
		&d,
		-angle,
		&rotation_point,
		SDL_FLIP_NONE
		);
}

void Image::renderImage(SDL_Renderer* renderer, int x, int y, int w, int h, float nangle)
{
	SDL_Rect d;
	d.x = x;
	d.y = y;
	d.w = w;
	d.h = h;

	SDL_RenderCopyEx(
		renderer,
		texture,
		&src_rec,
		&d,
		-nangle,
		&rotation_point,
		SDL_FLIP_NONE
		);
}

void Image::setX(int x)
{
	dst_rec.x = x;
}

void Image::setY(int y)
{
	dst_rec.y = y;
}

void Image::setPosition(int x, int y)
{
	dst_rec.x = x;
	dst_rec.y = y;
}

int Image::getWidth()
{
	return w;
}

int Image::getHeight()
{
	return h;
}
