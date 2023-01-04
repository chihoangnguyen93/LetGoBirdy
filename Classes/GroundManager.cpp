//
//  GroundManager.cpp
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#include "GroundManager.h"
#include "GameConfig.h"

GroundManager::GroundManager(Layer *parentLayer) {
  this->parentLayer = parentLayer;
}

GroundManager::~GroundManager() {}

void GroundManager::update(float dt) {
  for (int index = 0; index < listGround.size(); index++) {
    Ground *ground = listGround[index];
    ground->update(dt);
    if (ground->getPosition().x < -ground->getContentSize().width) {
      ground->setPositionX(contentSize.width - ground->getContentSize().width - GROUND_SPEED);
    }
  }
}

void GroundManager::setUp(b2World *physicWorld, const Vec2 position) {
  float xPosition = position.x;
  float height;
  for (int index = 0; index < NUMBER_GROUND; index++) {
    Ground *ground = new Ground();
    ground->setAnchorPoint(Vec2::ZERO);
    ground->setPosition(Vec2(xPosition, position.y));
    ground->buildPhysicBody(physicWorld);
    parentLayer->addChild(ground);
    listGround.push_back(ground);
    xPosition += ground->getContentSize().width;
    height = ground->getContentSize().height;
  }
  contentSize = Size(xPosition, height);
}

Size GroundManager::getContentSize() {
  return contentSize;
}
