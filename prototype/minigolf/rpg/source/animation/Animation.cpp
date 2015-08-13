#include "Animation.h"

Animation::Animation()
{
    //ctor
}

Animation::~Animation()
{
    //dtor
}

void Animation::start()
{
    m_isRunning = true;
    m_isEnded   = false;

    // originalPosition
    // originalRotation
}

void Animation::pause()
{
    m_isRunning = false;
}

void Animation::resume()
{
    m_isRunning = true;
}

void Animation::hardReset()
{
    m_isRunning = false;
    m_isEnded = false;

    m_elapsedDuration = 0;
    m_elapsedLoops = 0;

    for (unsigned i = 0; i < m_actions.size(); ++i)
    {
        m_actions.at(i)->hardReset();
    }
}

std::vector<AnimationInstruction*> Animation::getInstructions()
{
    return m_actions;
}

void Animation::setInstructions(std::vector<AnimationInstruction*> actions)
{
    m_actions = actions;
}



void Animation::softReset()
{
    m_elapsedDuration = 0;

    for (unsigned i = 0; i < m_actions.size(); ++i)
    {
        m_actions.at(i)->hardReset();
    }
}

void Animation::update()
{
    if (!m_isRunning) return;
    bool loopFinished = true;

    for (unsigned i = 0; i < m_actions.size(); ++i)
    {
        AnimationInstruction& ai = *(m_actions.at(i));

        if ( !ai.getIsStarted() && m_elapsedDuration >= ai.m_startTime )
        {
            ai.m_isRunning = true;
            ai.m_isStarted = true;

            // convert to relative to parent and set start position
            Vector2 currentPosition = ai.m_relativeStartPosition ? m_object->getPosition() : Vector2(0,0);
            m_object->setPosition( currentPosition + ai.m_startPosition);
            ai.m_absoluteStartPosition = m_object->getPosition();

            // convert to relative to parent and set start rotation
            float currentRotation = ai.m_relativeStartRotation ? m_object->getRotation() : 0;
            m_object->setRotation(currentRotation + ai.m_startRotation);
            ai.m_absoluteStartRotation = m_object->getRotation();

            // convert to relative to parent
            Vector2 startPosition = ai.m_relativeEndPosition ? ai.m_absoluteStartPosition : Vector2(0,0);
            ai.m_absoluteEndPosition = startPosition + ai.m_endPosition;

            // convert to relative to parent
            float startRotation = ai.m_relativeEndRotation ? ai.m_absoluteStartRotation : 0;
            ai.m_absoluteEndRotation = startRotation + ai.m_endRotation;
        }

        if (ai.m_isRunning)
        {
            float deltaTime = gdata->m_timeDelta;

            if ( (ai.m_elapsedDuration += deltaTime) > ai.m_duration)
            {
                deltaTime -= ai.m_elapsedDuration - ai.m_duration;
                ai.m_elapsedDuration = ai.m_duration;
            }


            // move the required distance
            Vector2 delta = ai.m_absoluteEndPosition - ai.m_absoluteStartPosition;
            delta.setMagnitude( delta.getMagnitude() / ai.m_duration ); // this is the speed
            delta *= deltaTime;
            m_object->moveDistance(delta);

            // rotate the required angle
            float rotationDelta = ai.m_absoluteEndRotation - ai.m_absoluteStartRotation;
            if (ai.m_rotationMethod == 0)
            {
                if (rotationDelta < -180)       rotationDelta = 360 + rotationDelta;
                else if (rotationDelta > 180)   rotationDelta -= 360;
            }
            else if (ai.m_rotationMethod == 1)
            {
                if (rotationDelta < 0)  rotationDelta = 360 + rotationDelta;
            }
            else if (ai.m_rotationMethod == 2)
            {
                if (rotationDelta > 0)  rotationDelta = 360 - rotationDelta;
            }

            rotationDelta /= ai.m_duration;
            rotationDelta *= deltaTime;
            m_object->rotate(rotationDelta);

            m_elapsedDuration += deltaTime;

            // finalise the animation if it has ended
            if (ai.m_elapsedDuration >= ai.m_duration)
            {
                // this might cause probems when two animations are
                // making an object move to different locations
                m_object->setPosition(ai.m_absoluteEndPosition);
                m_object->setRotation(ai.m_absoluteEndRotation);
                //=================================================

                ai.m_isRunning = false;
                ai.m_isFinished = true;

                loopFinished = true;
                for (AnimationInstruction* in: m_actions)
                {
                    if (!in->m_isFinished) loopFinished = false;
                }

                if (loopFinished)
                {
                    ++m_elapsedLoops;

                    // check if we need to start another loop of the animation or finish
                    if (m_elapsedLoops < m_loops || m_loops == 0)
                    {
                        softReset();
                    }
                    else
                    {
                        m_isRunning = false;
                        if (m_reset){
                            m_object->setPosition(m_resetPosition);
                            m_object->setRotation(m_resetRotation);
                        }
                    }

                }
            }
        }
    }
}

void Animation::addAction(AnimationInstruction* ai)
{
    m_actions.push_back(ai);
}

void Animation::setObject(Object* obj)
{
    m_object = obj;
}
