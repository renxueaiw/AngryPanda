//
//  ContactListener.cpp
//  AngryPanda
//
//  Created by renxueaiw on 13-12-24.
//
//

#include "ContactListener.h"
#include "../../game_data/game_constants/Constants.h"
#include "../../game_interface/game_main/MainScene.h"
#include "../../visual_element/physics_node/PhysicsNode.h"
#include "../../visual_element/panda/Panda.h"
#include "../../visual_element/ground_plane/GroundPlane.h"
#include "../../visual_element/fire_platform/FirePlatform.h"
#include "../../visual_element/stack_object/StackObject.h"
#include "../../visual_element/enemy/Enemy.h"
#include "../../game_data/game_state/GameData.h"
#include "SimpleAudioEngine.h"

//碰撞检测和处理机制
void ContactListener::BeginContact(b2Contact *contact)
{
    b2Body *bodyA = contact->GetFixtureA()->GetBody();
    b2Body *bodyB = contact->GetFixtureB()->GetBody();
    PhysicsNode *physicsNodeA = (PhysicsNode*)(bodyA->GetUserData());
    PhysicsNode *physicsNodeB = (PhysicsNode*)(bodyB->GetUserData());
    
    // 熊猫碰撞地平面上
    if ((typeid(physicsNodeA) == typeid(Panda)) && (typeid(physicsNodeB) == typeid(GroundPlane))) {
//        Panda *thePanda = (Panda*)physicsNodeA;
        
        
    }
}


void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    
}

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    
}

void ContactListener::EndContact(b2Contact *contact)
{
    
}
