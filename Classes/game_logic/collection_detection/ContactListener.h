//
//  ContactListener.h
//  AngryPanda
//
//  Created by renxueaiw on 13-12-24.
//
//

#ifndef __AngryPanda__ContactListener__
#define __AngryPanda__ContactListener__

#include "Box2D.h"
#include "../../game_assist/game_audio_manager/GameSounds.h"

class ContactListener: public b2ContactListener
{
private:
    void BeginContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    void EndContact(b2Contact* contact);
};

#endif /* defined(__AngryPanda__ContactListener__) */
