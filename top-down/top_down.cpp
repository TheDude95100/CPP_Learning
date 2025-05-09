#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"
#include "enemy.h"
#include <string>

int main()
{
    const int windowHeight{384};
    const int windowWidth{384};

    const float mapScale{4.f};

    InitWindow(windowWidth, windowHeight, "top down");

    Texture2D background = LoadTexture("nature_tileset/OpenWorldMap24x24.png");

    Vector2 mapPos{0.0, 0.0};

    Prop props[2]{
        Prop{Vector2{600.0f, 300.0f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.0f, 500.0f}, LoadTexture("nature_tileset/Log.png")},
    };

    Enemy goblin(Vector2{500.0f, 300.0f},
                 LoadTexture("characters/goblin_idle_spritesheet.png"),
                 LoadTexture("characters/goblin_run_spritesheet.png"));

    Enemy slime(Vector2{500.f, 700.f},
                LoadTexture("characters/slime_idle_spritesheet.png"),
                LoadTexture("characters/slime_run_spritesheet.png"));

    Enemy *enemies[]{
        &goblin,
        &slime
    };

    Character knight(windowWidth, windowHeight);

    for(auto enemy : enemies){
        enemy->setTarget(&knight);
    }
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dT = GetFrameTime();
        BeginDrawing();
        ClearBackground(WHITE);
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        DrawTextureEx(background, mapPos, 0.0, mapScale, WHITE);

        for (Prop prop : props)
        {
            prop.Render(knight.getWorldPos());
        }
        if (!knight.GetAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightHealth{"Health: "};
            knightHealth.append(std::to_string(knight.GetHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.f, 45.f, 40, RED);
        }
        knight.tick(dT);
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > background.width * mapScale ||
            knight.getWorldPos().y + windowHeight > background.height * mapScale)
        {
            knight.undoMovement();
        }

        for(auto enemy: enemies){
            enemy->tick(dT);
        }

        for (Prop prop : props)
        {

            if (CheckCollisionRecs(prop.GetCollisionRec(knight.getWorldPos()), knight.GetCollisionRec()))
            {
                knight.undoMovement();
            }
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for(auto enemy : enemies){
                if(enemy->GetVelocity() == Vector2{}){
                    if (CheckCollisionRecs(enemy->GetCollisionRec(), knight.GetWeaponCollisionRec()))
                    {
                        enemy->SetAlive(false);
                    }
                }
            }

        }
        EndDrawing();
    }
    UnloadTexture(background);
    knight.unloadTexture();
    for(auto enemy : enemies){
        enemy->unloadTexture();
    }
}