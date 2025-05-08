#ifndef CHARACTER_H
#define CHARACTER_H
#include "baseCharacter.h"
class Character : public BaseCharacter
{

public:
    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPosition() override;
    Rectangle GetWeaponCollisionRec(){ return weaponCollisionRec;};
    float GetHealth() const {return health;};
    void takeDamage(float damage){health -= damage;};
private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};

    Rectangle weaponCollisionRec{};

    float health{100.f};
};
#endif