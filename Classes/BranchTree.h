//
//  BranchTree.h
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#ifndef BranchTree_h
#define BranchTree_h

#include "cocos2d.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;

class BranchTree : public Node {
private:
  Sprite *mainSprite;
  b2Body *surfaceBody;
public:
  BranchTree(int type);
  
  virtual ~BranchTree();
  
  void update(float dt);
  
  Size getContentSize();
  
  void buildPhysicBody(b2World *physicWorld);
};


#endif /* BranchTree_h */
