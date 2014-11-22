#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include "Box2D\Box2D.h"
#include <vector>
#include <string>
using namespace std;

class ContactListener : public b2ContactListener
{
public:
        static ContactListener* instance;
        static ContactListener* getListener();
        ContactListener(void);
        ~ContactListener(void);
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void setWorld(b2World* world);
        static b2World* mWorld;
};

#endif