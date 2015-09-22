#include "Laser.h"

Laser::Laser()
{
    //ctor
    emitter.frequency = 60;
    emitter.duration = 375;
    emitter.speed = 5;
    emitter.size = 1;
    emitter.enabled = true;

    laser_beam.setTexture(*gdata.assets->getTexture("laser_beam"));
    laser_beam.setOrigin(0,7);
    laser_end.setTexture(*gdata.assets->getTexture("laser_end"));
    laser_end.setOrigin(0,7);

    laser_dir.set(1,0);
}

Laser::~Laser()
{
    //dtor
}

void Laser::rotateLaser()
{
    if (!rotating) return;

    float unit_time = (r_time / r_duration);
    if (m_enabledRotation)
    {
        if (increasing) {
            r_time += gdata.m_timeDelta;
            if (unit_time >= 1) {
                unit_time = 1;
                increasing = false;
            }
        } else {
            r_time -= gdata.m_timeDelta;
            if (unit_time <= 0) {
                unit_time = 0;
                increasing = true;
            }
        }
    }

    float new_angle = start_angle + (delta_angle * unit_time);
    rotated_laser = laser_dir;
    rotated_laser.rotate(new_angle);
    rotation = new_angle;

}

void Laser::moveLaser()
{
    if (!m_enabledMovement || !m_moving) return;

    Vector2 delta;
    Vector2 dist_v = m_point2 - m_point1;
    float dist = dist_v.getMagnitude();

    delta = dist_v;
    delta.normalise();
    delta.setMagnitude(dist * (m_time / m_duration));

    if (m_dest == m_point1) // time is increasing
    {
        m_time += gdata.m_timeDelta;
        if (m_time >= m_duration)
        {
            m_time = m_duration - (m_time - m_duration);
            m_dest = m_point2;
        }
    }
    else if (m_dest == m_point2)
    {
        m_time -= gdata.m_timeDelta;
        if (m_time <= 0)
        {
            m_time = 0 - m_time;
            m_dest = m_point1;
        }
    }

    laserPos.set(m_point1 + delta);
}

void Laser::raycast()
{
    b2Vec2 p1 = laserPos.toBulletVector();
	float rayLength = 50;

    rotated_laser.normalise(); // very important

	b2RayCastInput	input;
	input.p1 = p1;
	input.p2 = b2Vec2(p1.x + rotated_laser.x, p1.y + rotated_laser.y);
	input.maxFraction = rayLength;

	float closest_fraction = rayLength;
	b2Body* body = nullptr;
	for (b2Body* b = gdata.world->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
		    int categoryBits = f->GetFilterData().categoryBits;

		    if (categoryBits != CF_PARTICLE && categoryBits != CF_NONE && !f->IsSensor())
			{
			    b2RayCastOutput output;
                if (!f->RayCast(&output, input, 0)) continue;
                if (output.fraction < closest_fraction)
                {
                    closest_fraction = output.fraction;
                    body = b;
                    emitter.dir = Vector2(output.normal);
                }
			}
		}

	}


	if (body != nullptr && body->GetUserData() != nullptr)
	{
		Object* p = static_cast<Object*>(body->GetUserData());

		if (body->GetUserData() != nullptr && p->m_type == PLAYER)
		{
		    if (gdata.countdown <= 0)
			{
			    cout << "you died" << endl;
                static_cast<Object*>(body->GetUserData())->onDestroy();
                //gdata.countdown = 60.f;
			}
		}
	}

	laser = rotated_laser;
	laser.setMagnitude(closest_fraction);
}


void Laser::onUpdate()
{
    rotated_laser = laser_dir;
    rotated_laser.rotate(rotation);
    rotateLaser();
    moveLaser();

    if (m_enabled)
    {
        raycast();
    }

    emitter.pos = laserPos + laser;
    emitter.update();
    emitter.enabled = m_enabled;
}

void Laser::onDraw()
{
    if (m_enabled)
    {
        Vector2 s = gdata.toScreenPixels(laserPos.x,laserPos.y);
        Vector2 e = gdata.toScreenPixels(laserPos + laser);

        float length = laser.getMagnitude();
        float rot = (float)atan2(laser.y,laser.x);
        rot *= RADTODEG;
        rot *= -1;

        laser_beam.setScale(length * gdata.zoom,gdata.zoom);
        laser_beam.setRotation(rot);
        laser_beam.setPosition(s.x,s.y);
        laser_end.setScale(gdata.zoom,gdata.zoom);
        laser_end.setPosition(e.x,e.y);
        laser_end.setRotation(rot);

        gdata.window->draw(laser_beam);
        gdata.window->draw(laser_end);

        laser_head.setRotation(-rotation);
        laser_head.setPosition(s.x,s.y);
        laser_head.setScale(gdata.zoom,gdata.zoom);

        gdata.window->draw(laser_head);
    }

    emitter.drawParticles();
}

void Laser::freeResources()
{
    deletePhysicsObject();
    emitter.freeResources();
}







