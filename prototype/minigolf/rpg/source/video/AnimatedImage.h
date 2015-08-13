#pragma once
#include "general.h"
#include "Image.h"

class AnimatedImage
{
	public:
		AnimatedImage(){}
		virtual ~AnimatedImage(){}

	public: 
		virtual void initialise();
		virtual void update();
		virtual void updateFrame();
		virtual void renderImage(SDL_Renderer* renderer);

		virtual void start();
		virtual void stop();
		virtual void reset();
	
	public:
		
		Vector2		m_position;
		Vector2		m_scale = Vector2(1,1);
		float		m_angle = 0;

		bool		m_playing = false;
		bool		m_loop = false;
		bool		m_finished = false;
		float		m_speed = 1.0f;

		int			m_frameIndex = 0;
		int			m_elapsedTime = 0;

		vector<Frame>	m_frames;
		vector<int>		m_animationSequence;
};

