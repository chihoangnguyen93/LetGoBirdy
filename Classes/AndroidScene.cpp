//
//  AndroidScene.cpp
//  LetGoBirdy
//
//  Created by Harry Nguyen on 12/10/16.
//
//

#include "AndroidScene.h"
#include "HomeScene.h"

Scene *AndroidScene::CreateScene() {
  auto newScene = Scene::create();
  auto layer = AndroidScene::create();
  newScene->addChild(layer);
  return newScene;
}

bool AndroidScene::init() {
  if (!Layer::init()) { return false; }
  
  Size winSize = Director::getInstance()->getWinSize();
  auto backgroundSprite = Sprite::create("home_back_ground.png");
  backgroundSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
  addChild(backgroundSprite);
  
  auto logoGameSprite = Sprite::create("logo_game.png");
  logoGameSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
  logoGameSprite->setScale(0.8);
  addChild(logoGameSprite);
  scheduleOnce(schedule_selector(AndroidScene::update), 1.0f);
  return true;
}

void AndroidScene::update(float dt) {
  Director::getInstance()->replaceScene(HomeScene::createHomeScene());
}
