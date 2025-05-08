

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"
class BaseCharacter{

    public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    virtual void tick(float deltaTime);
    void unloadTexture();
    void undoMovement();
    Rectangle GetCollisionRec();
    virtual Vector2 getScreenPosition() = 0;
    bool GetAlive(){return alive;};
    void SetAlive(bool statut){alive = statut;};
    Vector2 GetVelocity(){return velocity;};


    protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};

    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};

    float windowWidth{};
    float windowHeigth{};
    float speed{10.f};
    Vector2 velocity{};

    float rightLeft{1.0f};
    float runningTime{};
    float width{};
    float height{};
    float scale{4.f};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};

    private:
    bool alive{true};
};

#endif