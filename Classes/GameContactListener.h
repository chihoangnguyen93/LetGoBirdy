//
//  GameContactListener.h
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#ifndef GameContactListener_h
#define GameContactListener_h

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Character.h"
#include "BranchTree.h"
#include "GameContactListenerDelegate.h"

class GameContactListener : public b2ContactListener {
private:
  GameContactListenerDelegate *delegate;
  void processCollisionCharacterVsBranchTree(Character *character, BranchTree *branchTree);
public:
  GameContactListener();
  
  void setDelegate(GameContactListenerDelegate *delegate);
  
  void BeginContact(b2Contact *contact);
  
  void EndContact(b2Contact *contact);
  
  void processCollisionCharacterVsOther(b2Body *characterBody, b2Body *otherBody);
};

#endif /* GameContactListener_h */
