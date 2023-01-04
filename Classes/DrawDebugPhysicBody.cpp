//
//  DrawDebugPhysicBody.cpp
//  LetGoBirdy
//
//  Created by Harry Nguyen on 24/12/22.
//

#include "DrawDebugPhysicBody.h"
#include "GameConfig.h"

DrawDebugPhysicBody::DrawDebugPhysicBody(Color4B polygonColor, Color4B circleColor, Color4B solidCircleColor) {
  this->polygonColor = polygonColor;
  this->circleColor = circleColor;
  this->solidCircleColor = solidCircleColor;
  this->SetFlags(e_shapeBit);
}

void DrawDebugPhysicBody::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
  Vec2* points = new Vec2[vertexCount];
  for(int i=0;i<vertexCount;i++){
    points[i].x = vertices[i].x * PTM_RATIO;
    points[i].y = vertices[i].y * PTM_RATIO;
  }
  DrawPrimitives::drawPoly(points, vertexCount, false);
}

void DrawDebugPhysicBody::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
  Vec2* points = new Vec2[vertexCount];
  for(int i=0;i<vertexCount;i++){
    points[i].x = vertices[i].x * PTM_RATIO;
    points[i].y = vertices[i].y * PTM_RATIO;
  }
  DrawPrimitives::drawSolidPoly(points, vertexCount, Color4F(polygonColor));
}

void DrawDebugPhysicBody::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color){
  DrawPrimitives::setDrawColor4B(circleColor.r, circleColor.b, circleColor.g, circleColor.a);
  DrawPrimitives::drawCircle(Vec2(center.x*PTM_RATIO, center.y*PTM_RATIO), radius*PTM_RATIO, 360.0f, 100, true, 1.0f, 1.0f);
}

void DrawDebugPhysicBody::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color){
  DrawPrimitives::setDrawColor4B(solidCircleColor.r, solidCircleColor.b , solidCircleColor.g, solidCircleColor.a);
  DrawPrimitives::drawSolidCircle(Vec2(center.x*PTM_RATIO, center.y*PTM_RATIO), radius*PTM_RATIO, 360.0f, 100, 1.0f, 1.0f);
}

void DrawDebugPhysicBody::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color){}
void DrawDebugPhysicBody::DrawTransform(const b2Transform& xf){}
void DrawDebugPhysicBody::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) {}
