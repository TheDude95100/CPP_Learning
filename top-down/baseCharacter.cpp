#include "baseCharacter.h"

BaseCharacter::BaseCharacter(){};


void BaseCharacter::unloadTexture()
{
    UnloadTexture(texture);
    UnloadTexture(idle);
    UnloadTexture(run);
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec(){
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale
    };
}