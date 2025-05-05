#include "baseCharacter.h"

class Character : public BaseCharacter
{

public:
    Character(int winWidth, int winHeight);

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
};