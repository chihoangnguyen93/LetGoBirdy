//
//  MonsterManager.h
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#ifndef MonsterManager_h
#define MonsterManager_h

#include "cocos2d.h"
#include "Monster.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;
using namespace std;

class MonsterManager {
private:
  Size visibleSize;
  vector<Monster *> listMonster;
  Layer *parentLayer;
  float widthContent;
public:
  MonsterManager(Layer *parentLayer);
  
  virtual ~MonsterManager();
  
  void setUp(b2World *physicWorld, float yPosition);
  
  void update(float dt);
};

#endif /* MonsterManager_h */
