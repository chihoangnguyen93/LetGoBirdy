//
//  Character.h
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#ifndef Character_h
#define Character_h

#include "cocos2d.h"
#include <spine/spine-cocos2dx.h>
#include <Box2D/Box2D.h>

using namespace cocos2d;
using namespace spine;

class Character : public Node {
private:
  Size visibleSize;
  int status;
  b2Body *body;
  SkeletonAnimation *skeleton;
  float walkYPosition;
public:
  Character();
  
  virtual ~Character();
  
  void update(float dt);
  
  void didWalk(int walkType, float yPosition);
  
  void didJump();
  
  void didDie();
  
  void runWalkAnimation();
  
  void buildPhysicBody(b2World *physicWorld);
  
  int getStatus();
  
  void fallDownFromBranchTreeToGround();
};


#endif /* Character_h */
