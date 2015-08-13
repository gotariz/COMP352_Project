#include "Player.h"

Player::Player(int id) : Object(id)
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::setMoveDirection(Vector2 direction)
{
   //moveDirection.set(direction);
}

void Player::onPrePhysicsUpdate()
{
    //if (moveDirection.getMagnitude() != 0)
    //{
    //    m_physicsObject->SetLinearDamping(0);
    //    Vector2 currentVelocity = Vector2(m_physicsObject->GetLinearVelocity());
    //    Vector2 velocity = currentVelocity + (moveDirection * (acceleration * gdata.m_timeDelta));

    //    if (velocity.getMagnitude() > maxMoveSpeed) {
    //        velocity.setMagnitude(maxMoveSpeed);
    //    }

    //    setLinearVelocity(velocity);
    //}
    //else
    //{
    //    m_physicsObject->SetLinearDamping(decceleration);
    //}
}

void Player::onPostPhysicsUpdate()
{
	//gdata.camera->m_x = getAbsolutePosition().x;// -(gdata.camera->m_w / 2);
	//gdata.camera->m_y = getAbsolutePosition().y;// -(gdata.camera->m_h / 2);
}

void Player::onEnterCollision(Object* objectB)
{
	if (objectB->m_type == HOLE)
	{
		cout << "You win!" << endl;
	}
}

void Player::onExitCollision(Object* objectB)
{

}

void Player::flap()
{
	m_physicsObject->SetLinearVelocity(b2Vec2(0, -30));
	m_physicsObject->ApplyLinearImpulse(b2Vec2(0, 33.5), m_physicsObject->GetWorldCenter(),true);
}

void Player::applyImpulse(Vector2 impulse)
{
	m_physicsObject->ApplyLinearImpulse(b2Vec2(impulse.x, impulse.y), m_physicsObject->GetWorldCenter(), true);
}

