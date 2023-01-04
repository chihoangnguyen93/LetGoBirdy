//
//  GameContactListener.cpp
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#include "GameContactListener.h"
#include "Character.h"
#include "BranchTree.h"
#include "Ground.h"
#include "GameConfig.h"

GameContactListener::GameContactListener() {}

void GameContactListener::setDelegate(GameContactListenerDelegate *delegate) {
  this->delegate = delegate;
}

void GameContactListener::BeginContact(b2Contact *contact) {
  if (contact && contact->IsTouching()) {
    b2Body *bodyA = contact->GetFixtureA()->GetBody();
    b2Body *bodyB = contact->GetFixtureB()->GetBody();
    Character *character = dynamic_cast<Character *>((Ref *) bodyA->GetUserData());
    if (character) {
      processCollisionCharacterVsOther(bodyA, bodyB);
    } else {
      processCollisionCharacterVsOther(bodyB, bodyA);
    }
  }
}

void GameContactListener::EndContact(b2Contact *contact) {}

void GameContactListener::processCollisionCharacterVsOther(b2Body *characterBody, b2Body *otherBody) {
  Character *character = (Character *) characterBody->GetUserData();
  uint16 categoryBits = otherBody->GetFixtureList()[0].GetFilterData().categoryBits;
  if (categoryBits == kGroundCatBit) {
    if (character->getStatus() != JUMP) { return; }
    Ground *ground = (Ground *) otherBody->GetUserData();
    character->didWalk(WALK_ON_GROUND, ground->getContentSize().height - CHARACTER_Y_BUFFER);
  } else if (categoryBits == kBranchTreeCatBit) {
    if (character->getStatus() != JUMP) { return; }
    BranchTree *branchTree = (BranchTree *) otherBody->GetUserData();
    processCollisionCharacterVsBranchTree(character, branchTree);
  } else if (categoryBits == kMonsterCatBit) {
    character->didDie();
    delegate->eventCharacterContactWithMonster();
  }
}

void GameContactListener::processCollisionCharacterVsBranchTree(Character *character, BranchTree *branchTree) {
  float yFootCharacterPosition = character->getPositionY() - character->getContentSize().height/2.0;
  float yBranchTreePosition = branchTree->getPositionY() + BRANCH_TREE_RATIO_HEIGHT_BODY / 2.0 * branchTree->getContentSize().height;
  if (yFootCharacterPosition > yBranchTreePosition) {
    float walkPosition = branchTree->getPositionY() + branchTree->getContentSize().height - 12.0;
    character->didWalk(WALK_ON_BRANCH_TREE, walkPosition);
  }
}
