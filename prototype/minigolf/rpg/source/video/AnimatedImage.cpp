#include "AnimatedImage.h"

void AnimatedImage::start()
{
	m_playing = true;
}

void AnimatedImage::stop()
{
	m_playing = false;
}

void AnimatedImage::reset()
{
	m_frameIndex = 0;
	m_elapsedTime = 0;
	m_finished = false;
}

void AnimatedImage::initialise()
{

}

void AnimatedImage::update()
{
	m_elapsedTime += gdata.m_timeDelta;// *m_speed;
	updateFrame();
}

void AnimatedImage::updateFrame()
{
	if (!m_playing || m_finished) return;

	// only update 
	if (m_frames.size() > 0 && m_animationSequence.size() > 0)
	{
		Frame& frame = m_frames.at(m_animationSequence.at(m_frameIndex));
		if (frame.m_duration >0 && m_elapsedTime >= frame.m_duration)
		{
			m_elapsedTime -= frame.m_duration;

			if (m_frameIndex == static_cast<int>(m_animationSequence.size()) - 1)
			{
				if (m_loop)	m_frameIndex = 0;
				else		m_finished = true;
			}
			else
			{
				++m_frameIndex;
			}

			updateFrame();// keep updating frame until m_elapsedTime < frame.m_duration
		}

	}
}

void AnimatedImage::renderImage(SDL_Renderer* renderer)
{
	Image* img = m_frames.at(m_animationSequence.at(m_frameIndex)).m_frame;
	img->renderImage(renderer, m_position.x, m_position.y, img->getWidth() * m_scale.x, img->getHeight() * m_scale.y,  m_angle);
}
