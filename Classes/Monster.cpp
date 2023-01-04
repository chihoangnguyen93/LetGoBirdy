//
//  Monster.cpp
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#include "Monster.h"
#include "GameConfig.h"

Monster::Monster(int type, bool imPrisoned) {
  body = nullptr;
  switch (type) {
    case PIG:
      skeleton = SkeletonAnimation::createWithJsonFile("pig.json", "pig.atlas",
                                                       RATIO_SCALE_MONSTER_SKELETON);
      break;
    default:
      skeleton = SkeletonAnimation::createWithJsonFile("cat.json", "cat.atlas",
                                                       RATIO_SCALE_MONSTER_SKELETON);
      break;
  }
  skeleton->clearTrack();
  skeleton->setAnimation(0, "walk", true);
  this->addChild(skeleton);
  if (imPrisoned) {
    addPrisonOutSide(type);
  } else {
    this->setContentSize(DEFAULT_CONTENT_SIZE);
  }
  this->setScaleX(-1);
}

Monster::~Monster() {}

void Monster::addPrisonOutSide(int type) {
  Sprite *sprite;
  switch (type) {
    case PIG:
      sprite = Sprite::create("cage_pig.png");
      break;
    default:
      sprite = Sprite::create("cage_cat.png");
      break;
  }
  this->setContentSize(sprite->getContentSize());
  sprite->setPosition(Vec2(0, sprite->getContentSize().height / 2));
  this->addChild(sprite);
}

void Monster::update(float dt) {
  float xPosition = this->getPositionX();
  xPosition -= MONSTER_SPEED;
  this->setPositionX(xPosition);
  
  if (body != nullptr) {
    body->SetTransform(b2Vec2((getPositionX()) / PTM_RATIO,
                              (getPositionY() + getContentSize().height / 2.0) / PTM_RATIO),
                       0.0f);
  }
}

void Monster::buildPhysicBody(b2World *physicWorld) {
  b2BodyDef bodyDef;
  bodyDef.type = b2_staticBody;
  bodyDef.userData = this;
  bodyDef.position.Set((getPositionX()) / PTM_RATIO,
                       (getPositionY() + getContentSize().height / 2.0) / PTM_RATIO);
  body = physicWorld->CreateBody(&bodyDef);
  body->SetFixedRotation(false);
  
  b2PolygonShape shape;
  shape.SetAsBox((getContentSize().width / 2.0) / PTM_RATIO,
                 (getContentSize().height * 0.4) / PTM_RATIO);
  b2FixtureDef fixtureDef;
  fixtureDef.density = 0;
  fixtureDef.friction = 0.0;
  fixtureDef.restitution = 0.0;
  fixtureDef.filter.categoryBits = kMonsterCatBit;
  fixtureDef.filter.maskBits = kMonsterMashBit;
  fixtureDef.shape = &shape;
  body->CreateFixture(&fixtureDef);
}
