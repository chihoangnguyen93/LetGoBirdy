//
//  Ground.cpp
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#include "Ground.h"
#include "GameConfig.h"

Ground::Ground() {
  body = nullptr;
  mainSprite = Sprite::create("ground.png");
  mainSprite->setAnchorPoint(Vec2::ZERO);
  mainSprite->setPosition(Vec2::ZERO);
  this->addChild(mainSprite);
}

Ground::~Ground() {}


Size Ground::getContentSize() {
  return mainSprite->getContentSize();
}

void Ground::update(float dt) {
  float xPosition = this->getPositionX();
  xPosition -= GROUND_SPEED;
  this->setPositionX(xPosition);
  
  if (body != nullptr) {
    body->SetTransform(b2Vec2((getPositionX() + getContentSize().width / 2.0) / PTM_RATIO,
                              (getPositionY() + getContentSize().height / 2.0) / PTM_RATIO),
                       0.0f);
  }
}

void Ground::buildPhysicBody(b2World *physicWorld) {
  b2BodyDef bodyDef;
  bodyDef.type = b2_staticBody;
  bodyDef.userData = this;
  bodyDef.position.Set((getPositionX() + getContentSize().width / 2.0) / PTM_RATIO,
                       (getPositionY() + getContentSize().height / 2.0) / PTM_RATIO);
  body = physicWorld->CreateBody(&bodyDef);
  body->SetFixedRotation(false);
  
  b2PolygonShape shape;
  shape.SetAsBox((mainSprite->getContentSize().width / 2.0) / PTM_RATIO,
                 (mainSprite->getContentSize().height / 2.0) / PTM_RATIO);
  b2FixtureDef fixtureDef;
  fixtureDef.density = 0;
  fixtureDef.friction = 0.0;
  fixtureDef.restitution = 0.0;
  fixtureDef.filter.categoryBits = kGroundCatBit;
  fixtureDef.filter.maskBits = kGroundMaskBit;
  fixtureDef.shape = &shape;
  body->CreateFixture(&fixtureDef);
}
