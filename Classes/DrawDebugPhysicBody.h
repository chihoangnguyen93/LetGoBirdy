//
//  DrawDebugPhysicBody.h
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#ifndef DrawDebugPhysicBody_h
#define DrawDebugPhysicBody_h

#include "cocos2d.h"
#include <Box2D/Box2D.h>

USING_NS_CC;
using namespace cocos2d;

class DrawDebugPhysicBody : public b2Draw {
private:
  Color4B polygonColor;
  Color4B circleColor;
  Color4B solidCircleColor;
public:
  DrawDebugPhysicBody(Color4B polygonColor = Color4B(220, 0, 0, 255),
                      Color4B circleColor = Color4B(255, 110, 49, 255),
                      Color4B solidCircleColor = Color4B(36, 55, 99, 255));
  
  virtual void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
  
  virtual void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
  
  virtual void DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color);
  
  virtual void
  DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color);
  
  virtual void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color);
  
  virtual void DrawTransform(const b2Transform &xf);
  
  virtual void DrawPoint(const b2Vec2 &p, float32 size, const b2Color &color);
};

#endif /* DrawDebugPhysicBody_h */
