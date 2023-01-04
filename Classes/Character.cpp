//
//  Character.cpp
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#include "Character.h"
#include "GameConfig.h"

Character::Character() {
  body = nullptr;
  visibleSize = Director::getInstance()->getWinSize();
  skeleton = spine::SkeletonAnimation::createWithJsonFile("bird.json", "bird.atlas",
                                                          RATIO_SCALE_CHARACTER_SKELETON);
  skeleton->setPosition(Vec2::ZERO);
  this->setContentSize(DEFAULT_CONTENT_SIZE);
  this->addChild(skeleton);
}

Character::~Character() {}

void Character::update(float dt) {
  switch (status) {
    case WALK_ON_GROUND:
      if (body == nullptr) { break; }
      if (this->getPositionX() < visibleSize.width / 2.0) {
        float xPosition = getPositionX();
        xPosition += CHARACTER_SPEED;
        this->setPositionX(xPosition);
      }
      this->setPositionY(walkYPosition);
      body->SetTransform(b2Vec2(getPositionX() / PTM_RATIO, (getPositionY() + getContentSize().height / 2.0) / PTM_RATIO), 0.0f);
      break;
    case WALK_ON_BRANCH_TREE:
      this->setPositionY(walkYPosition);
      body->SetTransform(b2Vec2(getPositionX() / PTM_RATIO, (getPositionY() + getContentSize().height / 2.0) / PTM_RATIO), 0.0f);
      break;
    case JUMP:
      b2Vec2 bodyPosition = body->GetPosition();
      this->setPosition(Vec2(bodyPosition.x * PTM_RATIO, bodyPosition.y * PTM_RATIO - getContentSize().height / 2.0));
      break;
  }
}

void Character::runWalkAnimation() {
  skeleton->clearTrack();
  skeleton->setAnimation(0, "walk", true);
}

void Character::didWalk(int walkType, float yPosition) {
  if (status == walkType) { return; }
  walkYPosition = yPosition;
  status = walkType;
  runWalkAnimation();
}

void Character::didJump() {
  if (status == JUMP) { return; }
  status = JUMP;
  skeleton->clearTrack();
  skeleton->setAnimation(0, "jump", false);
  body->SetLinearVelocity(JUMP_UP_VELOCITY);
}

void Character::fallDownFromBranchTreeToGround() {
  if (status == JUMP) { return; }
  status = JUMP;
//  b2Vec2 vel = body->GetLinearVelocity();
//  float velChange = 5 - vel.x;
//  float force = body->GetMass() * velChange / (1/60.0); //f = mv/t
//  body->ApplyForce( b2Vec2(0.0,-force), body->GetWorldCenter(), false);
////  body->SetLinearVelocity(JUMP_DOWN_VELOCITY);
}

void Character::didDie() {
  if (status == DIE) { return; }
  status = DIE;
  skeleton->clearTrack();
  skeleton->setAnimation(0, "die", false);
}

void Character::buildPhysicBody(b2World *physicWorld) {
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.userData = this;
  bodyDef.bullet = true;
  bodyDef.position.Set(getPositionX() / PTM_RATIO,
                       (getPositionY() + getContentSize().height / 2.0) / PTM_RATIO);
  body = physicWorld->CreateBody(&bodyDef);
  body->SetFixedRotation(false);
  
  b2PolygonShape shape;
  shape.SetAsBox((getContentSize().width / 2.0) / PTM_RATIO,
                 (getContentSize().height / 2.0) / PTM_RATIO);
  b2FixtureDef fixtureDef;
  fixtureDef.density = 0;
  fixtureDef.friction = 0.0;
  fixtureDef.restitution = 0.0;
  fixtureDef.filter.categoryBits = kCharacterCatBit;
  fixtureDef.filter.maskBits = kCharacterMaskBit;
  fixtureDef.shape = &shape;
  body->CreateFixture(&fixtureDef);
}

int Character::getStatus() {
  return status;
}
