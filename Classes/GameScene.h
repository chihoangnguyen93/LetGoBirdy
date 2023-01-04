//
//  GameScene.h
//  LetGoBirdy
//
//  Created by Harry Nguyen on 2/14/17.
//
//

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
#include "GameContactListenerDelegate.h"
#include "GameManager.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;

class GameScene : public Layer, GameContactListenerDelegate {
private:
  Size visibleSize;
  b2World *physicWorld = nullptr;
  CustomCommand debugCommand;
  GameManager *gameManager;
  
  void createObjectsInGame();
  
  void displayGameOverLayer();
  
public:
  virtual bool init();
  
  CREATE_FUNC(GameScene);
  
  static Scene *createGameScene();
  
  void update(float dt);
  
  bool onTouchOneByOneBegan(Touch *mTouch, Event *pEvent);
  
  // Render debug body can see real collision
  void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
  
  void drawPhysics(const Mat4 &transform);
  
  // GameContactListenerDelegate
  void eventCharacterContactWithMonster();
  
  void handleClickButtonOnGameOverPopUp(Ref *pSender);
};


#endif /* GameScene_h */
