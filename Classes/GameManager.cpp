//
//  GameManager.cpp
//  LetGoBirdy
//
//  Created by Harry Nguyen on 25/12/22.
//

#include "GameManager.h"
#include "GameConfig.h"

GameManager::GameManager() {
  branchTreeManager = nullptr;
  groundManager = nullptr;
  monsterManager = nullptr;
  character = nullptr;
}

GameManager::~GameManager() {}


void GameManager::setObjects(GroundManager *groundManager,
                             MonsterManager *monsterManager,
                             BranchTreeManager *branchTreeManager,
                             Character *character) {
  this->groundManager = groundManager;
  this->monsterManager = monsterManager;
  this->branchTreeManager = branchTreeManager;
  this->character = character;
}

void GameManager::update(float dt) {
  if (branchTreeManager == nullptr ||
      groundManager == nullptr ||
      monsterManager == nullptr ||
      character == nullptr) { return; }
  character->update(dt);
  branchTreeManager->update(dt);
  groundManager->update(dt);
  monsterManager->update(dt);
  checkFallDownFromBranchTreeToGround();
}

void GameManager::checkFallDownFromBranchTreeToGround() {
  if(character->getStatus() != WALK_ON_BRANCH_TREE) { return; }
  for(int index = 0; index < branchTreeManager->listBranchTree.size(); index++) {
    BranchTree* tree = branchTreeManager->listBranchTree[index];
    if(character->getPositionX() > tree->getPositionX() + tree->getContentSize().width) {
      character->fallDownFromBranchTreeToGround();
      break;
    }
  }
}

void GameManager::didTouchOneByOneBegan() {
  if (character == NULL) { return; }
  character->didJump();
}
