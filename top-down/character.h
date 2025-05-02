#include "raylib.h"

class Character
{

public:
    Character(int winWidth, int winHeight);
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);
    void unloadTexture();
    void undoMovement();

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
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