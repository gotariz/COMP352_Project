#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include "general.h"
#include "entities/Object.h"

class ContactListener : public b2ContactListener
{
    public:
        ContactListener();
        virtual ~ContactListener();

    public:

        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
};

#endif // CONTACTLISTENER_H
