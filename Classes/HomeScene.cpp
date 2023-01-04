//
//  HomeScene.cpp
//  LetGoBirdy
//
//  Created by Nguyen Chi Hoang on 4/5/17.
//
//

#include "HomeScene.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

#define TAG_BTN_PLAY 101

Scene *HomeScene::createHomeScene() {
  auto scene = Scene::create();
  auto layer = HomeScene::create();
  scene->addChild(layer);
  return scene;
}

bool HomeScene::init() {
  if (!Layer::init()) { return false; }

  winSize = Director::getInstance()->getWinSize();
  auto backgroundSprite = Sprite::create("home_back_ground.png");
  backgroundSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
  addChild(backgroundSprite);
  
  auto logoGameSprite = Sprite::create("logo_game.png");
  logoGameSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
  logoGameSprite->setScale(0.8);
  addChild(logoGameSprite);
  
  ui::Button *playButton = ui::Button::create("play_button.png", "", "", ui::Widget::TextureResType::LOCAL);
  playButton->setZoomScale(0.1f);
  playButton->setPosition(Vec2(winSize.width / 2, logoGameSprite->getPositionY() - playButton->getContentSize().height * 2.0));
  playButton->setTag(TAG_BTN_PLAY);
  playButton->addClickEventListener(CC_CALLBACK_1(HomeScene::handleClickButton, this));
  playButton->setSwallowTouches(true);
  addChild(playButton);
  
  return true;
}

void HomeScene::handleClickButton(Ref *pSender) {
  int tag = ((ui::Button *) pSender)->getTag();
  if (tag == TAG_BTN_PLAY) {
    Director::getInstance()->replaceScene(GameScene::createGameScene());
  }
}
