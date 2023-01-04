//
//  GroundManager.h
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#ifndef GroundManager_h
#define GroundManager_h

#include "cocos2d.h"
#include "Ground.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;
using namespace std;

class GroundManager {
private:
  vector<Ground *> listGround;
  Size contentSize;
  Layer *parentLayer;
public:
  GroundManager(Layer *parentLayer);
  
  virtual ~GroundManager();
  
  void setUp(b2World *physicWorld, const Vec2 position);
  
  void update(float dt);
  
  Size getContentSize();
};

#endif /* GroundManager_h */
