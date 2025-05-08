#include "enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) 
{
    worldPos = pos ;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 3.0f;
}

void Enemy::tick(float deltaTime)
{
    if(!GetAlive()) return;
    //get to Target
    velocity = Vector2Subtract(target->getScreenPosition(), getScreenPosition());
    if(Vector2Length(velocity) < detectionRadius) velocity = {};
    BaseCharacter::tick(deltaTime);
    if(CheckCollisionRecs(GetCollisionRec(), target->GetCollisionRec())){
        target->takeDamage(damagePerSec * deltaTime);
    }
}

Vector2 Enemy::getScreenPosition(){
    return Vector2Subtract(worldPos, target->getWorldPos());
}