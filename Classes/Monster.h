//
//  Monster.h
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#ifndef Monster_h
#define Monster_h

#include "cocos2d.h"
#include <spine/spine-cocos2dx.h>
#include <Box2D/Box2D.h>

using namespace cocos2d;
using namespace spine;

class Monster : public Node {
private:
  b2Body *body;
  SkeletonAnimation *skeleton;
  
  void addPrisonOutSide(int type);
  
public:
  Monster(int type, bool imPrisoned);
  
  virtual ~Monster();
  
  void update(float dt);
  
  void buildPhysicBody(b2World *physicWorld);
};

#endif /* Monster_hpp */
