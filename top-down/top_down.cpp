#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"

int main()
{
    const int windowHeight{384};
    const int windowWidth{384};

    const float mapScale{4.f};

    InitWindow(windowWidth, windowHeight, "top down");

    Texture2D background = LoadTexture("nature_tileset/OpenWorldMap24x24.png");

    Vector2 mapPos{0.0, 0.0};

    Prop props[2]{
        Prop{Vector2{600.0f,300.0f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.0f,500.0f}, LoadTexture("nature_tileset/Log.png")},
    };

    Character knight(windowWidth,windowHeight);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(WHITE);
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        DrawTextureEx(background, mapPos, 0.0, mapScale, WHITE);
        knight.tick(GetFrameTime());
        
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > background.width * mapScale ||
            knight.getWorldPos().y + windowHeight > background.height * mapScale)
            {
                knight.undoMovement();
            }

        EndDrawing();
    }

    UnloadTexture(background);
    knight.unloadTexture();
}