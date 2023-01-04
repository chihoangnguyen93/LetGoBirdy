//
//  MonsterManager.cpp
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#include "MonsterManager.h"
#include "GameConfig.h"

MonsterManager::MonsterManager(Layer *parentLayer) {
  this->parentLayer = parentLayer;
  visibleSize = parentLayer->getContentSize();
}

MonsterManager::~MonsterManager() {}


void MonsterManager::update(float dt) {
  for (int index = 0; index < listMonster.size(); index++) {
    Monster *monster = listMonster[index];
    monster->update(index);
    if (monster->getPositionX() < 0.0) {
      monster->setPositionX(widthContent - monster->getContentSize().width - MONSTER_SPEED);
    }
  }
}

void MonsterManager::setUp(b2World *physicWorld, const float yPosition) {
  Monster *pigPrisonMonster = new Monster(PIG, true);
  pigPrisonMonster->setPosition(Vec2(visibleSize.width, yPosition));
  parentLayer->addChild(pigPrisonMonster);
  pigPrisonMonster->buildPhysicBody(physicWorld);
  listMonster.push_back(pigPrisonMonster);
  
  Monster *pigMonster = new Monster(PIG, false);
  pigMonster->setPosition(Vec2(visibleSize.width * 1.5, yPosition));
  parentLayer->addChild(pigMonster);
  pigMonster->buildPhysicBody(physicWorld);
  listMonster.push_back(pigMonster);
  
  Monster *catPrisonMonster = new Monster(CAT, true);
  catPrisonMonster->setPosition(Vec2(visibleSize.width * 2, yPosition));
  parentLayer->addChild(catPrisonMonster);
  catPrisonMonster->buildPhysicBody(physicWorld);
  listMonster.push_back(catPrisonMonster);
  
  Monster *catMonster = new Monster(CAT, false);
  catMonster->setPosition(Vec2(visibleSize.width * 2.5, yPosition));
  parentLayer->addChild(catMonster);
  catMonster->buildPhysicBody(physicWorld);
  listMonster.push_back(catMonster);
  
  widthContent = visibleSize.width * 2.5;
}
