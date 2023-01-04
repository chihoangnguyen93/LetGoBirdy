//
//  GameConfig.h
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#ifndef GameConfig_h
#define GameConfig_h

#define NUMBER_GROUND 2
#define NUMBER_BRANCH_TREE 3
#define CHARACTER_SPEED 5
#define GROUND_SPEED 5
#define MONSTER_SPEED 5

#define DISTANCE_BRANCH_TREE_GROUND 230.0
#define BRANCH_TREE_RATIO_HEIGHT_BODY 0.3

#define DEFAULT_CONTENT_SIZE Size(54, 54)
#define RATIO_SCALE_CHARACTER_SKELETON 0.104f
#define RATIO_SCALE_MONSTER_SKELETON 0.086f
#define JUMP_UP_VELOCITY b2Vec2(0.0/PTM_RATIO, 352.0/PTM_RATIO)
#define JUMP_DOWN_VELOCITY b2Vec2(0.0/PTM_RATIO, -352.0/PTM_RATIO)

#define IS_TESTING false
#define PTM_RATIO 32.0f
#define CHARACTER_Y_BUFFER 6.0

/// Game over layer
#define BG_COLOR_GAME_OVER_LAYER Color4B(115.0f, 115.0f, 115.0f,200.0f)
#define TAG_REPLAY_BUTTON  201
#define TAG_HOME_BUTTON  202
#define TAG_RATE_BUTTON  203

enum {
  PIG = 1,
  CAT = 2
} MONSTER_TYPE;


enum {
  WALK_ON_GROUND = 1,
  WALK_ON_BRANCH_TREE = 2,
  JUMP = 3,
  DIE = 4
} CHARACTER_STATUS;


enum{
  kCharacterCatBit = 1 << 0,
  kGroundCatBit = 1<< 1,
  kBranchTreeCatBit = 1 << 2,
  kMonsterCatBit = 1 << 3
};

enum{
  kCharacterMaskBit =  kGroundCatBit | kBranchTreeCatBit | kMonsterCatBit,
  kGroundMaskBit = kCharacterCatBit,
  kBranchTreeMaskBit = kCharacterCatBit,
  kMonsterMashBit = kCharacterCatBit,
};


#endif /* GameConfig_h */
