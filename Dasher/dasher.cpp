#include "raylib.h"

struct AnimData{
        Rectangle rec;
        Vector2 pos;
        int frame;
        float updateTime;
        float runningTime;
};

int main()
{
        const int windowHeight{512};
        const int windowWidth{380};

        InitWindow(windowWidth, windowHeight, "Dasher");

        // obstacles
        Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
        AnimData neb1 {
                {0.0, 0.0, nebula.width / 8, nebula.height / 8},
                {windowWidth + 300, windowHeight - nebula.height / 8}, 
                0, 
                1.0/12.0, 
                0.0};
        AnimData neb2 {
                {0.0, 0.0, nebula.width / 8, nebula.height / 8},
                {windowWidth, windowHeight - nebula.height / 8}, 
                 0, 
                1.0/16.0, 
                0.0};

        int nebVel{-200};



        // Should be a proper class btw
        Texture2D scarfy = LoadTexture("textures/scarfy.png");
        AnimData scarfyData{{0.0, 0.0, scarfy.width / 6, scarfy.height},{ windowWidth /2 - scarfy.width / 12, windowHeight - scarfy.height},0,1.0/12.0,0.0};



        const int gravity{1000};

        bool isInAir{};

        const int jumpVel{-600};

        int velocity{0};

        SetTargetFPS(60);
        while (!WindowShouldClose())
        {
                const float dT{GetFrameTime()};
                BeginDrawing();
                ClearBackground(WHITE);

                if (scarfyData.pos.y >= windowHeight - scarfyData.rec.height)
                {
                        velocity = 0;
                        isInAir = false;
                }
                else
                {
                        velocity += gravity * dT;
                }
                if (IsKeyPressed(KEY_SPACE) && !isInAir)
                {
                        velocity += jumpVel;
                        isInAir = true;
                }
                neb1.pos.x += nebVel * dT;
                neb2.pos.x += nebVel * dT;
                scarfyData.pos.y += velocity * dT;
                scarfyData.runningTime += dT;
                // scarfy's
                if (!isInAir)
                {
                        if (scarfyData.runningTime >= scarfyData.updateTime)
                        {
                                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                                scarfyData.frame++;
                                scarfyData.runningTime = 0.0;
                                if (scarfyData.frame > 5)
                                {
                                        scarfyData.frame = 0;
                                }
                        }
                }

                // nebula's
                neb1.runningTime+= dT;
                if (neb1.runningTime >= neb1.runningTime)
                {
                        neb1.runningTime = 0.0;
                        neb1.rec.x = neb1.frame * neb1.rec.width;
                        neb1.frame++;
                        if (neb1.frame > 7)
                        {
                                neb1.frame = 0;
                        }
                }

                neb2.runningTime+= dT;
                if (neb2.runningTime >= neb2.runningTime)
                {
                        neb2.runningTime = 0.0;
                        neb2.rec.x = neb1.frame * neb2.rec.width;
                        neb2.frame++;
                        if (neb2.frame > 7)
                        {
                                neb2.frame = 0;
                        }
                }
                // Draw obstacle
                DrawTextureRec(nebula, neb1.rec, neb1.pos, WHITE);
                DrawTextureRec(nebula, neb2.rec, neb2.pos, WHITE);

                // Character Draw
                DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
                EndDrawing();
        }
        UnloadTexture(scarfy);
        UnloadTexture(nebula);
        CloseWindow();
}