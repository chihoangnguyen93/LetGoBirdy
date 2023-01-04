//
//  GameScene.cpp
//  LetGoBirdy
//
//  Created by Harry Nguyen on 2/14/17.
//
//

#include "GameScene.h"
#include "GameContactListener.h"
#include "DrawDebugPhysicBody.h"
#include "GroundManager.h"
#include "MonsterManager.h"
#include "Character.h"
#include "BranchTreeManager.h"
#include "GameConfig.h"
#include "ui/CocosGUI.h"
#include "HomeScene.h"

Scene *GameScene::createGameScene() {
  auto scene = Scene::create();
  auto layer = GameScene::create();
  scene->addChild(layer);
  return scene;
}

bool GameScene::init() {
  if (!Layer::init()) { return false; }
  visibleSize = Director::getInstance()->getWinSize();
  Sprite *background = Sprite::create("main_game_back_ground.png");
  background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
  addChild(background);
  
  // Create b2World
  physicWorld = new b2World(b2Vec2(0.0, -9.81));
  GameContactListener *contactListener = new GameContactListener();
  contactListener->setDelegate(this);
  physicWorld->SetContactListener(contactListener);
  physicWorld->SetAllowSleeping(false);
  
  if (IS_TESTING) {
    DrawDebugPhysicBody *drawDebugPhysicBody = new DrawDebugPhysicBody();
    physicWorld->SetDebugDraw(drawDebugPhysicBody);
  }
  
  // Create GameManager
  gameManager = new GameManager();
  
  // Create objects in game
  createObjectsInGame();
  
  // Create touch event
  auto touchLister = EventListenerTouchOneByOne::create();
  touchLister->setSwallowTouches(true);
  touchLister->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchOneByOneBegan, this);
  Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchLister, this);
  
  // Start schedule
  scheduleUpdate();
  return true;
}

void GameScene::createObjectsInGame() {
  // create groundManager
  GroundManager *groundManager = new GroundManager(this);
  groundManager->setUp(physicWorld, Vec2::ZERO);;
  
  // create monsterManager
  MonsterManager *monsterManager = new MonsterManager(this);
  monsterManager->setUp(physicWorld, groundManager->getContentSize().height);
  
  // create character
  Character *character = new Character();
  character->setPosition(Vec2(0.0, groundManager->getContentSize().height));
  character->didWalk(WALK_ON_GROUND, groundManager->getContentSize().height - CHARACTER_Y_BUFFER);
  character->buildPhysicBody(physicWorld);
  addChild(character);
  
  // create branchTreeManager
  BranchTreeManager *branchTreeManager = new BranchTreeManager(this);
  branchTreeManager->setUp(physicWorld, DISTANCE_BRANCH_TREE_GROUND);
  
  gameManager->setObjects(groundManager, monsterManager, branchTreeManager, character);
}

void GameScene::update(float dt) {
  if (physicWorld == nullptr) { return; }
  gameManager->update(dt);
  int velocityIterations = 8;
  int positionIterations = 3;
  physicWorld->Step(dt, velocityIterations, positionIterations);
  physicWorld->ClearForces();
}

bool GameScene::onTouchOneByOneBegan(Touch *mTouch, Event *pEvent) {
  if (gameManager == NULL) { return false; }
  gameManager->didTouchOneByOneBegan();
  return true;
}

void GameScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
  Layer::draw(renderer, transform, flags);
  debugCommand.init(INT_MAX);
  debugCommand.func = CC_CALLBACK_0(GameScene::drawPhysics, this, transform);
  renderer->addCommand(&debugCommand);
}

void GameScene::drawPhysics(const Mat4 &transform) {
  Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
  Director::getInstance()->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
  physicWorld->DrawDebugData();
  Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void GameScene::eventCharacterContactWithMonster() {
  unscheduleUpdate();
  displayGameOverLayer();
}

void GameScene::displayGameOverLayer() {
  LayerColor *gameOverLayer = LayerColor::create(BG_COLOR_GAME_OVER_LAYER, visibleSize.width,
                                                 visibleSize.height);
  gameOverLayer->setPosition(Vec2::ZERO);
  this->addChild(gameOverLayer);
  
  auto gameOverPopUp = Sprite::create("game_over_pop_up.png");
  gameOverPopUp->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.4));
  gameOverLayer->addChild(gameOverPopUp);
  
  auto logoGameSprite = Sprite::create("logo_game.png");
  logoGameSprite->setPosition(Vec2(visibleSize.width / 2,
                                   gameOverPopUp->getPositionY() +
                                   gameOverPopUp->getContentSize().height / 2.0
                                   + 40.0));
  logoGameSprite->setScale(0.6);
  gameOverLayer->addChild(logoGameSprite);
  
  char bufferTotalEarnScore[512] = {0};
  snprintf(bufferTotalEarnScore, sizeof((bufferTotalEarnScore)), "%d", 100);
  Label *totalEarnScoreLabel = Label::createWithTTF(bufferTotalEarnScore, "HGEOSLAB.TTF", 28);
  totalEarnScoreLabel->setPosition(Vec2(gameOverPopUp->getContentSize().width / 2.0,
                                        gameOverPopUp->getContentSize().height / 2.0
                                        + 54.0));
  totalEarnScoreLabel->setTextColor(Color4B::WHITE);
  gameOverPopUp->addChild(totalEarnScoreLabel);
  
  Label *scoreTitleLabel = Label::createWithTTF("Score", "HGEOSLAB.TTF", 28);
  scoreTitleLabel->setPosition(Vec2(totalEarnScoreLabel->getPositionX(),
                                    totalEarnScoreLabel->getPositionY()
                                    + 32.0));
  scoreTitleLabel->setTextColor(Color4B::YELLOW);
  gameOverPopUp->addChild(scoreTitleLabel);
  
  Label *bestScoreLabel = Label::createWithTTF("Best score", "HGEOSLAB.TTF", 28);
  bestScoreLabel->setPosition(Vec2(gameOverPopUp->getContentSize().width / 2.0,
                                   gameOverPopUp->getContentSize().height / 2.0
                                   - 8.0));
  bestScoreLabel->setTextColor(Color4B::YELLOW);
  gameOverPopUp->addChild(bestScoreLabel);
  
  char bufferHighScore[512] = {0};
  snprintf(bufferHighScore, sizeof((bufferHighScore)), "%d", 200);
  Label *hightScoreLabel = Label::createWithTTF(bufferHighScore, "HGEOSLAB.TTF", 28);
  hightScoreLabel->setPosition(Vec2(bestScoreLabel->getPositionX(),
                                    bestScoreLabel->getPositionY()
                                    - 32.0));
  hightScoreLabel->setTextColor(Color4B::WHITE);
  gameOverPopUp->addChild(hightScoreLabel);
  
  auto replayButton = ui::Button::create("replay_normal_button.png", "", "",
                                         ui::Widget::TextureResType::LOCAL);
  replayButton->setPosition(Vec2(gameOverPopUp->getPositionX() - 5.0f,
                                 gameOverPopUp->getPositionY() -
                                 gameOverPopUp->getContentSize().height * 0.3));
  replayButton->addClickEventListener(
                                      CC_CALLBACK_1(GameScene::handleClickButtonOnGameOverPopUp, this));
  replayButton->setSwallowTouches(true);
  replayButton->setZoomScale(0.1f);
  replayButton->setTag(TAG_REPLAY_BUTTON);
  gameOverLayer->addChild(replayButton);
  
  auto homeButton = ui::Button::create("home_normal_button.png", "", "",
                                       ui::Widget::TextureResType::LOCAL);
  homeButton->setPosition(
                          Vec2(replayButton->getPositionX() - homeButton->getContentSize().width * 1.4,
                               replayButton->getPositionY() + homeButton->getContentSize().height * 0.3));
  homeButton->addClickEventListener(
                                    CC_CALLBACK_1(GameScene::handleClickButtonOnGameOverPopUp, this));
  homeButton->setSwallowTouches(true);
  homeButton->setZoomScale(0.1f);
  homeButton->setTag(TAG_HOME_BUTTON);
  gameOverLayer->addChild(homeButton);
  
  auto rateButton = ui::Button::create("rate_normal_button.png", "", "",
                                       ui::Widget::TextureResType::LOCAL);
  rateButton->setPosition(
                          Vec2(replayButton->getPositionX() + rateButton->getContentSize().width * 1.4,
                               replayButton->getPositionY() + rateButton->getContentSize().height * 0.3));
  rateButton->addClickEventListener(
                                    CC_CALLBACK_1(GameScene::handleClickButtonOnGameOverPopUp, this));
  rateButton->setSwallowTouches(true);
  rateButton->setZoomScale(0.1f);
  rateButton->setTag(TAG_RATE_BUTTON);
  gameOverLayer->addChild(rateButton);
  
  auto touchOnGameOverLayer = EventListenerTouchOneByOne::create();
  touchOnGameOverLayer->setSwallowTouches(true);
  touchOnGameOverLayer->onTouchBegan = [=](Touch *mtouch, Event *pEvent) { return true; };
  Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
                                                                                        touchOnGameOverLayer, gameOverLayer);
}


void GameScene::handleClickButtonOnGameOverPopUp(Ref *pSender) {
  int tag = ((ui::Button *) pSender)->getTag();
  if (tag == TAG_REPLAY_BUTTON) {
    Director::getInstance()->replaceScene(GameScene::createGameScene());
  } else if (tag == TAG_HOME_BUTTON) {
    Director::getInstance()->replaceScene(HomeScene::createHomeScene());
  } else if (tag == TAG_RATE_BUTTON) {
    Application::getInstance()->openURL(
                                        "https://play.google.com/store/apps/developer?id=Nguyen+Chi+Hoang");
  }
}


