#include "raylib.h"

class Prop
{
    public:
        Prop(Vector2 worldPos, Texture2D texture);
        void Render(Vector2 knightPos);
        Rectangle GetCollisionRec(Vector2 knightPos);
    private:
        Texture2D texture{};
        Vector2 worldPos{};
        float scale{4.f};
        float width{texture.width*scale};
        float height{texture.height * scale};

};