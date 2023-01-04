//
//  GameManager.h
//  LetGoBirdy
//
//  Created by Harry Nguyen on 25/12/22.
//

#ifndef GameManager_h
#define GameManager_h

#include "cocos2d.h"
#include "GroundManager.h"
#include "MonsterManager.h"
#include "Character.h"
#include "BranchTreeManager.h"

using namespace cocos2d;
using namespace std;

class GameManager {
private:
  GroundManager *groundManager;
  MonsterManager *monsterManager;
  BranchTreeManager *branchTreeManager;
  Character *character;
  void checkFallDownFromBranchTreeToGround();
public:
  GameManager();
  
  virtual ~GameManager();
  
  void update(float dt);
  
  void setObjects(GroundManager *groundManager,
                  MonsterManager *monsterManager,
                  BranchTreeManager *branchTreeManager,
                  Character *character);
  
  void didTouchOneByOneBegan();
};


#endif /* GameManager_h */
