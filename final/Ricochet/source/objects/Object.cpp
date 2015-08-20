#include "Object.h"

Object::Object(int id) : m_id(id)
{
    //ctor
}

Object::~Object()
{
    //dtor
}

void Object::onCreate()
{

}

void Object::onDestroy()
{

}

void Object::onCollision(Object* objectB)
{

}

void Object::onUpdate()
{

}

void Object::onPrePhysicsUpdate()
{
}

void Object::onPostPhysicsUpdate()
{
    syncChildren();
}

void Object::onEnterCollision(Object* objectB)
{
}

void Object::onExitCollision(Object* objectB)
{
}

void Object::setPhysicsObject(b2Body* physicsObject)
{
    m_physicsObject = physicsObject;
    m_physicsObject->SetUserData(this);
}

void Object::onDraw()
{
    if (m_image.getTexture() != nullptr)
    {
		Vector2 pos = getAbsolutePosition();
		pos = gdata.toPixels(pos.x, pos.y);
		pos.x -= gdata.camera->getScreenX();
		pos.y -= gdata.camera->getScreenY();
		m_image.setScale(gdata.zoom,gdata.zoom);
		m_image.setRotation(getAbsoluteRotation());
        gdata.window->draw(m_image);
    }
}

vector<Object*>	Object::getChildren()
{
	return m_children;
}

void Object::syncWithParent()
{
    float   deltaRotation = m_parent->getAbsoluteRotation() - parentPrimalRotation;
    Vector2 deltaPosition = m_parent->getAbsolutePosition() - parentPrimalPosition;

    setAbsoluteRotation(getAbsoluteRotation() + deltaRotation);

    // the rotation will affect the position
    Vector2 rotatedPosition = getAbsolutePosition() + deltaPosition;
    rotatedPosition.rotateAround(deltaRotation,m_parent->getAbsolutePosition());

    setAbsolutePosition(rotatedPosition);

    parentPrimalRotation = m_parent->getAbsoluteRotation();
    parentPrimalPosition = m_parent->getAbsolutePosition();
}

void Object::syncChildren()
{
    for (Object* c: m_children)
    {
        c->syncWithParent();
        c->syncChildren();
    }
}

void Object::addChild(Object* child)
{
    if (child->m_physicsObject->GetType() != b2_dynamicBody)
    {
        bool alreadyChild = false;
        for (unsigned i = 0; i < m_children.size(); ++i)
        {
            Object* object = m_children.at(i);
            if (object == child) {alreadyChild = true;}
        }

        if (!alreadyChild)
        {
            child->m_parent = this;
            m_children.push_back(child);

            child->parentPrimalRotation = getAbsoluteRotation();
            child->parentPrimalPosition = getAbsolutePosition();
        }
    }
}

void Object::moveTo(Vector2 newPosition)
{
    Vector2 delta = newPosition - getAbsolutePosition();
    moveDistance(delta);
}

int Object::getID()
{
    return m_id;
}


// postion AND rotation =============================================================
Vector2 Object::getPosition()
{
    Vector2 result;
    if (m_parent)
    {
        result = getAbsolutePosition() - m_parent->getAbsolutePosition();
        result.rotateAround( -m_parent->getAbsoluteRotation(), Vector2(0,0) );
    }
    else
    {
        result = getAbsolutePosition();
    }

    return result;
}

Vector2 Object::getAbsolutePosition()
{
    if (m_physicsObject)
        return Vector2(m_physicsObject->GetPosition());
    else
        return Vector2(0,0); // FIX THIS
}

float Object::getRotation()
{
    float result = getAbsoluteRotation();
    if (m_parent)
        result -= m_parent->getAbsoluteRotation();

    return utils::toAngle(result);
}

float Object::getAbsoluteRotation()
{
    return utils::toAngle( m_physicsObject->GetAngle() * RADTODEG );
}

void Object::setRotation(float angle)
{
    if (m_physicsObject)
    {
        if (m_parent)
            angle += m_parent->getAbsoluteRotation();

        float safe_angle = utils::toAngle(angle);
        safe_angle *= DEGTORAD;

        m_physicsObject->SetTransform( m_physicsObject->GetPosition(), safe_angle );
    }
}

void Object::setAbsoluteRotation(float newAngle)
{
    float safe_angle = utils::toAngle(newAngle);
    m_physicsObject->SetTransform( m_physicsObject->GetPosition(), safe_angle * DEGTORAD);
}

void Object::setPosition(Vector2 newPosition)
{
    if (m_parent)
    {
        newPosition.rotateAround( m_parent->getAbsoluteRotation(), Vector2(0,0) );
        newPosition += m_parent->getAbsolutePosition();
    }

    setAbsolutePosition( newPosition );
}

void Object::setAbsolutePosition(Vector2 newPosition)
{
    m_physicsObject->SetTransform( newPosition.toBulletVector(), m_physicsObject->GetAngle() );
}



//================================================================================

void Object::moveDistance(Vector2 delta)
{
    float angle = 0;
    if (m_parent != nullptr)
    {
        angle = m_parent->getAbsoluteRotation();
    }

    //delta.rotateAround(angle,Vector2(0,0));
    Vector2 absoluteDelta = delta;
    absoluteDelta.rotateAround(angle,0,0);

    m_physicsObject->SetTransform( (getAbsolutePosition() + absoluteDelta).toBulletVector() , m_physicsObject->GetAngle() );

    for (unsigned i = 0; i < m_children.size(); ++i)
    {
        Object* child = m_children.at(i);
        if (!child->m_independent)
        {
            child->moveAbsoluteDistance(delta);
        }
    }
}

// this should be renamed moveAbsoluteDistance
void Object::moveAbsoluteDistance(Vector2 delta)
{
    m_physicsObject->SetTransform( (getAbsolutePosition() + delta).toBulletVector() , m_physicsObject->GetAngle() );

    // set position and target positions for children objects
    for (unsigned i = 0; i < m_children.size(); ++i)
    {
        Object* child = m_children.at(i);
        if (!child->m_independent)
        {
            child->moveAbsoluteDistance(delta);
        }
    }
}

void Object::applyImpulse(Vector2 impulseForce)
{
    m_physicsObject->ApplyForceToCenter(impulseForce.toBulletVector(),true);
}

void Object::setLinearVelocity(Vector2 linearVelocity)
{
    m_physicsObject->SetLinearVelocity(linearVelocity.toBulletVector());
}


//=================================================================================
//=================================================================================

void Object::translate(Vector2 delta)
{
    if (!m_independent)
    {
        setAbsolutePosition( getAbsolutePosition() + delta );
        for (unsigned i = 0; i < m_children.size(); ++i)
        {
            Object* child = m_children.at(i);
            child->translate( delta );
        }
    }
}

void Object::translateChildren(Vector2 delta)
{
    for (unsigned i = 0; i < m_children.size(); ++i)
    {
        Object* child = m_children.at(i);
        child->translate( delta );
    }
}

void Object::rotateAround(float angle, Vector2 origin)
{
    Vector2 oldPos = getAbsolutePosition();
    Vector2 newPos = getAbsolutePosition();
    newPos.rotateAround(angle,origin);

    setAbsolutePosition(newPos);

    translateChildren( newPos - oldPos );
}

void Object::rotate(float angle)
{
    float rot = getRotation();
    float fullAngle = (rot + angle);

    setRotation(fullAngle);

    for (unsigned i = 0; i < m_children.size(); ++i)
    {
        Object* child = m_children.at(i);

        if (!child->m_independent)
        {
            if (!child->m_lockRotation) {child->rotate(angle);}
            if (!child->m_lockPosition) {child->rotateAround(angle,getAbsolutePosition());}
        }
    }
}

void Object::deletePhysicsObject()
{
	if (m_physicsObject != nullptr)
	{
		m_physicsObject->GetWorld()->DestroyBody(m_physicsObject);
	}
}
