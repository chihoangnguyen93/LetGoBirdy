//
//  Ground.h
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#ifndef Ground_h
#define Ground_h

#include "cocos2d.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;

class Ground : public Node {
private:
  Sprite *mainSprite;
  b2Body *body;
public:
  Ground();
  
  virtual ~Ground();
  
  void update(float dt);
  
  Size getContentSize();
  
  void buildPhysicBody(b2World *physicWorld);
};

#endif /* Ground_h */
