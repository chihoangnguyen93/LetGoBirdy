//
//  BranchTreeManager.c
//  LetGoBirdy
//
//  Created by Harry Nguyen on 25/12/22.
//

#include "BranchTreeManager.h"
#include "GameConfig.h"

BranchTreeManager::BranchTreeManager(Layer *parentLayer) {
  this->parentLayer = parentLayer;
}

BranchTreeManager::~BranchTreeManager() {}

void BranchTreeManager::setUp(b2World *physicWorld, float yPosition) {
  float xPosition = parentLayer->getContentSize().width;
  float height;
  std::srand(static_cast<unsigned int>(time(0)));

  for (int index = 0; index < NUMBER_BRANCH_TREE; index++) {
    int typeBranchTree =  std::rand() % (2) + 1;
    BranchTree *branchTree = new BranchTree(typeBranchTree);
    branchTree->setAnchorPoint(Vec2::ZERO);
    branchTree->setPosition(Vec2(xPosition, yPosition));
    branchTree->buildPhysicBody(physicWorld);
    parentLayer->addChild(branchTree);
    listBranchTree.push_back(branchTree);
    height = branchTree->getContentSize().height;
    xPosition += parentLayer->getContentSize().width;
  }
  contentSize = Size(xPosition, height);
}

void BranchTreeManager::update(float dt) {
  for (int index = 0; index < listBranchTree.size(); index++) {
    BranchTree *branchTree = listBranchTree[index];
    branchTree->update(dt);
    if (branchTree->getPosition().x < -branchTree->getContentSize().width) {
      branchTree->setPositionX(contentSize.width - branchTree->getContentSize().width - GROUND_SPEED);
    }
  }
}
