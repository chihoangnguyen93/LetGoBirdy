//
//  BranchTree.cpp
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#include "BranchTree.h"
#include "GameConfig.h"

static char bufferFileName[512] = {0};

BranchTree::BranchTree(int type) {
  surfaceBody = nullptr;
  snprintf(bufferFileName, sizeof(bufferFileName), "%d_tree_branch.png", type);
  mainSprite = Sprite::create(bufferFileName);
  mainSprite->setAnchorPoint(Vec2::ZERO);
  mainSprite->setPosition(Vec2::ZERO);
  this->addChild(mainSprite);
}

BranchTree::~BranchTree() {}

Size BranchTree::getContentSize() {
  return mainSprite->getContentSize();
}

void BranchTree::update(float dt) {
  float xPosition = this->getPositionX();
  xPosition -= GROUND_SPEED;
  this->setPositionX(xPosition);
  if (surfaceBody != nullptr) {
    surfaceBody->SetTransform(
                              b2Vec2((getPositionX() + (getContentSize().width / 2.0)) / PTM_RATIO,
                                     (getPositionY() + (getContentSize().height) / 2.0) / PTM_RATIO),
                              0.0);
  }
}

void BranchTree::buildPhysicBody(b2World *physicWorld) {
  b2PolygonShape shape;
  shape.SetAsBox(mainSprite->getContentSize().width / 2.0 / PTM_RATIO,
                 mainSprite->getContentSize().height * BRANCH_TREE_RATIO_HEIGHT_BODY / PTM_RATIO);
  
  b2FixtureDef fixtureDef;
  fixtureDef.density = 0;
  fixtureDef.friction = 0;
  fixtureDef.restitution = 0.0;
  fixtureDef.shape = &shape;
  fixtureDef.filter.categoryBits = kBranchTreeCatBit;
  fixtureDef.filter.maskBits = kBranchTreeMaskBit;
  
  b2BodyDef bodyDef;
  bodyDef.type = b2_staticBody;
  bodyDef.userData = this;
  bodyDef.position.Set((getPositionX() + getContentSize().width / 2.0) / PTM_RATIO,
                       (getPositionY() + (getContentSize().height) / 2.0) / PTM_RATIO);
  surfaceBody = physicWorld->CreateBody(&bodyDef);
  surfaceBody->CreateFixture(&fixtureDef);
}
