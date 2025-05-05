#include "prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D texture) :
worldPos(pos),
texture(texture) 
{

}

void Prop::Render(Vector2 knightPos){
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};
    DrawTextureEx(texture, screenPos,0.0, scale, WHITE);
}

Rectangle Prop::GetCollisionRec(Vector2 knightPos){
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width,
        height,
        };
}