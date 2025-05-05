#include "raylib.h"

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
class BaseCharacter{

    public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void tick(float deltaTime);
    void unloadTexture();
    void undoMovement();
    Rectangle GetCollisionRec();

    protected:
    Texture2D texture{};
    Texture2D idle{};
    Texture2D run{};
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};

    const float speed{10.f};

    float rightLeft{1.0f};
    float runningTime{};
    float width{};
    float height{};
    float scale{4.f};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};
};

#endif