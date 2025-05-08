#include "baseCharacter.h"
#include "raymath.h"

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
        getScreenPosition().x,
        getScreenPosition().y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::tick(float deltaTime){
    if(!GetAlive())return;
    worldPosLastFrame = worldPos;
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }
    if (Vector2Length(velocity) != 0.0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};
    Rectangle source{frame * (float)texture.width / 6.f, 0.f, rightLeft * width, height};
    Rectangle dest{getScreenPosition().x, getScreenPosition().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}