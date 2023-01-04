//
//  BranchTreeManager.h
//  LetGoBirdy
//
//  Created by Harry Nguyen on 25/12/22.
//

#ifndef BranchTreeManager_h
#define BranchTreeManager_h

#include "BranchTree.h"

using namespace cocos2d;
using namespace std;

class BranchTreeManager {
private:
  Layer *parentLayer;
  Size contentSize;
public:
  vector<BranchTree *> listBranchTree;
  BranchTreeManager(Layer *parentLayer);
  
  virtual ~BranchTreeManager();
  
  void setUp(b2World *physicWorld, float yPosition);
  
  void update(float dt);
};


#endif /* BranchTreeManager_h */
